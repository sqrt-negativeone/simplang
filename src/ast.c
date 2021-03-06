#include "parser/ast.h"


#define CALLOC(T) (T*) calloc(sizeof(T), 1)

//private functions
static ast_t* get_ast_stmt_node(stmt_type t){
    ast_t* ast = CALLOC(ast_t);
    ast->type = STATEMENT;
    ast->data = CALLOC(ast_data_t);
    ast->data->stmt.type = t;
    ast->data->stmt.data = CALLOC(ast_stmt_data_t);

    return ast;
}
static ast_t* get_ast_exp_node(exp_type t){
    ast_t* ast = CALLOC(ast_t);
    ast->type = EXPRESSION;
    ast->data = CALLOC(ast_data_t);
    ast->data->exp.type = t;
    ast->data->exp.data = CALLOC(ast_exp_data_t);

    return ast;
}

//public functions

//statments utilities
void insert_ast_stmt(ast_t* ast, ast_t* elem){
    if (elem != NULL) ast->data->stmt.next = &elem->data->stmt;
}
ast_t* create_ast_stmt_exp(ast_exp_t* exp){
    ast_t* ast_exp = get_ast_stmt_node(EXP_STMT);

    ast_exp->data->stmt.data->exp = exp;
    
    return ast_exp;
}
ast_t* create_ast_stmt_empty(){
    return get_ast_stmt_node(EMPTY);
}
for_range_t create_for_range(ast_exp_t* begin, ast_exp_t* end, ast_exp_t* jump){
    for_range_t range;
    range.begin = begin;
    range.end = end;
    range.jump = jump;
}
ast_t* create_ast_stmt_for(for_range_t range, ast_stmt_t* body){
    ast_t* ast_for = get_ast_stmt_node(FOR_STMT);

    ast_for->data->stmt.data->for_stmt.range = range;
    ast_for->data->stmt.data->for_stmt.body = body;

    return ast_for;
}

ast_t* create_ast_stmt_while(ast_exp_t* condition, ast_stmt_t* body){
    ast_t* ast_while = get_ast_stmt_node(WHILE_STMT);

    ast_while->data->stmt.data->while_stmt.body = body; 
    ast_while->data->stmt.data->while_stmt.condition = condition; 

    return ast_while;
}

ast_t* create_ast_stmt_if(ast_exp_t* condition, ast_stmt_t* if_body, ast_stmt_t* else_body){
    ast_t* ast_if = get_ast_stmt_node(IF_STMT);

    ast_if->data->stmt.data->if_stmt.condition = condition;
    ast_if->data->stmt.data->if_stmt.if_body = if_body;
    ast_if->data->stmt.data->if_stmt.else_body = else_body;

    return ast_if;
}

ast_t* create_ast_stmt_switch(ast_exp_t* item, when_part_list* when_list, ast_stmt_t* default_part){
    ast_t* ast_switch = get_ast_stmt_node(SWITCH_STMT);

    ast_switch->data->stmt.data->switch_stmt.item = item;
    ast_switch->data->stmt.data->switch_stmt.when_list = when_list;
    ast_switch->data->stmt.data->switch_stmt.default_part = default_part;

    return ast_switch;
}

ast_t* create_ast_stmt_fnc_dec(char* name, param_list* parameters, char* return_type, ast_stmt_t* body){
    ast_t* ast_fnc_dec = get_ast_stmt_node(FNC_DEC_STMT);

    ast_fnc_dec->data->stmt.data->fnc_dec.name = name;
    ast_fnc_dec->data->stmt.data->fnc_dec.parameters = parameters;
    ast_fnc_dec->data->stmt.data->fnc_dec.return_type = return_type;
    ast_fnc_dec->data->stmt.data->fnc_dec.body = body;

    return ast_fnc_dec;
}

