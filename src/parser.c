#include "parser/parser.h"
#include "lexer/token.h"
#include "lexer/lexer.h"
#include "errors/error.h"

void program(){
    get_next_token();
    decl_list();
}

void decl_list(){
    if (current_token.type == EOFF) return;
    decl();
    decl_list();
}
void decl(){
    switch (current_token.type)
    {
    case KEYWORD_TYPE:
        type_decl();
        break;
    case KEYWORD_FNC:
        fnc_decl();
        break;
    case IDENTIFIER:
        var_decl();
        break;
    default:
        error();
    }
}

void var_decl(){
    var_decl_id();
    if (current_token.type != DELIMETER_COLON) error();
    get_next_token();
    type_spec();
    var_decl_tail();
}

void var_decl_id(){
    if (current_token.type != IDENTIFIER) error();
    get_next_token();
    var_decl_id_aux();
}

void var_decl_id_aux(){
    if (current_token.type != DELIMETER_LEFT_BRACKET) return;
    get_next_token();
    if (current_token.type != NUMBER_CONST) error();
    get_next_token();
    if (current_token.type != DELIMETER_RIGHT_BRACKET) error();
    get_next_token();
}
void var_decl_tail(){
    if (current_token.type == DELIMETER_SEMICOLON) {
        get_next_token();
        return;
    }
    if (current_token.type == DELIMETER_ASSIGN){
        get_next_token();
        simple_exp();
        if (current_token.type != DELIMETER_SEMICOLON) error();
        get_next_token();
    }
    else error();
}

void type_spec(){
    switch (current_token.type)
    {
    case NUMBER_CONST:
    case FLOAT_CONST:
    case CHR_LITERAL:
    case STR_LITERAL:
    case BOOL_FALSE:
    case BOOL_TRUE:
    case IDENTIFIER:
        get_next_token();
        break;
    default:
        error();
        break;
    }
}

void typedec(){
    if (current_token.type != KEYWORD_TYPE) error();
    get_next_token();
    if (current_token.type != IDENTIFIER) error();
    get_next_token();
    if (current_token.type != DELIMETER_CURL_OPEN_PAR) error();
    get_next_token();
    var_decl();
    var_decl_list();
    if (current_token.type != DELIMETER_CURL_CLOS_PAR) error();
    get_next_token();
    if (current_token.type != DELIMETER_SEMICOLON) error();
    get_next_token();
}
void var_decl_list(){
    if (current_token.type != IDENTIFIER) return;
    var_decl();
    var_decl_list();
}

void fnc_decl(){
    if (current_token.type != KEYWORD_FNC) error();
    get_next_token();
    if (current_token.type != IDENTIFIER) error();
    get_next_token();
    if (current_token.type != DELIMETER_OPEN_PAR) error();
    get_next_token();
    fnc_args();
    if (current_token.type != DELIMETER_CLOS_PAR) error();
    get_next_token();
    if (current_token.type != DELIMETER_COLON) error();
    get_next_token();
    fnc_type_spec();
    stmt();
}

void fnc_type_spec(){
    if (current_token.type == KEYWORD_VOID){
        get_next_token();
        return;
    }
    else type_spec();
}

void fnc_args(){
    switch (current_token.type)
    {
    case IDENTIFIER:
        fnc_args_list();
        break;
    case KEYWORD_VOID:
        get_next_token();
        return;
    default:
        break;
    }
}
void fnc_args_list(){
    fnc_arg();
    fnc_args_list_aux();
}

void fnc_args_list_aux(){
    if (current_token.type != DELIMETER_COMMA) return;
    get_next_token();
    fnc_arg();
    fnc_args_list_aux();
}

