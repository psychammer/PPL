#pragma once
#include <iostream>
#include <optional>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

enum class TokenType {
    _return,
    int_lit,
    semi

};

struct Token{
    TokenType type;
    std::optional<std::string> value;
};

class Tokenizer {
    public:
        inline explicit Tokenizer(const std::string&  src)
            : m_src(std::move(src))

        {
        }

        inline std::vector<Token> tokenize(){ 
            std::vector<Token> tokens;

            std::string buf;
            while(peak().has_value()){
                if(std::isalpha(peak().value())){
                    buf.push_back(consume());
                    
                    while (peak().has_value() && std::isalnum(peak().value())){
                        buf.push_back(consume());
                    }
                    if(buf == "exit" || buf == "return"){
                        tokens.push_back({.type = TokenType::_return});
                        buf.clear();
                        continue;
                    }
                    else{
                        std::cerr << "You messed up!" << std::endl;
                        exit(EXIT_FAILURE);
                    }

                }
                else if(std::isdigit(peak().value())){
                    buf.push_back(consume());
                    while(peak().has_value() && std::isdigit(peak().value())){
                        buf.push_back(consume());
                    } 
                    tokens.push_back({.type = TokenType::int_lit, .value = buf});
                }
                else if(peak().value() == ';'){
                    consume();
                    tokens.push_back({.type = TokenType::semi});
                    continue;
                }
                else if(std::isspace(peak().value())){
                    consume();
                    continue;
                }
                else{
                    std:: cerr << "You messed it up!" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            m_index = 0;
            return tokens;

        }

    private:

        [[nodiscard]] inline std::optional<char> peak(int ahead = 1) const{
            if(m_index + ahead > m_src.length()){
                return {};
            }
            else{
                return m_src.at(m_index);
            }
            
        }

        inline char consume(){
            return m_src.at(m_index++);
            

        }

        const std::string m_src;
        int m_index = 0;
};