ast_t* create_ast_stmt_type_dec(char* name, fields_list* fields){
    ast_t* ast_type_dec = get_ast_stmt_node(TYPE_DEC_STMT);

    ast_type_dec->data->stmt.data->type_dec.name = name;
    ast_type_dec->data->stmt.data->type_dec.fields = fields;

    return ast_type_dec;
}
ast_t* create_ast_stmt_var_dec(var_dec_data_t data, ast_exp_t* declaration){
    ast_t* ast_var_dec = get_ast_stmt_node(VAR_DEC_STMT);

    ast_var_dec->data->stmt.data->var_dec.data = data;
    ast_var_dec->data->stmt.data->var_dec.declaration = declaration;

    return ast_var_dec;
}
ast_t* create_ast_stmt_return_stmt(ast_exp_t* return_exp){
    ast_t* ast_return = get_ast_stmt_node(RETURN_STMT);

    ast_return->data->stmt.data->return_stmt.return_exp = return_exp;

    return ast_return;
}
ast_t* create_ast_stmt_break_continue_stmt(bool is_break){
    ast_t* ast_break_continue = get_ast_stmt_node(BREAK_RETURN_STMT);

    ast_break_continue->data->stmt.data->break_continue_stmt.is_break = is_break;

    return ast_break_continue;
}

//expressions utilities
ast_t* create_ast_exp_const(const_type type, char* value){
    ast_t* ast_const = get_ast_exp_node(CONST_EXP);

    ast_const->data->exp.data->const_type.type = type;
    ast_const->data->exp.data->const_type.value = value;

    return ast_const;
}
ast_t* create_ast_exp_array_access(char* id, ast_exp_t* index){
    ast_t* ast_array_access = get_ast_stmt_node(ARRAY_ACCESS);

    ast_array_access->data->exp.data->array_access.id = id;
    ast_array_access->data->exp.data->array_access.index = index;
}
ast_t* create_ast_exp_assign(assign_type type, ast_exp_t* variable, ast_exp_t* expression){
    ast_t* ast_assign = get_ast_exp_node(ASSING_EXP);

    ast_assign->data->exp.data->assign.type = type;
    ast_assign->data->exp.data->assign.variable = variable;
    ast_assign->data->exp.data->assign.expression = expression;

    return ast_assign;
}
ast_t* create_ast_exp_operation(operation_type operation, ast_exp_t* left, ast_exp_t* right){
    ast_t* ast_operation = get_ast_exp_node(OPERATION_EXP);

    ast_operation->data->exp.data->operation.left = left;
    ast_operation->data->exp.data->operation.operation = operation;
    ast_operation->data->exp.data->operation.right = right;

    return ast_operation;
}
ast_t* create_ast_exp_member_access(char* id, ast_exp_member_access* next){
    ast_t* ast_mem_acc = get_ast_exp_node(MEMBER_ACCESS);

    ast_mem_acc->data->exp.data->member_acces.id = id;
    ast_mem_acc->data->exp.data->member_acces.next = next;

    return ast_mem_acc;
}
ast_t* create_ast_exp_fnc_call(char* id, arg_list* args){
    ast_t* ast_fnc_call = get_ast_exp_node(FNC_CALL_EXP);

    ast_fnc_call->data->exp.data->fnc_call.args = args;
    ast_fnc_call->data->exp.data->fnc_call.id = id;

    return ast_fnc_call;
}

// helper utilities

fields_list* create_field_lists_node(var_dec_data_t data){
    fields_list* field = CALLOC(fields_list);
    field->data = data;
    return field;
}

param_list* create_param_list_node(var_dec_data_t data){
    param_list* param = CALLOC(param_list);
    param->data = data;
    return param;
}

arg_list* create_arg_list_node(ast_exp_t* exp, arg_list* next){
    arg_list* arg = CALLOC(arg_list);
    arg->exp = exp;
    arg->next = next;
    return arg;
}

var_dec_data_t create_var_dec_data(char* name, char* type, bool is_array, int size){
    var_dec_data_t data;
    data.is_array = is_array;
    data.name = name;
    data.size = size;
    data.type = type;
    return data;
}
when_part_list* create_when_part_list(ast_exp_t* expression, ast_stmt_t* body){
    when_part_list* when_part = CALLOC(when_part_list);
    when_part->body = body;
    when_part->expression = expression;
    return when_part;
}