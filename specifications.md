GRAMMAR FOR THE PROGRAMMING LANGUAGE : SimpLang
===============================================================

## TOKEN DECLARATION

* `letter := a...z | A...Z`

* `digit := 0...9`

* `letgit := letter | digit _`

* `ID := letter letgit*`

* `CONSTNUM := digit*`

* `CONSTCHAR := single byte character`

* `CONSTSTRING := sequence of one or more byte character`

## GRAMMAR

* `PROG := DECLIST`

* `DECLIST := EMPTY | DECL DECLIST`

* `DECL := VARDEC | TYPEDEC | FNCDEC`

* `VARDEC := let  VARDECLID : TYPESPEC VAR_DEC_TAIL`

* `VARDECLID := ID VARDECLID_AUX`

* `VARDECLID_AUX := EMPTY | [ CONSTNUM ]`

* `VAR_DEC_TAIL := ; | = SIMPLEXP ;`

* `TYPESPEC := int | float | chr | str | bool | ID`

* `TYPEDEC := type ID { FIELDEC FIELDEC_LIST };`

* `FIELDEC := VARDECLID  : TYPESPEC ;`

* `FIELDEC_LIST := FIELDEC DIELDEC_LIST | EMPTY`

* `VARDECLIST := VARDEC VARDECLIST | EMPTY`

* `FNCDEC := fnc ID ( ARGS ) : FNCTYPESPEC STMT`

* `FNCTYPESPEC  :=  void | TYPESPEC`

* `ARGS  :=  ARGSLIST | void | EMPTY`

* `ARGLIST  :=  ARG ARGLIST_AUX`

* `ARGLIST_AUX  :=  , ARG ARGLIST_AUX | EMPTY`

* `ARG  :=  ARGID : TYPESPEC`

* `ARGID  :=  ID ARGID_TAIL`

* `ARGID_TAIL := EMPTY | [ ]`

* `STMT  :=  EXP_STMT | COMPLEX_STMT | IF_STMT | LOOP_STMT | RETURN_STMT | BREAK_STMT | SWITCH_STMT | CONTINUE_STMT`

* `EXP_STMT  :=  EXP ; | ;`

* `COMPLEX_STMT  :=  { VARDEC STMT_LIST }`

* `STMT_LIST  :=  STMT STMT_LIST | EMPTY`

* `IF_STMT  :=  if SIMPLEXP { STMT } ELSE_IF_STMT`

* `ELSE_IF_STMT  :=  else ELSE_AUX_STMT | EMPTY`

* `ELSE_AUX_STMT  :=  IF_STMT | { STMT }`

* `LOOP_STMT  := WHILE_STMT | FOR_STMT `

* `WHILE_STMT := while SIMPLEXP { STMT }`

* `FOR_STMT := for ID RANGE { STMT }`

* `RANGE  := : SIMPLEXP to SIMPLEXP RANGE_TAIL`

* `RANGE_TAIL := jump SIMPLEXP | EMPTY`

* `RETURN_STMT  :=  return RETURN_STMT_TAIL`

* `RETURN_STMT_TAIL := ; | EXPT;`

* `BREAK_STMT  :=  break;`

* `CONTINUE_STMT  :=  continue;`

* `SWITCH_STMT  :=  switch SIMPLEXP { WHEN_PART DEFAULT_PART }`

* `WHEN_PART  :=  when SIMPLEXP : STMT WHEN_PART | EMPTY`

* `DEFAULT_PART  :=  default STMT | EMPTY`

* `EXP  :=  SIMPLEXP`

* `SIMPLEXP := ANDEXP SIMEPLEXP_AUX`

* `SIMPLEXP_AUX := or ANDEXP SIMPLEXP_AUX | EMPTY`

* `AND_EXP := UNARY_REL_EXP AND_EXP_AUX`

* `AND_EXP_AUX := and UNARY_REL_EXP AND_EXP_AUX | EMPTY`

* `UNARY_REL_EXP := NOT UNARY_REL_EXP | REL_EXP`

* `REL_EXP := SUM_EXP REL_EXP_TAIL`

* `REL_EXP_TAIL := REL_OP SUM_EXP REL_EXP_TAIL | EMPTY`

* `REL_OP := <= | < | > | >= | == | !=`

* `SUM_EXP := MULT_EXP SUM_EXP_AUX`

* `SUM_EXP_AUX := SUM_OP MULT_EXP SUM_EXP_AUX | EMPTY`

* `SUM_OP := + | -`

* `MULT_EXP := UNARY_EXP MULT_EXP_AUX`

* `MULT_EXP_AUX := MULT_OP UNARY_EXP MULT_EXP_AUX | EMPTY`

* `MULT_OP := * | / | %`

* `UNARY_EXP := UNARY_OP UNARY_EXP | ASSIGN`

* `ASSIGN := FACT ASSIGN_TAIL`

* `ASSING_TAIL := ASSIGN_TAIL_HEAD EXP | EMPTY`

* `ASSIGN_TAIL_HEAD := = | += | -= | *= | \=`

* `UNARY_OP := + | - `

* `FACT := ( EXP ) | ID POST_ID | CONSTANT`

* `POST_ID := CALL | [ EXP ] | . ID POST_ID | EMPTY`

* `CALL := ( ARGS_CALL )`

* `ARGS_CALL := EMPTY | ARGS_CALL_LIST`

* `ARGS_CALL_LIST := EXP ARGS_CALL_LIST_AUX`

* `ARGS_CALL_LIST_AUX := , EXP ARGS_CALL_LIST_AUX | EMPTY`

* `CONST := CONSTCHAR | CONSTNUM | CONSTSTRING | true | false`

## KEYWORDS

```
let
put
get
if
else
for
to
while
type
fnc
return
break
continue
true
false
switch
when
default
and
or
not
jump
void
int
float
str
chr
bool
```
