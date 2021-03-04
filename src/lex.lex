%{
#include "lexer/lexer.h"

#include <stdio.h>
#include <stdlib.h>

int line = 1;

token_t current_token;

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
"void"		{return KEYWORD_VOID;}
\:			{return DELIMETER_COLON;}
\;			{return DELIMETER_SEMICOLON;}
\(			{return DELIMETER_OPEN_PAR;}
\)			{return DELIMETER_CLOS_PAR;}
\{			{return DELIMETER_CURL_OPEN_PAR;}
\}			{return DELIMETER_CURL_CLOS_PAR;}
\+			{return DELIMETER_PLUS;}
\-			{return DELIMETER_MINUS;}
\*			{return DELIMETER_STAR;}
"%"			{return DELIMETER_PERCENTAGE;}
\=			{return DELIMETER_ASSIGN;}
\<			{return DELIMETER_LESS;}
\<\=		{return DELIMETER_LESS_EQ;}
\>			{return DELIMETER_GREATER;}
\>\=		{return DELIMETER_GREATER_EQ;}
\=\=		{return DELIMETER_EQUAL;}
\!\=		{return DELIMETER_NOT_EQUAL;}
\/			{return DELIMETER_SLASH;}
\/\=		{return DELIMETER_DIVIDE_EQ;}
\*\=		{return DELIMETER_MULT_EQ;}
\+\=		{return DELIMETER_PLUS_EQ;}
\-\=		{return DELIMETER_MINUS_EQ;}
\,			{return DELIMETER_COMMA;}
\.			{return DELIMETER_DOT;}
\[			{return DELIMETER_LEFT_BRACKET;}
\]			{return DELIMETER_RIGHT_BRACKET;}
{COMMENTS}    {return COMMENT;}
{ID}		  {return IDENTIFIER;}
{CHR} 		  {return CHR_LITERAL;}
{STR}		  {return STR_LITERAL;}
{NUMBER}      {return NUMBER_CONST;}
{FLOAT}       {return FLOAT_CONST;}

\n          { line++}
[ \r\t]+	  {}

. 			  { printf("unexpected character, line = %d\n", line); return ERRONEOUS;}

%%

void get_next_token()
{
	current_token.type = yylex();
	current_token.line_no = line;
	current_token.value = yytext;
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

