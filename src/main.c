#include <stdio.h>
#include "lexer/lexer.h"
#include "parser/parser.h"
extern char* source;

int main(int argc, char* argv[]) {
    if (argc == 2){
        FILE* file;
        file = fopen(argv[1], "r");
        if (!file) {
            printf("File Not Found!\n");
            return 1;
        }
        size_t size;
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        fseek(file, 0, SEEK_SET);
        source = malloc(size);
        fread(source, 1,size, file);
        printf("%s\n",source);
        init_lexer();
    }
    ast_t* ast = program();
    if (ast != NULL) printf("Program well parsed!\n");
    return 0;
}