void fnc_arg(){
    arg_id();
    if (current_token.type != DELIMETER_SEMICOLON) error();
    get_next_token();
    type_spec();
}
void arg_id(){
    if (current_token.type != IDENTIFIER) error();
    get_next_token();
    arg_id_tail();
}
void arg_id_tail(){
    if (current_token.type != DELIMETER_LEFT_BRACKET) return;
    get_next_token();
    if (current_token.type != DELIMETER_RIGHT_BRACKET) error();
}
void stmt(){
    switch (current_token.type)
    {
    case KEYWORD_IF:
        if_stmt();
        break;
    case KEYWORD_FOR:
    case KEYWORD_WHILE:
        loop_stmt();
        break;
    case KEYWORD_SWITCH:
        switch_stmt();
        break;
    case KEYWORD_RETURN:
        return_stmt();
        break;
    case KEYWORD_BREAK:
        break_stmt();
        break;
    case KEYWORD_CONTINUE:
        continue_stmt();
        break;
    case DELIMETER_CURL_OPEN_PAR:
        complex_stmt();
        break;
    default:
        exp_stmt();
        break;
    }
}
void exp_stmt(){
    if (current_token.type != DELIMETER_SEMICOLON) exp();
    else get_next_token();
}
void complex_stmt(){
    if (current_token.type != DELIMETER_CURL_OPEN_PAR) error();
    get_next_token();
    var_decl();
    stmt_list();
    if (current_token.type != DELIMETER_CURL_CLOS_PAR) error();
    get_next_token();
}
void stmt_list(){
    // if the current token is in the FOLLOW of the stmt_list
    if (current_token.type == DELIMETER_CURL_CLOS_PAR) return;
    stmt();
    stmt_list();
}

void if_stmt(){
    if (current_token.type != KEYWORD_IF) error();
    get_next_token();
    simple_exp();
    if (current_token.type != DELIMETER_CURL_OPEN_PAR) error();
    stmt();
    if (current_token.type != DELIMETER_CURL_CLOS_PAR) error();
    get_next_token();
    else_if_stmt();
}

void else_if_stmt(){
    if (current_token.type != KEYWORD_ELSE) return;
    get_next_token();
    else_aux_stmt();
}
void else_aux_stmt(){
    if (current_token.type == DELIMETER_CURL_OPEN_PAR){
        get_next_token();
        stmt();
        if (current_token.type != DELIMETER_CURL_CLOS_PAR) error();
        get_next_token();
    }
    else if_stmt();
}
void loop_stmt(){
    if (current_token.type == KEYWORD_FOR) for_stmt();
    else if (current_token.type == KEYWORD_WHILE) while_stmt();
    else error();
}
void for_stmt(){
    get_next_token();
    if (current_token.type != IDENTIFIER) error();
    get_next_token();
    range();
    if (current_token.type != DELIMETER_CURL_OPEN_PAR) error();
    get_next_token();
    stmt();
    if (current_token.type != DELIMETER_CURL_CLOS_PAR) error();
    get_next_token();
}

void while_stmt(){
    get_next_token();
    simple_exp();
    if (current_token.type != DELIMETER_CURL_OPEN_PAR) error();
    stmt();
    if (current_token.type != DELIMETER_CURL_CLOS_PAR) error();
    get_next_token();
}

void range(){
    if (current_token.type == DELIMETER_COLON){
        get_next_token();
        simple_exp();
        if (current_token.type != KEYWORD_TO) error();
        get_next_token();
        simple_exp();
        range_tail();
    }
    else if (current_token.type == KEYWORD_IN){
        get_next_token();
        simple_exp();
    }
    else error();
}
void range_tail(){
    if (current_token.type != KEYWORD_JUMP) return;
    get_next_token();
    simple_exp();
}

void return_stmt(){
    get_next_token();
    return_stmt_tail();
}
void return_stmt_tail(){
    if (current_token.type == DELIMETER_SEMICOLON) get_next_token();
    else {
        exp();
        if (current_token.type != DELIMETER_SEMICOLON) error();
    }
}
void break_stmt(){
    get_next_token();
    if (current_token.type != DELIMETER_SEMICOLON) error();
}

void continue_stmt(){
    get_next_token();
    if (current_token.type != DELIMETER_SEMICOLON) error();
}
void switch_stmt(){
    get_next_token();
    simple_exp();
    if (current_token.type != DELIMETER_CURL_OPEN_PAR) error();
    when_part();
    default_part();
    if (current_token.type != DELIMETER_CURL_CLOS_PAR) error();
}
void when_part(){
    if (current_token.type != KEYWORD_WHEN) return;
    get_next_token();
    simple_exp();
    if (current_token.type != DELIMETER_COLON) error();
    get_next_token();
    stmt();
    when_part();
}
void default_part(){
    if (current_token.type != KEYWORD_DEFAULT) return;
    get_next_token();
    stmt();
}

