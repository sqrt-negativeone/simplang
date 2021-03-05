#ifndef AST_H
#define AST_H

#include <stdbool.h>

/*
    what we gonna need is an AST for expressions, and an AST for statements
    and at the end we can merge them into one structure, the AST.
*/

//AST for expressions
typedef enum _exp_type exp_type;
typedef enum _operation_type operation_type;
typedef struct _ast_exp ast_exp;
typedef struct _ast_exp_operation ast_exp_operation;
typedef struct _ast_exp_member_access ast_exp_member_access;
typedef struct _ast_exp_fnc_call ast_exp_fnc_call;
typedef struct _arg_list arg_list;
typedef struct _ast_exp_assign ast_exp_assign;
typedef union _ast_exp_data_t* ast_exp_data_t;

enum _exp_type
{
    ASSING_EXP,
    OPERATION_EXP,
    MEMBER_ACCESS,
    FNC_CALL_EXP
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
    REMINDER_OPERATOR
};
struct _ast_exp_assign
{
    ast_exp_member_access* variable;
    ast_exp* expression;
};
struct _ast_exp_operation
{
    operation_type operation;
    ast_exp* left;
    ast_exp* right;
};
struct _ast_exp_member_access
{
    char* id;
    ast_exp_member_access* next;
};

struct _arg_list
{
    ast_exp exp;
    arg_list* next;
};

struct _ast_exp_fnc_call
{
    char* id;
    arg_list* args;
};

union _ast_exp_data_t
{
    ast_exp_fnc_call fnc_call;
    ast_exp_member_access member_acces;
    ast_exp_operation operation;
    ast_exp_assign assign;
};

struct _ast_exp
{
    exp_type type;
    ast_exp_data_t data;
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
typedef enum _stmt_type stmt_type;
typedef struct _ast_stmt ast_stmt;

struct _param_list
{
    char* id;
    char* type;
    _param_list* next;
};

struct _ast_stmt_fnc_dec
{
    char* name;
    param_list* parameters;
    char* return_type;
    ast_stmt *body;
};

struct _ast_stmt_var_dec
{
    char* name;
    char* type;
    ast_exp* declaration;
};

struct _fields_list
{
    char* name;
    char* type;
    fields_list* next;
};

struct _ast_stmt_type_dec
{
    char* name;
    fields_list* fields;
};

struct _ast_stmt_if
{
    ast_exp condition;
    ast_stmt* if_body;
    ast_stmt* else_body;
};

struct _ast_stmt_for
{
    char* it;
    int begin;
    int end;
    int jump;
    ast_stmt* body;
};

struct _ast_stmt_while
{
    ast_exp* condition;
    ast_stmt* body;
};

struct _when_part_list
{
    ast_exp* expression;
    ast_stmt* body;
    when_part_list* next;
};

struct _ast_stmt_switch
{
    ast_exp_member_access* item;
    when_part_list when_list;
    ast_stmt* default_part;
};

struct _ast_stmt_return
{
    ast_exp return_exp;
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
    BREAK_RETURN_STMT
};

struct _ast_stmt
{
    stmt_type type;
    ast_stmt_data_t* data;
};

//merge the two ASTs into one, the  AST
typedef enum _ast_type ast_type;
typedef union _ast_data_t ast_data_t;
typedef struct _ast ast;

enum _ast_type
{
    EXPRESSION,
    STATEMENT
};

union _ast_data_t
{
    ast_stmt stmt;
    ast_exp exp;
};


struct _ast
{
    ast_type type;
    ast_data_t* data;
};

#endif