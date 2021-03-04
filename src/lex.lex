%{
#include "../include/lexer/lexer.h"
#include "../include/lexer/token.h"

#include <stdio.h>
#include <stdlib.h>

int line = 1;

%}

%option noyywrap
%option nounput yylineno

ID [a-zA-z][a-zA-z"_"0-9]*
DIGIT [0-9]
NUMBER	 {DIGIT}{DIGIT}*
FLOAT {NUMBER}("."{NUMBER})?
COMMENTS [\/][\/](.)*
STR         ([\"]([^\n'"\\]|[\\][n]|[\\][t]|[\\][r]|[\\][\\]|[\\][']|[\\]["])*[\"])
CHR            ([\']([^\n'"\\]|[\\][n]|[\\][t]|[\\][r]|[\\][\\]|[\\][']|[\\]["])?[\'])

%%


<<EOF>> {return EOFF;}

"put"   {return KEYWORD_PUT;}
"get"	{return KEYWORD_GET;}
"if"	{return KEYWORD_IF;}
"else"	{return KEYWORD_ELSE;}
"for"	{return KEYWORD_FOR;}
"in"	{return KEYWORD_IN;}
"to"	{return KEYWORD_TO;}
"while"	{return KEYWORD_WHILE;}
"type"	{return KEYWORD_TYPE;}
"fnc"	{return KEYWORD_FNC;}
"return" {return KEYWORD_RETURN;}
"break"	 {return KEYWORD_BREAK;}
"continue"	{return KEYWORD_CONTINUE;}
"true"		{return KEYWORD_TRUE;}
"false"		{return KEYWORD_FALSE;}
"switch"	{return KEYWORD_SWITCH;}
"when"		{return KEYWORD_WHEN;}
"default"	{return KEYWORD_DEFAULT;}
"and"		{return KEYWORD_AND;}
"or"		{return KEYWORD_OR;}
"not"		{return KEYWORD_NOT;}
"jump"		{return KEYWORD_JUMP;}
"main"		{return KEYWORD_MAIN;}
"void"		{return KEYWORD_VOID;}
\:			{return DELEMETER_COLON;}
\;			{return DELEMETER_SEMICOLON;}
\(			{return DELEMETER_OPEN_PAR;}
\)			{return DELEMETER_CLOS_PAR;}
\{			{return DELEMETER_CURL_OPEN_PAR;}
\}			{return DELEMETER_CURL_CLOS_PAR;}
\+			{return DELEMETER_PLUS;}
\-			{return DELEMETER_MINUS;}
\*			{return DELEMETER_STAR;}
"%"			{return DELEMETER_PERCENTAGE;}
\=			{return DELEMETER_ASSIGN;}
\<			{return DELEMETER_LESS;}
\<\=		{return DELEMETER_LESS_EQ;}
\>			{return DELEMETER_GREATER;}
\>\=		{return DELEMETER_GREATER_EQ;}
\=\=		{return DELEMETER_EQUAL;}
\!\=		{return DELEMETER_NOT_EQUAL;}
\/			{return DELEMETER_DIVIDE;}
\/\=		{return DELEMETER_DIVIDE_EQ;}
\*\=		{return DELEMETER_MULT_EQ;}
\+\=		{return DELEMETER_PLUS_EQ;}
\-\=		{return DELEMETER_MINUS_EQ;}
\,			{return DELEMETER_COMMA;}
\.			{return DELEMETER_DOT;}
\[			{return DELEMETER_LEFT_BRACKET;}
\]			{return DELEMETER_RIGHT_BRACKET;}
{COMMENTS}    {return COMMENT;}
{ID}		  {return IDENTIFIER;}
{CHR} 		  {return CHR_LITERAL;}
{STR}		  {return STR_LITERAL;}
{NUMBER}      {return NUMBER_CONST;}
{FLOAT}       {return FLOAT_CONST;}

[\n]+          {} 			 
[ \r\t]+	  {}

. 			  { printf("unexpected character, line = %d\n", line); return ERRONEOUS;}

%%

token_t get_next_token()
{
	extern int yylex();
	extern int yylineno;
	extern char* value;

	int token;

	token_t the_token;

	token = yylex();

	the_token.value = yytext;
    the_token.line_no = yylineno;
    the_token.t = token;

    return the_token;
}

int main(void)
{
	token_t ntoken = get_next_token();

	printf("hello zeus\n");
	printf("this is the fuckin 51 , %d\n", IDENTIFIER);
	while(ntoken.t != EOFF)
	{
		printf("line : %d\t tokenValue : %s\t tokenType : %d\n", ntoken.line_no, ntoken.value, ntoken.t);
		ntoken = get_next_token();
	}
	
	return 0;
}

