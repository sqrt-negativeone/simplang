GRAMMAR FOR THE PROGRAMMING LANGUAGE (YET TO BE NAMED)
===============================================================

## TOKEN DECLARATION

* `letter = a...z | A...Z`

* `digit = 0...9`

* `letgit = letter | digit`

* `ID = letter letgit*`

* `CONSTNUM = digit*`

* `CONSTCHAR = single byte character`

* `CONSTSTRING = sequence of one or more byte character`

## GRAMMAR

* `PROG = DECLIST`

* `DECLIST = (DECL)*`

* `DECL = VARDEC | TYPEDEC | FNCDEC`

* `VARDEC = VARDECLIST : TYPESPEC ;`

* `VARDECLIST = (VARDECLIST , | EMPTY) VARDECLINIT`

* `VARDECLINIT = VARDECLID | VARDECLID = SIMPLEXP`

* `VARDECLID = ID | ID [ CONSTNUM ]`

* `TYPESPEC = int | float | double | chr | str | bool | ID`

* `TYPEDEC = type { (VARDEC)+ };`

* `FNCDEC = fnc ID (ARGS) : FNCTYPESPEC (; | STMT)`

* `FNCTYPESPEC = void | TYPESPEC`

* `ARGS = ARGSLIST | void | EMPTY`

* `ARGLIST = (ARGLIST, | EMTY) ARG`

* `ARG = TYPESPEC ARGID`

* `ARGID = ID | ID []`

* `STMT = EXP_STMT | COMPLEX_STMT | IF_STMT | LOOP_STMT | RETURN_STMT | BREAK_STMT | SWITCH_STMT | CONTINUE_STMT`

* `EXP_STMT = EXP ; | ;`

* `COMPLEX_STMT = {VARDEC STMT_LIST}`

* `STMT_LIST = STMT_LIST STMT | EMPTY`

* `IF_STMT = if SIMPLEXP { STMT } ELSE_IF_STMT`

* `ELSE_IF_STMT = else IF_STMT | else { STMT } | EMPTY`

* `LOOP_STMT = while SIMPLEXP {STMT} | for ID = RANGE {STMT}`

* `RANGE = SIMPLEXP to SIMPLEXP | SIMPLEXP to SIMPLEXP jump SIMPLEXP | : ID`

* `RETURN_STMT = return; | return EXP;`

* `BREAK_STMT = break;`

* `CONTINUE_STMT = continue;`

* `SWITCH_STATME = switch SIMPLEXP {WHEN_PART DEFAULT_PART}`

* `WHEN_PART = when SIMPLEXP : STMT | EMPTY`

* `DEFAULT_PART = default STMT | EMPTY`

* `EXP = MUTABLE = EXP | MUTABLE += EXP | MUTABLE -= EXP | MUTABLE *= EXP | MUTABLE /= EXP | MUTABLE++ | MUTABLE--| SIMPLEXP`

* `SIMPLEXP = SIMPLEXP or AND_EXP | ANDEXP`

* `AND_EXP = AND_EXP and UNARY_RELATION_EXP | UNARY_REL_EXP`

* `UNARY_REL_EXP = NOT UNARY_REL_EXP | REL_EXP`

* `REL_EXP = SUM_EXP REL_OP SUM_EXP`

* `REL_OP = <= | < | > | >= | == | !=`

* `SUM_EXP = SUM_EXP SUM_OP MULT_EXP`

* `SUM_OP = + | -`

* `MULT_EXP = MULT_EXP MUTL_OP UNARY_EXP`

* `MULT_EXP = * | / | %`

* `UNARY_EXP = UNARY_OP UNARY_EXP | FACT`

* `UNARY_EXP = + | - | ?`

* `FACT = IMMUTABLE | MUTABLE`

* `MUTABLE = ID | ID [EXP]`

* `IMMUTABLE = ( EXP ) | CALL | CONSTANT`

* `CALL = ID ( ARGS_CALL )`

* `ARGS_CALL = EMPTY | ARGS_CALL_LIST`

* `ARGS_CALL_LIST = ARGS_CALL_LIST , EXP | EXP`

* `CONST = CONSTCHAR | CONSTNUM | CONSTSTRING | true | false`

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
```