void exp(){
    simple_exp();
}

void simple_exp(){
    and_exp();
    simple_exp_aux();
}

void simple_exp_aux(){
    if (current_token.type != KEYWORD_OR) return;
    get_next_token();
    and_exp();
    simple_exp_aux();
}

void and_exp(){
    unary_rel_exp();
    and_exp_aux();
}
void and_exp_aux(){
    if (current_token.type != KEYWORD_AND) return;
    get_next_token();
    unary_rel_exp();
    and_exp_aux();
}
void unary_rel_exp(){
    if (current_token.type == KEYWORD_NOT){
        get_next_token();
        unary_rel_exp();
    }
    else rel_exp();
}
void rel_exp(){
    sum_exp();
    rel_exp_tail();
}
void rel_exp_tail(){
    switch (current_token.type)
    {
    case DELIMETER_LESS_EQ:
    case DELIMETER_LESS:
    case DELIMETER_GREATER:
    case DELIMETER_GREATER_EQ:
    case DELIMETER_EQUAL:
    case DELEMTER_NOT_EQUAL:
        get_next_token();
        sum_exp();
        rel_exp_tail();
        break;
    
    default:
        return;
    }
}
void sum_exp(){
    mult_exp();
    sum_exp_aux();
}
void sum_exp_aux(){
    if (current_token.type != DELIMETER_PLUS && current_token.type != DELIMETER_MINUS ) return;
    get_next_token();
    mult_exp();
    sum_exp_aux();
}
void mult_exp(){
    unary_exp();
    mult_exp_aux();
}
void mult_exp_aux(){
    if (current_token.type != DELIMETER_STAR &&
        current_token.type != DELIMETER_SLASH &&
        current_token.type != DELIMETER_PERCENTAGE
    ) return;
    get_next_token();
    mult_exp();
}

void unary_exp(){
    if (current_token.type != DELIMETER_PLUS &&
        current_token.type != DELIMETER_MINUS &&
        current_token.type != DELIMETER_QUESTION_MARK
    ) fact();
    else{
        get_next_token();
        unary_exp();
    }
}
void fact(){
    if (current_token.type == DELIMETER_OPEN_PAR){
        get_next_token();
        exp();
        if (current_token.type != DELIMETER_CLOS_PAR) error();
        get_next_token();
    }
    else if (current_token.type == IDENTIFIER){
        get_next_token();
        post_id();
    }
    else const_();
}
void post_id(){
    switch (current_token.type)
    {
    case DELIMETER_OPEN_PAR:
        call();
        break;
    case DELIMETER_LEFT_BRACKET:
        get_next_token();
        exp();
        if (current_token.type != DELIMETER_RIGHT_BRACKET) error();
        get_next_token();
        break;
    case DELIMETER_DOT:
        get_next_token();
        if (current_token.type != IDENTIFIER) error();
        get_next_token();
        post_id();
        break;
    default:
        return;
    }
}
void call(){
    get_next_token();
    args_call();
    if (current_token.type != DELIMETER_CLOS_PAR) error();
    get_next_token();
}
void args_call(){
    if (current_token.type == DELIMETER_CLOS_PAR) return;
    args_call_list();
}
void args_call_list(){
    exp();
    args_call_list_aux();
}

void args_call_list_aux(){
    if (current_token.type != DELIMETER_COMMA) return;
    get_next_token();
    args_call_list();
}
void const_(){
    if (current_token.type == CHR_LITERAL ||
        current_token.type == STR_LITERAL ||
        current_token.type == NUMBER_CONST ||
        current_token.type == FLOAT_CONST ||
        current_token.type == BOOL_TRUE ||
        current_token.type == BOOL_FALSE
    ){
        get_next_token();
        return;
    }
    error();
}