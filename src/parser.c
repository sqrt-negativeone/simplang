#include "parser/parser.h"
#include "lexer/token.h"
#include "lexer/lexer.h"
#include "errors/error.h"

#include <string.h>

ast_t* program(){
    get_next_token();
    return decl_list();
}

ast_t* decl_list(){
    ast_t* ast = NULL;
    if (current_token.type == EOFF) return ast;
    ast = decl();
    insert_ast_stmt(ast, decl_list());
    return ast;
}
ast_t* decl(){
    switch (current_token.type)
    {
    case KEYWORD_TYPE:
        return type_decl();
    case KEYWORD_FNC:
        return fnc_decl();
    case KEYWORD_LET:
        get_next_token();
        return var_decl();
    default:
        error();
    }
    return NULL;
}

ast_t* var_decl(){
    var_dec_data_t data;
    var_decl_id(&data);
    if (current_token.type != DELIMETER_COLON) error();
    get_next_token();
    switch (current_token.type)
    {
    case KEYWORD_INT:
        data.type = "int";
        get_next_token();
        break;
    case KEYWORD_FLOAT:
        data.type = "float";
        get_next_token();
        break;
    case KEYWORD_STR:
        data.type = "str";
        get_next_token();
        break;
    case KEYWORD_CHR:
        data.type = "chr";
        get_next_token();
        break;
    case KEYWORD_BOOL:
        data.type = "bool";
        get_next_token();
        break;
    case IDENTIFIER:
        data.type = current_token.value;
        get_next_token();
        break;
    default:
        error();
        break;
    }
    ast_t* ast_var_dec = create_ast_stmt_var_dec(data , NULL);
    var_decl_tail(ast_var_dec);
    return ast_var_dec;
}

void var_decl_id(var_dec_data_t* data){
    if (current_token.type != IDENTIFIER) error();
    data->name = current_token.value;
    get_next_token();
    var_decl_id_aux(data);
}

void var_decl_id_aux(var_dec_data_t* data){
    if (current_token.type != DELIMETER_LEFT_BRACKET) return;
    get_next_token();
    if (current_token.type != NUMBER_CONST) error();
    data->is_array = true;
    data->size = atoi(current_token.value);
    get_next_token();
    if (current_token.type != DELIMETER_RIGHT_BRACKET) error();
    get_next_token();
}
void var_decl_tail(ast_t* ast_var_dec){
    if (current_token.type == DELIMETER_SEMICOLON) {
        get_next_token();
        return;
    }
    if (current_token.type == DELIMETER_ASSIGN){
        get_next_token();
        ast_var_dec->data->stmt.data->var_dec.declaration = &simple_exp()->data->exp;
        if (current_token.type != DELIMETER_SEMICOLON) error();
        get_next_token();
    }
    else error();
}

ast_t* type_decl(){
    ast_t* ast_node = create_ast_stmt_type_dec("", NULL);
    if (current_token.type != KEYWORD_TYPE) error();
    get_next_token();
    if (current_token.type != IDENTIFIER) error();
    ast_node->data->stmt.data->type_dec.name = current_token.value;
    get_next_token();
    if (current_token.type != DELIMETER_CURL_OPEN_PAR) error();
    get_next_token();
    fields_list* fields = field_dec();
    fields->next = field_dec_list();
    if (current_token.type != DELIMETER_CURL_CLOS_PAR) error();
    get_next_token();
    if (current_token.type != DELIMETER_SEMICOLON) error();
    get_next_token();
    ast_node->data->stmt.data->type_dec.fields = fields;
    return ast_node;
}
fields_list* field_dec(){
    var_dec_data_t data;
    var_decl_id(&data);
    if (current_token.type != DELIMETER_COLON) error();
    get_next_token();
    switch (current_token.type)
    {
    case KEYWORD_INT:
        data.type = "int";
        get_next_token();
        break;
    case KEYWORD_FLOAT:
        data.type = "float";
        get_next_token();
        break;
    case KEYWORD_STR:
        data.type = "str";
        get_next_token();
        break;
    case KEYWORD_CHR:
        data.type = "chr";
        get_next_token();
        break;
    case KEYWORD_BOOL:
        data.type = "bool";
        get_next_token();
        break;
    case IDENTIFIER:
        data.type= current_token.value;
        get_next_token();
        break;
    default:
        error();
        break;
    }
    if (current_token.type != DELIMETER_SEMICOLON) error();
    get_next_token();
    fields_list* field = create_field_lists_node(data);
    return field;
}

