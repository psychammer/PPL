#include "./Lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <stdio.h>
#include <ctype.h> // For isspace()

void removeWhitespaces(char* str) {
    char* src = str; 
    char* dest = str; 

    while (*src) {
        if (!isspace((unsigned char)*src)) {
            *dest++ = *src; // Copy non-whitespace characters
        }
        src++;
    }
    *dest = '\0'; // Null-terminate the result
}


lexer_state* init_lexer(char* contents){
    lexer_state* lexer = calloc(1, sizeof(struct LEXER_STATE));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->curChar = lexer->contents[lexer->i];

    return lexer;
}

token_structure* init_token(int type, char* value){
    token_structure* token = calloc(1, sizeof(struct TOKEN_STRUCT)); 
    token->tokenType = type;
    token->token_value = value;

    return token;
}

void lexer_next_char(lexer_state* lexer){
    if(lexer->curChar != '\0' && lexer->i < strlen(lexer->contents));{
        lexer->i += 1; // go to the next character
        lexer->curChar = lexer->contents[lexer->i];
    }
}

// void lexer_skip_whitespace(lexer_state* lexer){
//     while((lexer->curChar=" " || lexer->curChar == 10) && lexer->i < strlen(lexer->contents)){ // 10 means new line
//         lexer_next_char(lexer);
//     }
// }

token_structure* lexer_get_next_token(lexer_state* lexer){
    while(lexer->curChar != '\0' && lexer->i < strlen(lexer->contents)){

        if(lexer->curChar == ' ' || lexer->curChar == 10 || lexer->curChar == 13){                                
            lexer_next_char(lexer);
        }

        if(lexer->curChar == '"'){
            return lexer_string_buffer(lexer);
        }
            
            
        if(isalnum(lexer->curChar)){
            return lexer_collect_id(lexer);
        }

        if(lexer->curChar=='*' && lexer->contents[lexer->i+1]=='*'){
            char* value = calloc(3, sizeof(char));
            value[0] = '*';
            value[1] = '*';
            value[2] = '\0';
            lexer_next_char(lexer);
            return lexer_advance_and_get_token(lexer, init_token(TOKEN_OPERATOR, value));
        }

       
        switch(lexer->curChar){
            case '+': return lexer_advance_and_get_token(lexer, init_token(TOKEN_OPERATOR, char_to_string(lexer)));
                      break;
            case '-': return lexer_advance_and_get_token(lexer, init_token(TOKEN_OPERATOR, char_to_string(lexer)));
                      break;   
            case '/': return lexer_advance_and_get_token(lexer, init_token(TOKEN_OPERATOR, char_to_string(lexer)));
                      break;
            case '*': return lexer_advance_and_get_token(lexer, init_token(TOKEN_OPERATOR, char_to_string(lexer)));
                      break;       
            case '=': return lexer_advance_and_get_token(lexer, init_token(TOKEN_ASSIGNMENT, char_to_string(lexer)));
                      break;
            case ':': return lexer_advance_and_get_token(lexer, init_token(TOKEN_SEMI, char_to_string(lexer)));
                      break;
            case '(': return lexer_advance_and_get_token(lexer, init_token(TOKEN_L_PARENTHESIS, char_to_string(lexer)));
                      break;
            case ')': return lexer_advance_and_get_token(lexer, init_token(TOKEN_R_PARENTHESIS, char_to_string(lexer)));
                      break;
            case ';': token_structure* result = lexer_advance_and_get_token(lexer, init_token(TOKEN_SEMI, char_to_string(lexer)));
                    //   printf("curr %ld", strlen(lexer->contents));
                      return result;
                      break;
        }
    }

    return (void*)0;
}

token_structure* lexer_advance_and_get_token(lexer_state* lexer, token_structure* token){
    lexer_next_char(lexer);

    return token;
}

token_structure* lexer_string_buffer(lexer_state* lexer){
    lexer_next_char(lexer);

    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while(lexer->curChar != '"'){  //while it's not the end of the string
        char* curChar = char_to_string(lexer);
        value = realloc(value, (strlen(value) + strlen(curChar) + 1) * sizeof(char));
        strcat(value, curChar);
        lexer_next_char(lexer);
    }
    lexer_next_char(lexer);

    return init_token(TOKEN_STRING, value);
}

token_structure* lexer_collect_id(lexer_state* lexer){
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while(isalnum(lexer->curChar)){  //while it's not the end of the string
        char* curChar = char_to_string(lexer);
        value = realloc(value, (strlen(value) + strlen(curChar) + 1) * sizeof(char));
        strcat(value, curChar);

        lexer_next_char(lexer);
    }

    removeWhitespaces(value);
    if(strcmp(value, "and")==0 || strcmp(value, "or")==0 || strcmp(value, "not")==0){
        return init_token(TOKEN_OPERATOR, value);
    }
    


    return init_token(TOKEN_IDENTIFIER, value);


}

char* char_to_string(lexer_state* lexer){
    char* str = calloc(2, sizeof(char)); // 2 for the null terminator
    str[0] = lexer->curChar;
    str[1] = '\0';

    return str;
}


int main(void){
    FILE *file_ptr;

    char ch;
    file_ptr = fopen("./test.ri", "r");
    
    if(NULL == file_ptr){
        printf("Can't be opened \n");
        return EXIT_FAILURE;
    }

    
    int content_size=0;
    char* str = calloc(1, sizeof(char));
    str[0] = '\0';
    while((ch = fgetc(file_ptr)) != EOF){
        char* ch_as_string = calloc(2, sizeof(char)); // convert ch to string
        ch_as_string[0] = ch;
        ch_as_string[1] = '\0';
        str = realloc(str, (strlen(str) + strlen(ch_as_string) + 1));
        strcat(str, ch_as_string);

        content_size++;
    }

    // printf("%s ", str);

    lexer_state* lexer = init_lexer(str);
    token_structure* token = (void*)0;

    while((token = lexer_get_next_token(lexer)) != (void*)0){
        printf("TOKEN(%d, %s)\n", token->tokenType, token->token_value);
    }


    fclose(file_ptr);
    return 0;

}