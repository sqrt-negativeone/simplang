#ifndef LEXER_H
#define LEXER_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "token.h"

// driver function to get next tokens from text
//when called, it leads the current_token variable with the information of the next token in input file
extern void get_next_token();

//placeholder of all the necessary information about the current token.
extern token_t current_token;

typedef enum {
    EOFF,
    ERRONEOUS,
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
    KEYWORD_JUMP,
    DELIMETER_COLON,
    DELIMETER_SEMICOLON,
    DELIMETER_OPEN_PAR,
    DELIMETER_CLOS_PAR,
    DELIMETER_CURL_OPEN_PAR,
    DELIMETER_CURL_CLOS_PAR,
    DELIMETER_PLUS,
    DELIMETER_MINUS,
    DELIMETER_STAR,
    DELIMETER_PERCENTAGE,
    DELIMETER_ASSIGN,
    DELIMETER_LESS,
    DELIMETER_LESS_EQ,
    DELIMETER_GREATER,
    DELIMETER_GREATER_EQ,
    DELIMETER_EQUAL,
    DELIMETER_NOT_EQUAL,
    DELIMETER_DIVIDE_EQ,
    DELIMETER_MULT_EQ,
    DELIMETER_PLUS_EQ,
    DELIMETER_MINUS_EQ,
    DELIMETER_COMMA,
    DELIMETER_DOT,
    DELIMETER_LEFT_BRACKET,
    DELIMETER_RIGHT_BRACKET,
    DELIMETER_UNDERSCORE,
    DELEMTER_NOT_EQUAL,
    DELIMETER_SLASH,
    DELIMETER_QUESTION_MARK,
    KEYWORD_VOID,
    COMMENT,
    IDENTIFIER,
    CHR_LITERAL,
    STR_LITERAL,
    BOOL_TRUE,
    BOOL_FALSE,
    NUMBER_CONST,
    FLOAT_CONST
}CODE_LEX;

//char* nom = calloc(1028,sizeof(char));
typedef struct {
	CODE_LEX CODE;
	char nom[20];
}TcurrentSymbole;

//Déclaration Variable Globale
TcurrentSymbole currentSymbole;
char currentCaractere;
char Car_suivant;
FILE* file;
FILE* fileprint;
int fl=0;

#endif