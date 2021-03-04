#ifndef LEXER_H
#define LEXER_H

#include "token.h"

// driver function to get next tokens from text
extern token_t get_next_token();

//placeholder of all the necessary information about the current token.
extern token_t current_token;

#endif