fields_list* field_dec_list(){
    if (current_token.type == DELIMETER_CURL_CLOS_PAR) return NULL;
    fields_list* root = field_dec();
    root->next = field_dec_list();
    return root;
}


ast_t* fnc_decl(){
    if (current_token.type != KEYWORD_FNC) error();
    get_next_token();
    if (current_token.type != IDENTIFIER) error();
    char* name = current_token.value;
    get_next_token();
    if (current_token.type != DELIMETER_OPEN_PAR) error();
    get_next_token();
    param_list* params = fnc_args();
    if (current_token.type != DELIMETER_CLOS_PAR) error();
    get_next_token();
    if (current_token.type != DELIMETER_COLON) error();
    get_next_token();
    char* return_type = fnc_type_spec();
    ast_t* body = stmt();
    return create_ast_stmt_fnc_dec(name,params,return_type, &body->data->stmt);
}

char* fnc_type_spec(){
    if (current_token.type == KEYWORD_VOID){
        get_next_token();
        return "void";
    }
    else {
        char* data;
        switch (current_token.type)
        {
        case KEYWORD_INT:
            data = "int";
            get_next_token();
            break;
        case KEYWORD_FLOAT:
            data = "float";
            get_next_token();
            break;
        case KEYWORD_STR:
            data = "str";
            get_next_token();
            break;
        case KEYWORD_CHR:
            data = "chr";
            get_next_token();
            break;
        case KEYWORD_BOOL:
            data = "bool";
            get_next_token();
            break;
        case IDENTIFIER:
            data = current_token.value;
            get_next_token();
            break;
        default:
            error();
            break;
        }
        return data;
    }
}

param_list* fnc_args(){
    switch (current_token.type)
    {
    case IDENTIFIER:
        return fnc_args_list();
        break;
    case KEYWORD_VOID:
        get_next_token();
        return NULL;
    default:
        return NULL;
    }
}
param_list* fnc_args_list(){
    param_list* root = fnc_arg();
    root->next = fnc_args_list_aux();
    return root;
}

param_list* fnc_args_list_aux(){
    if (current_token.type != DELIMETER_COMMA) return NULL;
    get_next_token();
    param_list* node = fnc_arg();
    node->next = fnc_args_list_aux();
    return node;
}

