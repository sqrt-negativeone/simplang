#ifndef AST_H
#define AST_H

#include <stdbool.h>
#include <stdlib.h>

/*
    what we gonna need is an AST for expressions, and an AST for statements
    and at the end we can merge them into one structure, the AST.
*/

//AST for expressions
typedef enum _exp_type exp_type;
typedef enum _operation_type operation_type;
typedef enum _assign_type assign_type;
typedef struct _ast_exp_t ast_exp_t;
typedef struct _ast_exp_operation ast_exp_operation;
typedef struct _ast_exp_member_access ast_exp_member_access;
typedef struct _ast_exp_fnc_call ast_exp_fnc_call;
typedef struct _arg_list arg_list;
typedef enum _const_type const_type;
typedef struct _ast_exp_const ast_exp_const_t;
typedef struct _ast_exp_array_access ast_exp_array_access;
typedef struct _ast_exp_assign ast_exp_assign;
typedef union _ast_exp_data_t ast_exp_data_t;

enum _exp_type
{
    ASSING_EXP,
    OPERATION_EXP,
    MEMBER_ACCESS,
    FNC_CALL_EXP,
    ARRAY_ACCESS,
    CONST_EXP
};
enum _operation_type
{
    PLUS_OPERATION,
    MINUS_OPERAION,
    MULT_OPERATION,
    DIV_OPERATION,
    AND_OPERATION,
    OR_OPERATION,
    NOT_OPERATION,
    REMINDER_OPERATOR,
    LESS_OPERATION,
    GREATER_OPERATION,
    LESS_EQ_OPERATION,
    GREATER_EQ_OPERATION,
    EQUAL_OPERATION,
    DIFF_OPERATION
};
enum _assign_type
{
    NORMAL_ASSIGN,
    ADD_ASSIGN,
    SUB_ASSIGN,
    MULT_ASSIGN,
    DIV_ASSIGN
};
struct _ast_exp_assign
{
    assign_type type;
    ast_exp_t* variable;
    ast_exp_t* expression;
};
struct _ast_exp_operation
{
    operation_type operation;
    ast_exp_t* left;
    ast_exp_t* right;
};
struct _ast_exp_member_access
{
    char* id;
    ast_exp_member_access* next;
};

struct _ast_exp_array_access
{
    char* id;
    ast_exp_t* index;
};

struct _arg_list
{
    ast_exp_t* exp;
    arg_list* next;
};

struct _ast_exp_fnc_call
{
    char* id;
    arg_list* args;
};

enum _const_type
{
    INT_CONST_EXP,
    FLOAT_CONST_EXP,
    CHR_CONST_EXP,
    STR_CONST_EXP,
    TRUE_CONST_EXP,
    FALSE_CONST_EXP
};
struct _ast_exp_const
{
    const_type type;
    char* value;
};
union _ast_exp_data_t
{
    ast_exp_fnc_call fnc_call;
    ast_exp_member_access member_acces;
    ast_exp_operation operation;
    ast_exp_assign assign;
    ast_exp_array_access array_access;
    ast_exp_const_t const_type;
};

struct _ast_exp_t
{
    exp_type type;
    ast_exp_data_t* data;
};

//AST for statements
typedef struct _param_list param_list;
typedef struct _ast_stmt_fnc_dec ast_stmt_fnc_dec;
typedef struct _ast_stmt_var_dec ast_stmt_var_dec;
typedef struct _fields_list fields_list;
typedef struct _ast_stmt_if ast_stmt_if;
typedef struct _ast_stmt_for ast_stmt_for;
typedef struct _ast_stmt_while ast_stmt_while;
typedef struct _when_part_list when_part_list;
typedef struct _ast_stmt_switch ast_stmt_switch;
typedef struct _ast_stmt_type_dec ast_stmt_type_dec;
typedef union _ast_stmt_data_t ast_stmt_data_t;
typedef struct _ast_stmt_return ast_stmt_return;
typedef struct  _ast_stmt_break_continue  ast_stmt_break_continue;
typedef struct _var_dec_data_t var_dec_data_t;
typedef struct _for_range for_range_t;
typedef enum _stmt_type stmt_type;
typedef struct _ast_stmt_t ast_stmt_t;

struct _var_dec_data_t
{
    char* name;
    char* type;
    bool is_array;
    int size;
};

struct _param_list
{
    var_dec_data_t data;
    param_list* next;
};


struct _ast_stmt_fnc_dec
{
    char* name;
    param_list* parameters;
    char* return_type;
    ast_stmt_t *body;
};
struct _ast_stmt_var_dec
{
    var_dec_data_t data;
    ast_exp_t* declaration;
};

struct _fields_list
{
    var_dec_data_t data;
    fields_list* next;
};

