#ifndef TOKEN_H
#define TOKEN_H

enum token_class_t{
    KEYWORD_PUT,
    KEYWORD_GET,
    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_FOR,
    KEYWORD_IN,
    KEYWORD_TO,
    KEYWORD_WHILE,
    KEYWORD_TYPE,
    KEYWORD_FNC,
    KEYWORD_RETURN,
    KEYWORD_BREAK,
    KEYWORD_CONTINUE,
    KEYWORD_TRUE,
    KEYWORD_FALSE,
    KEYWORD_SWITCH,
    KEYWORD_WHEN,
    KEYWORD_DEFAULT,
    KEYWORD_AND,
    KEYWORD_OR,
    KEYWORD_NOT,
    KEYWORD_JUMP
    //TODO: complete the implementation of the token_class enum
};

struct _token_t{
    token_class_t t;
    char* value;
    int line_no;
};

typedef struct _token_t token_t;
#endif