param_list* fnc_arg(){
    var_dec_data_t data;
    arg_id(&data);
    if (current_token.type != DELIMETER_SEMICOLON) error();
    get_next_token();
    switch (current_token.type)
    {
    case KEYWORD_INT:
        data.type = "int";
        get_next_token();
        break;
    case KEYWORD_FLOAT:
        data.type = "float";
        get_next_token();
        break;
    case KEYWORD_STR:
        data.type = "str";
        get_next_token();
        break;
    case KEYWORD_CHR:
        data.type = "chr";
        get_next_token();
        break;
    case KEYWORD_BOOL:
        data.type = "bool";
        get_next_token();
        break;
    case IDENTIFIER:
        data.type = current_token.value;
        get_next_token();
        break;
    default:
        error();
        break;
    }
    return create_param_list_node(data);
}
void arg_id(var_dec_data_t* data){
    if (current_token.type != IDENTIFIER) error();
    data->name = current_token.value;
    get_next_token();
    arg_id_tail(data);
}
void arg_id_tail(var_dec_data_t* data){
    if (current_token.type != DELIMETER_LEFT_BRACKET) return;
    data->is_array = true;
    data->size = 0;
    get_next_token();
    if (current_token.type != DELIMETER_RIGHT_BRACKET) error();
}
ast_t* stmt(){
    switch (current_token.type)
    {
    case KEYWORD_IF:
        return if_stmt();
    case KEYWORD_FOR:
    case KEYWORD_WHILE:
        return loop_stmt();
    case KEYWORD_SWITCH:
        return switch_stmt();
    case KEYWORD_RETURN:
        return return_stmt();
    case KEYWORD_BREAK:
        return break_stmt();
    case KEYWORD_CONTINUE:
        return continue_stmt();
    case DELIMETER_CURL_OPEN_PAR:
        return complex_stmt();
    default:
        return exp_stmt();
    }
}
ast_t* exp_stmt(){
    if (current_token.type != DELIMETER_SEMICOLON) {
        ast_t* exp_stmt = create_ast_stmt_exp(&exp_()->data->exp);
        if (current_token.type != DELIMETER_SEMICOLON) error();
        get_next_token();
        return exp_stmt;
    }
    else {
        get_next_token();
        return create_ast_stmt_empty();
    }
}
ast_t* complex_stmt(){
    if (current_token.type != DELIMETER_CURL_OPEN_PAR) error();
    get_next_token();
    ast_t* ast_stmt = NULL;
    if (current_token.type == KEYWORD_LET){
        get_next_token();
        ast_stmt = var_decl();
    }
    ast_t* stmt_next = stmt_list();
    if (ast_stmt == NULL){
        ast_stmt = stmt_next;
    }
    else{
        insert_ast_stmt(ast_stmt, stmt_next);
    }
    if (current_token.type != DELIMETER_CURL_CLOS_PAR) error();
    get_next_token();
    return ast_stmt;
}
ast_t* stmt_list(){
    // if the current token is in the FOLLOW of the stmt_list
    if (current_token.type == DELIMETER_CURL_CLOS_PAR) return NULL;
    ast_t* ast_stmt = stmt();
    insert_ast_stmt(ast_stmt, stmt_list());
    return ast_stmt;
}

ast_t* if_stmt(){
    if (current_token.type != KEYWORD_IF) error();
    get_next_token();
    ast_t* condition = simple_exp();
    if (current_token.type != DELIMETER_CURL_OPEN_PAR) error();
    get_next_token();
    ast_t* body = stmt();
    if (current_token.type != DELIMETER_CURL_CLOS_PAR) error();
    get_next_token();
    ast_t* else_body = else_if_stmt();
    return create_ast_stmt_if(&condition->data->exp, &body->data->stmt, &else_body->data->stmt);
}

