#ifndef LEXER_H
#define LEXER_H
#include "./token.h"

typedef struct LEXER_STATE{
    char curChar;
    unsigned int i;
    char* contents;
} lexer_state;

lexer_state* init_lexer(char* contents);

void lexer_next_char(lexer_state* lexer);

void lexer_skip_whitespace(lexer_state* lexer);

token_structure* lexer_get_next_token(lexer_state* lexer);

token_structure* lexer_string_buffer(lexer_state* lexer);

token_structure* lexer_advance_and_get_token(lexer_state* lexer, token_structure* token);

token_structure* lexer_collect_id(lexer_state* lexer);

char* char_to_string(lexer_state* lexer_advance);
#endif