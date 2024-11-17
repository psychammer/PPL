#include "./generation.hpp"
#include "./parser.hpp"
#include "./tokenization.hpp"


int main(int argc, char* argv[]){
    if(argc != 2){
        std::cerr << "Incorrect usage. Correct usage is..." << std::endl;
        std::cerr << "hydro <input.hy>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string contents;
    std::stringstream contents_stream;
    {
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    Tokenizer tokenizer(std::move(contents)); //take the pointer of the string and passing it and clear it to prevent copies
    std::vector<Token> tokens = tokenizer.tokenize();

    Parser parser(std::move(tokens)); 
    std::optional<NodeExit> tree = parser.parse();
    
    if(!tree.has_value()){
        std::cerr << "No exit statement found" << std::endl; 
        exit(EXIT_FAILURE);
    }

    Generator generator(tree.value());
    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.generate();
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    // std::cout<< contents << std::endl;

    // std::cout << argv[1] << std::endl;
    return 0;
}