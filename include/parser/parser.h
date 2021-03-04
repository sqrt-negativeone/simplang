#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
extern void program(); //done
extern void decl_list(); //done
extern void decl(); //done
extern void var_decl(); //done
extern void var_decl_id(); //done
extern void var_decl_id_aux(); //done
extern void var_decl_tail(); //done
extern void type_spec(); //done
extern void type_decl(); //done
extern void var_decl_list(); //done
extern void fnc_decl(); //done
extern void fnc_type_spec(); //done
extern void fnc_args(); //done
extern void fnc_args_list();// done
extern void fnc_args_list_aux();//done
extern void fnc_arg(); //done
extern void arg_id(); //done
extern void arg_id_tail(); //done

extern void stmt(); //done
extern void exp_stmt(); // done
extern void complex_stmt(); //done
extern void stmt_list(); //done
extern void if_stmt(); //done
extern void else_if_stmt(); //done
extern void else_aux_stmt(); //done
extern void loop_stmt(); //done
extern void for_stmt();// done
extern void while_stmt(); //done
extern void range(); //done
extern void range_tail(); //done
extern void return_stmt();
extern void return_stmt_tail(); //done
extern void break_stmt(); //done
extern void continue_stmt();//one
extern void switch_stmt();//done
extern void when_part(); //done
extern void default_part(); //done

extern void exp(); //done
extern void simple_exp(); //done
extern void simple_exp_aux(); //done
extern void and_exp(); // done
extern void and_exp_aux(); //done
extern void unary_rel_exp(); //done
extern void rel_exp(); //done
extern void rel_exp_tail(); //done
extern void sum_exp(); //done
extern void sum_exp_aux(); //done
extern void mult_exp(); //done
extern void mult_exp_aux(); //done
extern void unary_exp(); //done
extern void fact(); //done
extern void post_id(); //done
extern void call(); //done
extern void args_call(); //done
extern void args_call_list(); //done
extern void args_call_list_aux(); //done
extern void const_();

#endif