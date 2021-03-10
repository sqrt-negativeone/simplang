#include "errors/error.h"
#include "lexer/lexer.h"
#include <stdio.h>

void error(const char* expected){
    printf("syntax error at line %d\nexpected : \" %s \"\nfound :%s\n", current_token.line_no,expected, current_token.value);
    exit(1);
}


void sem_err(){
    //TODO: provide more informations
    printf("semantics error\n");
    exit(1);
}