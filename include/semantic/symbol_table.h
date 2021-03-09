#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdbool.h>

/*
 * symbol table entries, each entry has a type to determin if it is a function, a variable or a type declaration, and then we can access the respective data for each type
 * symbol_entry_t is the base unit of the symbol table
*/

//symbol entries type declarations :

typedef enum _symbol_entry_type_t symbol_entry_type_t;
typedef enum _native_type_t native_type_t;
typedef enum _type_kind_t type_kind_t;

typedef struct _symbol_var_t symbol_var_t;
typedef struct _symbol_fun_t symbol_fun_t;
typedef struct _type_fields_t type_fields_t;
typedef struct _symbol_custom_type_t symbol_custom_type_t;
typedef struct _symbol_type_t symbol_type_t; 
typedef struct _symbol_entry_t symbol_entry_t;

typedef union _symbol_type_data_t symbol_type_data_t;
typedef union _symbol_entry_data_t symbol_entry_data_t;

enum _symbol_entry_type_t{
    FUNCTION,
    VARIABLE,
    TYPE
};
enum _type_kind_t{
    CUSTOM,
    NATIVE
};
enum _native_type_t{
    NATIVE_INT,
    NATIVE_FLOAT,
    NATIVE_CHR,
    NATIVE_STR,
    NATIVE_BOOL
};

struct _symbol_var_t{
    char* type_name;
    bool is_array;
    bool is_initialized;
    void* value;
};
struct _symbol_fun_t{
    int parameters_count;
    symbol_var_t* params;
    char* return_type_name;
};
struct _type_fields_t{
    char* type_name;
    bool is_array;
};
struct _symbol_custom_type_t{
    type_fields_t* fields;
    int fields_count;
};
struct _symbol_type_t{
    type_kind_t type;
    symbol_type_data_t data;
};
struct _symbol_entry_t{
    char* name;
    symbol_entry_type_t type;
    symbol_entry_data_t data;
};

union _symbol_entry_data_t{
    symbol_var_t variable;
    symbol_fun_t function;
    symbol_type_t type;
};
union _symbol_type_data_t{
    symbol_custom_type_t custom;
    native_type_t native;
};

// symbol table will be just a dynamic array as a first version, we can later consider using more advanced data structures for effeciency like binary trees or hash tables

typedef struct _vec_symbol_table_t vec_symbol_table_t;

struct _vec_symbol_table_t
{
    symbol_entry_t* data;
    int size;
    int capacity;
};

// insert entry at the back of the symbol table
bool insert_entry(symbol_entry_t entry);
symbol_entry_t create_variable_entry(char* name, char* type_name, bool is_array, bool is_initialized, void* data);
symbol_entry_t create_function_entry(char* name, int paramters_count, symbol_var_t* params, char* return_type);
symbol_entry_t create_type_entry(char* name, type_fields_t* fields, int fields_count);

// scope declarations
/*
 * the scope will be represented as a stack data structure, the top of the stack will correspond to the current scope.
 * when we reach a new block, a new scope is pushed, and when we go out of that block the scope is poped.
 * when encountring an id, we first look at the scope in the top of the stack, if we find entry with the name of that id
   then we return that entry, else we search down the stack until an entry is found or else report that the id is undeclared
*/

typedef struct _scope_stack_t scope_stack_t;

struct _scope_stack_t{
    vec_symbol_table_t* top;
    scope_stack_t* next;
};

//push a new scope into the stack
void push_scope();

//pop the top scope from the stack
void pop_scope();

#endif