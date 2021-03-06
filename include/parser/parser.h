#ifndef PARSER_H
#define PARSER_H
#include "parser/ast.h"

extern ast_t* program();
extern ast_t* decl_list();
extern ast_t* decl();
extern ast_t* var_decl();
extern void var_decl_id(var_dec_data_t* data);
extern void var_decl_id_aux(var_dec_data_t* data);
extern void var_decl_tail(ast_t* ast_var_dec);
extern ast_t* type_decl();
extern fields_list* field_dec();
extern fields_list* field_dec_list();
extern ast_t* fnc_decl();
extern char* fnc_type_spec();
extern param_list* fnc_args();
extern param_list* fnc_args_list();
extern param_list* fnc_args_list_aux();
extern param_list* fnc_arg();
extern void arg_id(var_dec_data_t* data);
extern void arg_id_tail();

extern ast_t* stmt();
extern ast_t* exp_stmt();
extern ast_t* complex_stmt();
extern ast_t* stmt_list();
extern ast_t* if_stmt();
extern ast_t* else_if_stmt();
extern ast_t* else_aux_stmt();
extern ast_t* loop_stmt();
extern ast_t* for_stmt();
extern ast_t* while_stmt();
extern for_range_t range();
extern ast_t* range_tail();
extern ast_t* return_stmt();
extern ast_t* return_stmt_tail();
extern ast_t* break_stmt();
extern ast_t* continue_stmt();//one
extern ast_t* switch_stmt();
extern when_part_list* when_part();
extern ast_t* default_part();

extern ast_t* exp_();
extern ast_t* simple_exp();
extern ast_t* simple_exp_aux();
extern ast_t* and_exp();
extern ast_t* and_exp_aux();
extern ast_t* unary_rel_exp();
extern ast_t* rel_exp();
extern ast_t* sum_exp();
extern ast_t* mult_exp();
extern ast_t* unary_exp();
extern ast_t* assign_exp();
extern ast_t* fact();
extern ast_t* post_id();
extern arg_list* call();
extern arg_list* args_call();
extern arg_list* args_call_list();
extern ast_t* const_();

#endif