struct _ast_stmt_type_dec
{
    char* name;
    fields_list* fields;
};

struct _ast_stmt_if
{
    ast_exp_t* condition;
    ast_stmt_t* if_body;
    ast_stmt_t* else_body;
};

struct _for_range{
    ast_exp_t* begin;
    ast_exp_t* end;
    ast_exp_t* jump;
};

struct _ast_stmt_for
{
    char* it;
    for_range_t range;
    ast_stmt_t* body;
};

struct _ast_stmt_while
{
    ast_exp_t* condition;
    ast_stmt_t* body;
};

struct _when_part_list
{
    ast_exp_t* expression;
    ast_stmt_t* body;
    when_part_list* next;
};

struct _ast_stmt_switch
{
    ast_exp_t* item;
    when_part_list* when_list;
    ast_stmt_t* default_part;
};

struct _ast_stmt_return
{
    ast_exp_t* return_exp;
};

struct _ast_stmt_break_continue
{
    bool is_break;
};

union _ast_stmt_data_t
{
    ast_stmt_for for_stmt;
    ast_stmt_while while_stmt;
    ast_stmt_if if_stmt;
    ast_stmt_switch switch_stmt;
    ast_stmt_fnc_dec fnc_dec;
    ast_stmt_type_dec type_dec;
    ast_stmt_var_dec var_dec;
    ast_stmt_return return_stmt;
    ast_stmt_break_continue break_continue_stmt;
    ast_exp_t* exp;
};

enum _stmt_type
{
    FOR_STMT,
    WHILE_STMT,
    IF_STMT,
    SWITCH_STMT,
    FNC_DEC_STMT,
    VAR_DEC_STMT,
    TYPE_DEC_STMT,
    RETURN_STMT,
    BREAK_RETURN_STMT,
    EXP_STMT,
    EMPTY
};

struct _ast_stmt_t
{
    stmt_type type;
    ast_stmt_data_t* data;
    ast_stmt_t* next;
};

//merge the two ASTs into one, the AST
typedef enum _ast_type ast_type;
typedef union _ast_data_t ast_data_t;
typedef struct _ast_t ast_t;

enum _ast_type
{
    EXPRESSION,
    STATEMENT
};

union _ast_data_t
{
    ast_stmt_t stmt;
    ast_exp_t exp;
};


struct _ast_t
{
    ast_type type;
    ast_data_t* data;
};

//private functions
static ast_t* get_ast_stmt_node(stmt_type t);
static ast_t* get_ast_exp_node(exp_type t);

//public functions

//statments utilities
void insert_ast_stmt(ast_t* ast, ast_t* elem);
ast_t* create_ast_stmt_exp(ast_exp_t* exp);
ast_t* create_ast_stmt_empty();
for_range_t create_for_range(ast_exp_t* begin, ast_exp_t* end, ast_exp_t* jump);
ast_t* create_ast_stmt_for(for_range_t range, ast_stmt_t* body);
ast_t* create_ast_stmt_while(ast_exp_t* condition, ast_stmt_t* body);
ast_t* create_ast_stmt_if(ast_exp_t* condition, ast_stmt_t* if_body, ast_stmt_t* else_body);
ast_t* create_ast_stmt_switch(ast_exp_t* item, when_part_list* when_list, ast_stmt_t* default_part);
ast_t* create_ast_stmt_fnc_dec(char* name, param_list* parameters, char* return_type, ast_stmt_t* body);
ast_t* create_ast_stmt_type_dec(char* name, fields_list* fields);
ast_t* create_ast_stmt_var_dec(var_dec_data_t data, ast_exp_t* declaration);
ast_t* create_ast_stmt_return_stmt(ast_exp_t* return_exp);
ast_t* create_ast_stmt_break_continue_stmt(bool is_break);

//expressions utilities
ast_t* create_ast_exp_const(const_type type, char* value);
ast_t* create_ast_exp_array_access(char* id, ast_exp_t* index);
ast_t* create_ast_exp_assign(assign_type type, ast_exp_t* variable, ast_exp_t* expression);
ast_t* create_ast_exp_operation(operation_type operation, ast_exp_t* left, ast_exp_t* right);
ast_t* create_ast_exp_member_access(char* id, ast_exp_member_access* next);
ast_t* create_ast_exp_fnc_call(char* id, arg_list* args);

// helper utilities

fields_list* create_field_lists_node(var_dec_data_t data);
param_list* create_param_list_node(var_dec_data_t data);
arg_list* create_arg_list_node(ast_exp_t* exp, arg_list* next);
var_dec_data_t create_var_dec_data(char* name, char* type, bool is_array, int size);
when_part_list* create_when_part_list(ast_exp_t* expression, ast_stmt_t* body);

#endif