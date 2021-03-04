#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
extern void program();
extern void decl_list();
extern void decl();
extern void var_decl();
extern void var_decl_id();
extern void var_decl_id_aux();
extern void var_decl_tail();
extern void type_spec();
extern void type_decl();
extern void var_decl_list();
extern void fnc_decl();
extern void fnc_decl_aux();
extern void fnc_type_spec();
extern void fnc_args();
extern void fnc_args_list();
extern void fnc_args_list_aux();
extern void fnc_arg();
extern void arg_id();

extern void stmt();
extern void exp_stmt();
extern void complex_stmt();
extern void stmt_list();
extern void if_stmt();
extern void else_if_stmt();
extern void else_aux_stmt();
extern void loop_stmt();
extern void range();
extern void range_tail();
extern void return_stmt();
extern void break_stmt();
extern void continue_stmt();
extern void switch_stmt();
extern void when_part();
extern void default_part();

extern void exp();
extern void simple_exp();
extern void simple_exp_aux();
extern void and_exp();
extern void and_exp_aux();
extern void unary_rel_exp();
extern void rel_exp();
extern void rel_op();
extern void sum_exp();
extern void sum_exp_aux();
extern void sum_op();
extern void mult_exp();
extern void mult_exp_aux();
extern void mult_op();
extern void unary_exp();
extern void unary_op();
extern void fact();
extern void mutable_();
extern void mutable_aux();
extern void mutable_tail();
extern void immutable();
extern void call();
extern void args_call();
extern void args_call_list();
extern void args_call_list_aux();
extern void const_();

#endif