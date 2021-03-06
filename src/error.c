#include "errors/error.h"
#include "lexer/lexer.h"
#include <stdio.h>

void error(){
    printf("syntax error at line %d\ntoken : %s\n", current_token.line_no, current_token.value);
    exit(1);
}


void sem_err(){
    //TODO: provide more informations
    printf("semantics error\n");
    exit(1);
}