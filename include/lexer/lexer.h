#ifndef LEXER_H
#define LEXER_H

#include "token.h"

// driver function to get next tokens from text
//when called, it loads the current_token variable with the information of the next token in input file
extern void get_next_token();

//placeholder of all the necessary information about the current token.
extern token_t current_token;
#endif