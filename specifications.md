GRAMMAR FOR THE PROGRAMMING LANGUAGE (YET TO BE NAMED)
===============================================================

## TOKEN DECLARATION

* `letter := a...z | A...Z`

* `digit := 0...9`

* `letgit := letter | digit`

* `ID := letter letgit*`

* `CONSTNUM := digit*`

* `CONSTCHAR := single byte character`

* `CONSTSTRING := sequence of one or more byte character`

## GRAMMAR

* `PROG := DECLIST`

* `DECLIST := (DECL)*`

* `DECL := VARDEC | TYPEDEC | FNCDEC`

* `VARDEC := ID : TYPESPEC; | VARDECLID : TYPESPEC = SIMPLEXP;`

* `VARDECLID := ID | ID [ CONSTNUM ]`

* `TYPESPEC := int | float | double | chr | str | bool | ID`

* `TYPEDEC := type ID { (VARDEC)+ };`

* `FNCDEC := fnc ID (ARGS) : FNCTYPESPEC FNCDEC_AUX`

* `FNCDEC_AUX  :=  ; | STMT`

* `FNCTYPESPEC  :=  void | TYPESPEC`

* `ARGS  :=  ARGSLIST | void | EMPTY`

* `ARGLIST  :=  ARG ARGLIST_AUX`

* `ARGLIST_AUX  :=  , ARG ARGLIST_AUX | EMPTY`

* `ARG  :=  ARGID : TYPESPEC`

* `ARGID  :=  ID | ID []`

* `STMT  :=  EXP_STMT | COMPLEX_STMT | IF_STMT | LOOP_STMT | RETURN_STMT | BREAK_STMT | SWITCH_STMT | CONTINUE_STMT`

* `EXP_STMT  :=  EXP ; | ;`

* `COMPLEX_STMT  :=  { VARDEC STMT_LIST }`

* `STMT_LIST  :=  STMT STMT_LIST | EMPTY`

* `IF_STMT  :=  if SIMPLEXP { STMT } ELSE_IF_STMT`

* `ELSE_IF_STMT  :=  else ELSE_AUX_STMT | EMPTY`

* `ELSE_AUX_STMT  :=  IF_STMT | { STMT }`

* `LOOP_STMT  :=  while SIMPLEXP { STMT } | for ID RANGE { STMT }`

* `RANGE  := : SIMPLEXP to SIMPLEXP RANGE_TAIL | in SIMPLEXP`

* `RANGE_TAIL = jump SIMPLEXP | EMPTY`

* `RETURN_STMT  :=  return; | return EXP;`

* `BREAK_STMT  :=  break;`

* `CONTINUE_STMT  :=  continue;`

* `SWITCH_STMT  :=  switch SIMPLEXP { WHEN_PART DEFAULT_PART }`

* `WHEN_PART  :=  when SIMPLEXP : STMT WHEN_PART | EMPTY`

* `DEFAULT_PART  :=  default STMT | EMPTY`

* `EXP  :=  MUTABLE = EXP | MUTABLE += EXP | MUTABLE -= EXP | MUTABLE *= EXP | MUTABLE /= EXP | MUTABLE++ | MUTABLE--| SIMPLEXP`

* `SIMPLEXP := ANDEXP SIMEPLEXP_AUX`

* `SIMPLEXP_AUX := or ANDEXP SIMPLEXP_AUX | EMPTY`

* `AND_EXP := UNARY_REL_EXP AND_EXP_AUX`

* `AND_EXP_AUX := and UNARY_REL_EXP AND_EXP_AUX | EMPTY`

* `UNARY_REL_EXP := NOT UNARY_REL_EXP | REL_EXP`

* `REL_EXP := SUM_EXP REL_OP SUM_EXP`

* `REL_OP := <= | < | > | >= | == | !=`

* `SUM_EXP := MULT_EXP SUM_EXP_AUX`

* `SUM_EXP_AUX := SUM_OP MULT_EXP SUM_EXP_AUX | EMPTY`

* `SUM_OP := + | -`

* `MULT_EXP := UNARY_EXP MULT_EXP_AUX`

* `MULT_EXP_AUX := MULT_OP UNARY_EXP MULT_EXP_AUX | EMPTY`

* `MULT_EXP := * | / | %`

* `UNARY_EXP := UNARY_OP UNARY_EXP | FACT`

* `UNARY_EXP := + | - | ?`

* `FACT := IMMUTABLE | MUTABLE`

* `MUTABLE := ID MUTABLE_AUX MUTABLE_TAIL`

* `MUTABLE_AUX := EMPTY | [ EXP ]`

* `MUTABLE_TAIL := . MUTABLE`

* `IMMUTABLE := ( EXP ) | CALL | CONSTANT`

* `CALL := ID ( ARGS_CALL )`

* `ARGS_CALL := EMPTY | ARGS_CALL_LIST`

* `ARGS_CALL_LIST := EXP ARGS_CALL_LIST_AUX`

* `ARGS_CALL_LIST_AUX := , EXP ARGS_CALL_LIST_AUX | EMPTY`

* `CONST := CONSTCHAR | CONSTNUM | CONSTSTRING | true | false`

## KEYWORDS

```
put
get
if
else
for
in
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
```
