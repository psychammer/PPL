#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT
{
    enum{
        TOKEN_IDENTIFIER,
        TOKEN_ASSIGNMENT,
        TOKEN_COMMA,
        TOKEN_SEMICOLON,
        TOKEN_COLON,
        TOKEN_DOUBLEQUOTATION,
        TOKEN_SINGLEQUOTATION,
        TOKEN_QUESTION,
        TOKEN_EXCLAMATION,
        TOKEN_OPERATOR,
        TOKEN_CONSTANT,
        TOKEN_KEYWORDS,
        TOKEN_STRING,
        TOKEN_SEMI,
        TOKEN_L_PARENTHESIS,
        TOKEN_R_PARENTHESIS,
        TOKEN_INT_LITERAL,
    } tokenType;

    char* token_value; // Value within the token, for example age = 5; the integer literal value of the lexeme '5' is 5
} token_structure;

token_structure* init_token(int token_type, char* value);
#endif