ast_t* else_if_stmt(){
    if (current_token.type != KEYWORD_ELSE) return NULL;
    get_next_token();
    return else_aux_stmt();
}
ast_t* else_aux_stmt(){
    if (current_token.type == DELIMETER_CURL_OPEN_PAR){
        get_next_token();
        ast_t* body = stmt();
        if (current_token.type != DELIMETER_CURL_CLOS_PAR) error();
        get_next_token();
        return body;
    }
    else return if_stmt();
}
ast_t* loop_stmt(){
    if (current_token.type == KEYWORD_FOR) return for_stmt();
    else if (current_token.type == KEYWORD_WHILE) return while_stmt();
    else error();
    return NULL;
}
ast_t* for_stmt(){
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

ast_t* while_stmt(){
    get_next_token();
    simple_exp();
    if (current_token.type != DELIMETER_CURL_OPEN_PAR) error();
    stmt();
    if (current_token.type != DELIMETER_CURL_CLOS_PAR) error();
    get_next_token();
}

for_range_t range(){
    if (current_token.type == DELIMETER_COLON){
        get_next_token();
        ast_t* begin = simple_exp();
        if (current_token.type != KEYWORD_TO) error();
        get_next_token();
        ast_t* end = simple_exp();
        ast_t* jump = range_tail();

        return create_for_range(
                &begin->data->exp, 
                &end->data->exp,
                ((jump == NULL)? NULL : (&jump->data->exp))
            );
    }
    else error();
}
ast_t* range_tail(){
    if (current_token.type != KEYWORD_JUMP) return NULL;
    get_next_token();
    return simple_exp();
}

ast_t* return_stmt(){
    get_next_token();
    return return_stmt_tail();
}
ast_t* return_stmt_tail(){
    if (current_token.type == DELIMETER_SEMICOLON){
        get_next_token();
        return create_ast_stmt_return_stmt(NULL);
    }
    else {
        ast_t* ast_stmt = exp_();
        if (current_token.type != DELIMETER_SEMICOLON) error();
        get_next_token();
        return create_ast_stmt_return_stmt(&ast_stmt->data->exp);
    }
}
ast_t* break_stmt(){
    get_next_token();
    if (current_token.type != DELIMETER_SEMICOLON) error();
    get_next_token();
    return create_ast_stmt_break_continue_stmt(true);
}

ast_t* continue_stmt(){
    get_next_token();
    if (current_token.type != DELIMETER_SEMICOLON) error();
    get_next_token();
    return create_ast_stmt_break_continue_stmt(false);
}
ast_t* switch_stmt(){
    get_next_token();
    ast_t* item = simple_exp();
    if (current_token.type != DELIMETER_CURL_OPEN_PAR) error();
    when_part_list* when_lit = when_part();
    ast_t* ast_default_part = default_part();
    if (current_token.type != DELIMETER_CURL_CLOS_PAR) error();
    return create_ast_stmt_switch(&item->data->exp,when_lit, &ast_default_part->data->stmt);
}
when_part_list* when_part(){
    if (current_token.type != KEYWORD_WHEN) return NULL;
    get_next_token();
    ast_t* expression = simple_exp();
    if (current_token.type != DELIMETER_COLON) error();
    get_next_token();
    ast_t* body = stmt();
    when_part_list* when_list = create_when_part_list(&expression->data->exp, &body->data->stmt);
    when_list->next = when_part();
    return when_list;
}
ast_t* default_part(){
    if (current_token.type != KEYWORD_DEFAULT) return create_ast_stmt_empty();
    get_next_token();
    return stmt();
}

ast_t* exp_(){
    return simple_exp();
}

ast_t* simple_exp(){
    ast_t* ast_exp = and_exp();
    ast_t* tail_exp = simple_exp_aux();
    if (tail_exp == NULL){
        return ast_exp;
    }
    else {
        return create_ast_exp_operation(OR_OPERATION, &ast_exp->data->exp, &tail_exp->data->exp);
    }
}

ast_t* simple_exp_aux(){
    if (current_token.type != KEYWORD_OR) return NULL;
    get_next_token();
    return simple_exp();
}

ast_t* and_exp(){
    ast_t* ast_exp = unary_rel_exp();
    ast_t* tail_exp = and_exp_aux();
    if (tail_exp == NULL) return ast_exp;
    else {
        return create_ast_exp_operation(AND_OPERATION, &ast_exp->data->exp, &tail_exp->data->exp);
    }
}
ast_t* and_exp_aux(){
    if (current_token.type != KEYWORD_AND) return NULL;
    get_next_token();
    return and_exp();
}
ast_t* unary_rel_exp(){
    if (current_token.type == KEYWORD_NOT){
        get_next_token();
        ast_t* ast_exp = unary_rel_exp();
        return create_ast_exp_operation(NOT_OPERATION, NULL, &ast_exp->data->exp);
    }
    else return rel_exp();
}
ast_t* rel_exp(){
    ast_t* ast_exp = sum_exp();
    ast_t* tail_exp = NULL;

    switch (current_token.type)
    {
    case DELIMETER_LESS_EQ:
        get_next_token();
        return create_ast_exp_operation(LESS_EQ_OPERATION, &ast_exp->data->exp, &rel_exp()->data->exp);
    case DELIMETER_LESS:
        get_next_token();
        return create_ast_exp_operation(LESS_OPERATION, &ast_exp->data->exp, &rel_exp()->data->exp);
    case DELIMETER_GREATER:
        get_next_token();
        return create_ast_exp_operation(GREATER_OPERATION, &ast_exp->data->exp, &rel_exp()->data->exp);
    case DELIMETER_GREATER_EQ:
        get_next_token();
        return create_ast_exp_operation(GREATER_EQ_OPERATION, &ast_exp->data->exp, &rel_exp()->data->exp);
    case DELIMETER_EQUAL:
        get_next_token();
        return create_ast_exp_operation(EQUAL_OPERATION, &ast_exp->data->exp, &rel_exp()->data->exp);
    case DELEMTER_NOT_EQUAL:
        get_next_token();
        return create_ast_exp_operation(DIFF_OPERATION, &ast_exp->data->exp, &rel_exp()->data->exp);
        break;
    default:
        return ast_exp;
    }
}
ast_t* sum_exp(){
    ast_t* ast_exp = mult_exp();
    if (current_token.type == DELIMETER_PLUS){
        get_next_token();
        return create_ast_exp_operation(PLUS_OPERATION, &ast_exp->data->exp, &sum_exp()->data->exp);
    }
    else if (current_token.type == DELIMETER_MINUS){
        get_next_token();
        return create_ast_exp_operation(MINUS_OPERAION, &ast_exp->data->exp, &sum_exp()->data->exp);
    }
    else return ast_exp;
}
ast_t* mult_exp(){
    ast_t* ast_exp = unary_exp();
    if (current_token.type == DELIMETER_STAR){
        get_next_token();
        return create_ast_exp_operation(MULT_OPERATION, &ast_exp->data->exp, &mult_exp()->data->exp);
    }
    else if (current_token.type == DELIMETER_SLASH){
        get_next_token();
        return create_ast_exp_operation(DIV_OPERATION, &ast_exp->data->exp, &mult_exp()->data->exp);
    }
    else if (current_token.type == DELIMETER_PERCENTAGE){
        get_next_token();
        return create_ast_exp_operation(REMINDER_OPERATOR, &ast_exp->data->exp, &mult_exp()->data->exp);
    }
    else return ast_exp;
}

ast_t* unary_exp(){
    if (current_token.type == DELIMETER_PLUS){
        get_next_token();
        return create_ast_exp_operation(PLUS_OPERATION, NULL, &unary_exp()->data->exp);
    }
    else if (current_token.type == DELIMETER_MINUS){
        get_next_token();
        return create_ast_exp_operation(MINUS_OPERAION, NULL, &unary_exp()->data->exp);
    }
    else return assign_exp();
}
ast_t* assign_exp(){
    ast_t* ast_fact = fact();
    switch (current_token.type)
    {
    case DELIMETER_ASSIGN:
        get_next_token();
        return create_ast_exp_assign(NORMAL_ASSIGN, &ast_fact->data->exp, &exp_()->data->exp);
    case DELIMETER_PLUS_EQ:
        get_next_token();
        return create_ast_exp_assign(ADD_ASSIGN, &ast_fact->data->exp, &exp_()->data->exp);
    case DELIMETER_MINUS_EQ:
        get_next_token();
        return create_ast_exp_assign(SUB_ASSIGN, &ast_fact->data->exp, &exp_()->data->exp);
    case DELIMETER_MULT_EQ:
        get_next_token();
        return create_ast_exp_assign(MULT_ASSIGN, &ast_fact->data->exp, &exp_()->data->exp);
    case DELIMETER_DIVIDE_EQ:
        get_next_token();
        return create_ast_exp_assign(DIV_ASSIGN, &ast_fact->data->exp, &exp_()->data->exp);
    
    default:
        return ast_fact;
    }
}
ast_t* fact(){
    if (current_token.type == DELIMETER_OPEN_PAR){
        get_next_token();
        ast_t* ast_exp =  exp_();
        if (current_token.type != DELIMETER_CLOS_PAR) error();
        get_next_token();
        return ast_exp;
    }
    else if (current_token.type == IDENTIFIER || current_token.type == KEYWORD_PUT || current_token.type == KEYWORD_GET){
        char* name = current_token.value;
        get_next_token();
        ast_t* next = post_id();
        if (next == NULL) return create_ast_exp_member_access(name, NULL);
        switch (next->data->exp.type)
        {
        case MEMBER_ACCESS:
            return create_ast_exp_member_access(name, &next->data->exp.data->member_acces);
        case ARRAY_ACCESS:
            return create_ast_exp_array_access(name, &next->data->exp);
        case FNC_CALL_EXP:
            next->data->exp.data->fnc_call.id = name;
            return next;
        default:
            sem_err();
        }
    }
    else return const_();
}
ast_t* post_id(){
    switch (current_token.type)
    {
    case DELIMETER_OPEN_PAR:{
        arg_list* args = call();
        return create_ast_exp_fnc_call("", args);
    }
    case DELIMETER_LEFT_BRACKET:{
        get_next_token();
        ast_t* ast_exp = exp_();
        if (current_token.type != DELIMETER_RIGHT_BRACKET) error();
        get_next_token();
        return create_ast_exp_array_access("", &ast_exp->data->exp);
    }
    case DELIMETER_DOT:{
        get_next_token();
        if (current_token.type != IDENTIFIER) error();
        char* id; id = current_token.value;
        get_next_token();
        ast_t* ast_exp = post_id();
        if (ast_exp == NULL) return create_ast_exp_member_access(id, NULL);
        if (ast_exp->data->exp.type != MEMBER_ACCESS) sem_err();
        return create_ast_exp_member_access(id, &ast_exp->data->exp.data->member_acces);
    }
    default:
        return NULL;
    }
}
arg_list* call(){
    get_next_token();
    arg_list* args = args_call();
    if (current_token.type != DELIMETER_CLOS_PAR) error();
    get_next_token();
    return args;
}
arg_list* args_call(){
    if (current_token.type == DELIMETER_CLOS_PAR) return NULL;
    ast_t* ast_exp = exp_();
    return create_arg_list_node(&ast_exp->data->exp, args_call_list());
}
arg_list* args_call_list(){
    if (current_token.type != DELIMETER_COMMA) return NULL;
    get_next_token();
    return args_call();
}
ast_t* const_(){
    switch (current_token.type)
    {
    case CHR_LITERAL:{
        char* value; value = current_token.value;
        get_next_token();
        return create_ast_exp_const(CHR_CONST_EXP, value);
    }
    case STR_LITERAL:{
        char* value; value = current_token.value;
        get_next_token();
        return create_ast_exp_const(STR_CONST_EXP, value);
    }
    case NUMBER_CONST:{
        char* value; value = current_token.value;
        get_next_token();
        return create_ast_exp_const(INT_CONST_EXP, value);
    }
    case FLOAT_CONST:{
        char* value; value = current_token.value;
        get_next_token();
        return create_ast_exp_const(FLOAT_CONST_EXP, value);
    }
    case BOOL_TRUE:{
        char* value; value = current_token.value;
        get_next_token();
        return create_ast_exp_const(TRUE_CONST_EXP, value);
    }
    case BOOL_FALSE:{
        char* value; value = current_token.value;
        get_next_token();
        return create_ast_exp_const(FALSE_CONST_EXP, value);
    }
    default:
        error();
    }
    return NULL;
}