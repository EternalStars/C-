#############################################################################
#                     U N R E G I S T E R E D   C O P Y
# 
# You are on day 70 of your 30 day trial period.
# 
# This file was produced by an UNREGISTERED COPY of Parser Generator. It is
# for evaluation purposes only. If you continue to use Parser Generator 30
# days after installation then you are required to purchase a license. For
# more information see the online help or go to the Bumble-Bee Software
# homepage at:
# 
# http://www.bumblebeesoftware.com
# 
# This notice must remain present in the file. It cannot be removed.
#############################################################################

#############################################################################
# myparser.v
# YACC verbose file generated from myparser.y.
# 
# Date: 12/26/19
# Time: 18:51:03
# 
# AYACC Version: 2.07
#############################################################################


##############################################################################
# Rules
##############################################################################

    0  $accept : start $end

    1  start : MAIN LP RP block

    2  block : LFP stmts RFP

    3  stmts : stmt stmts
    4        | stmt

    5  stmt : expr_stmt
    6       | var_stmt
    7       | if_stmt
    8       | while_stmt
    9       | for_stmt
   10       | block
   11       | input_stmt
   12       | output_stmt
   13       | func_stmt
   14       | func_asked_stmt
   15       | return_stmt

   16  type_var : INT
   17           | CHAR
   18           | VOID
   19           | BOOL

   20  id_list : expr COMMA id_list
   21          | expr

   22  input_stmt : CIN RM ID SEMI

   23  output_stmt : COUT LM term SEMI

   24  var_stmt : type_var id_list SEMI

   25  func_var : func_var1 COMMA func_var
   26           | func_var1

   27  func_var1 : type_var ID

   28  expr_stmt : expr SEMI
   29            | SEMI

   30  expr : ID ASSIGN expr
   31       | or_expr

   32  or_expr : or_expr OR and_expr
   33          | and_expr

   34  and_expr : and_expr AND eq_expr
   35           | eq_expr

   36  eq_expr : eq_expr EQ simple_expr
   37          | eq_expr GE simple_expr
   38          | eq_expr LE simple_expr
   39          | eq_expr GT simple_expr
   40          | eq_expr LT simple_expr
   41          | eq_expr NEQ simple_expr
   42          | eq_expr LM simple_expr
   43          | eq_expr RM simple_expr
   44          | simple_expr

   45  simple_expr : simple_expr PLUS simple_expr
   46              | simple_expr MINUS simple_expr
   47              | simple_expr MUL simple_expr
   48              | simple_expr DIV simple_expr
   49              | simple_expr MOD simple_expr
   50              | simple_expr DPLUS
   51              | simple_expr DMINUS
   52              | term

   53  term : LP expr RP
   54       | ID
   55       | NUMBER
   56       | Constchar
   57       | NOT term

   58  if_stmt : IF LP expr RP stmt
   59          | IF LP expr RP stmt ELSE stmt

   60  for_stmt : FOR LP expr SEMI expr SEMI expr RP stmt
   61           | FOR LP SEMI expr SEMI expr RP stmt
   62           | FOR LP expr SEMI SEMI expr RP stmt
   63           | FOR LP expr SEMI expr SEMI RP stmt
   64           | FOR LP SEMI SEMI expr RP stmt
   65           | FOR LP SEMI expr SEMI RP stmt
   66           | FOR LP expr SEMI SEMI RP stmt
   67           | FOR LP SEMI SEMI RP stmt

   68  while_stmt : WHILE LP expr RP stmt

   69  func_stmt : type_var ID LP func_var RP block

   70  func_asked_stmt : type_var ID ASSIGN func_asked_stmt1
   71                  | func_asked_stmt1

   72  func_asked_stmt1 : ID LP expr RP SEMI

   73  expr_func : expr COMMA expr_func
   74            | expr

   75  return_stmt : RETURN term


##############################################################################
# States
##############################################################################

state 0
	$accept : . start $end

	MAIN  shift 1

	start  goto 2


state 1
	start : MAIN . LP RP block

	LP  shift 3


state 2
	$accept : start . $end  (0)

	$end  accept


state 3
	start : MAIN LP . RP block

	RP  shift 4


state 4
	start : MAIN LP RP . block

	LFP  shift 5

	block  goto 6


state 5
	block : LFP . stmts RFP

	IF  shift 7
	FOR  shift 8
	WHILE  shift 9
	CIN  shift 10
	COUT  shift 11
	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15
	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LFP  shift 5
	SEMI  shift 20
	LP  shift 21
	RETURN  shift 22

	stmt  goto 23
	while_stmt  goto 24
	output_stmt  goto 25
	expr_stmt  goto 26
	if_stmt  goto 27
	input_stmt  goto 28
	func_stmt  goto 29
	func_asked_stmt  goto 30
	return_stmt  goto 31
	block  goto 32
	for_stmt  goto 33
	stmts  goto 34
	var_stmt  goto 35
	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	type_var  goto 40
	term  goto 41
	func_asked_stmt1  goto 42
	expr  goto 43


state 6
	start : MAIN LP RP block .  (1)

	.  reduce 1


state 7
	if_stmt : IF . LP expr RP stmt ELSE stmt
	if_stmt : IF . LP expr RP stmt

	LP  shift 44


state 8
	for_stmt : FOR . LP SEMI expr SEMI RP stmt
	for_stmt : FOR . LP expr SEMI expr SEMI RP stmt
	for_stmt : FOR . LP expr SEMI expr SEMI expr RP stmt
	for_stmt : FOR . LP expr SEMI SEMI expr RP stmt
	for_stmt : FOR . LP SEMI expr SEMI expr RP stmt
	for_stmt : FOR . LP SEMI SEMI expr RP stmt
	for_stmt : FOR . LP expr SEMI SEMI RP stmt
	for_stmt : FOR . LP SEMI SEMI RP stmt

	LP  shift 45


state 9
	while_stmt : WHILE . LP expr RP stmt

	LP  shift 46


state 10
	input_stmt : CIN . RM ID SEMI

	RM  shift 47


state 11
	output_stmt : COUT . LM term SEMI

	LM  shift 48


state 12
	type_var : INT .  (16)

	.  reduce 16


state 13
	type_var : CHAR .  (17)

	.  reduce 17


state 14
	type_var : VOID .  (18)

	.  reduce 18


state 15
	type_var : BOOL .  (19)

	.  reduce 19


state 16
	expr : ID . ASSIGN expr
	term : ID .  (54)
	func_asked_stmt1 : ID . LP expr RP SEMI

	ASSIGN  shift 49
	LP  shift 50
	.  reduce 54


state 17
	term : NUMBER .  (55)

	.  reduce 55


state 18
	term : Constchar .  (56)

	.  reduce 56


state 19
	term : NOT . term

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	term  goto 52


state 20
	expr_stmt : SEMI .  (29)

	.  reduce 29


state 21
	term : LP . expr RP

	ID  shift 53
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 54


state 22
	return_stmt : RETURN . term

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	term  goto 55


state 23
	stmts : stmt . stmts
	stmts : stmt .  (4)

	IF  shift 7
	FOR  shift 8
	WHILE  shift 9
	CIN  shift 10
	COUT  shift 11
	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15
	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LFP  shift 5
	SEMI  shift 20
	LP  shift 21
	RETURN  shift 22
	.  reduce 4

	stmt  goto 23
	while_stmt  goto 24
	output_stmt  goto 25
	expr_stmt  goto 26
	if_stmt  goto 27
	input_stmt  goto 28
	func_stmt  goto 29
	func_asked_stmt  goto 30
	return_stmt  goto 31
	block  goto 32
	for_stmt  goto 33
	stmts  goto 56
	var_stmt  goto 35
	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	type_var  goto 40
	term  goto 41
	func_asked_stmt1  goto 42
	expr  goto 43


state 24
	stmt : while_stmt .  (8)

	.  reduce 8


state 25
	stmt : output_stmt .  (12)

	.  reduce 12


state 26
	stmt : expr_stmt .  (5)

	.  reduce 5


state 27
	stmt : if_stmt .  (7)

	.  reduce 7


state 28
	stmt : input_stmt .  (11)

	.  reduce 11


state 29
	stmt : func_stmt .  (13)

	.  reduce 13


state 30
	stmt : func_asked_stmt .  (14)

	.  reduce 14


state 31
	stmt : return_stmt .  (15)

	.  reduce 15


state 32
	stmt : block .  (10)

	.  reduce 10


state 33
	stmt : for_stmt .  (9)

	.  reduce 9


state 34
	block : LFP stmts . RFP

	RFP  shift 57


state 35
	stmt : var_stmt .  (6)

	.  reduce 6


state 36
	or_expr : and_expr .  (33)
	and_expr : and_expr . AND eq_expr

	AND  shift 58
	.  reduce 33


state 37
	expr : or_expr .  (31)
	or_expr : or_expr . OR and_expr

	OR  shift 59
	.  reduce 31


state 38
	eq_expr : eq_expr . RM simple_expr
	eq_expr : eq_expr . NEQ simple_expr
	eq_expr : eq_expr . LM simple_expr
	and_expr : eq_expr .  (35)
	eq_expr : eq_expr . GT simple_expr
	eq_expr : eq_expr . LT simple_expr
	eq_expr : eq_expr . EQ simple_expr
	eq_expr : eq_expr . LE simple_expr
	eq_expr : eq_expr . GE simple_expr

	GT  shift 60
	LT  shift 61
	GE  shift 62
	LE  shift 63
	NEQ  shift 64
	LM  shift 65
	RM  shift 66
	EQ  shift 67
	.  reduce 35


state 39
	eq_expr : simple_expr .  (44)
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr . PLUS simple_expr
	simple_expr : simple_expr . MINUS simple_expr

	PLUS  shift 68
	MINUS  shift 69
	MUL  shift 70
	DIV  shift 71
	MOD  shift 72
	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 44


state 40
	var_stmt : type_var . id_list SEMI
	func_stmt : type_var . ID LP func_var RP block
	func_asked_stmt : type_var . ID ASSIGN func_asked_stmt1

	ID  shift 75
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	and_expr  goto 36
	id_list  goto 76
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 77


state 41
	simple_expr : term .  (52)

	.  reduce 52


state 42
	func_asked_stmt : func_asked_stmt1 .  (71)

	.  reduce 71


state 43
	expr_stmt : expr . SEMI

	SEMI  shift 78


state 44
	if_stmt : IF LP . expr RP stmt ELSE stmt
	if_stmt : IF LP . expr RP stmt

	ID  shift 53
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 79


state 45
	for_stmt : FOR LP . SEMI expr SEMI RP stmt
	for_stmt : FOR LP . expr SEMI expr SEMI RP stmt
	for_stmt : FOR LP . expr SEMI expr SEMI expr RP stmt
	for_stmt : FOR LP . expr SEMI SEMI expr RP stmt
	for_stmt : FOR LP . SEMI expr SEMI expr RP stmt
	for_stmt : FOR LP . SEMI SEMI expr RP stmt
	for_stmt : FOR LP . expr SEMI SEMI RP stmt
	for_stmt : FOR LP . SEMI SEMI RP stmt

	ID  shift 53
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	SEMI  shift 80
	LP  shift 21

	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 81


state 46
	while_stmt : WHILE LP . expr RP stmt

	ID  shift 53
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 82


state 47
	input_stmt : CIN RM . ID SEMI

	ID  shift 83


state 48
	output_stmt : COUT LM . term SEMI

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	term  goto 84


state 49
	expr : ID ASSIGN . expr

	ID  shift 53
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 85


state 50
	func_asked_stmt1 : ID LP . expr RP SEMI

	ID  shift 53
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 86


state 51
	term : ID .  (54)

	.  reduce 54


state 52
	term : NOT term .  (57)

	.  reduce 57


state 53
	expr : ID . ASSIGN expr
	term : ID .  (54)

	ASSIGN  shift 49
	.  reduce 54


state 54
	term : LP expr . RP

	RP  shift 87


state 55
	return_stmt : RETURN term .  (75)

	.  reduce 75


state 56
	stmts : stmt stmts .  (3)

	.  reduce 3


state 57
	block : LFP stmts RFP .  (2)

	.  reduce 2


state 58
	and_expr : and_expr AND . eq_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	eq_expr  goto 88
	simple_expr  goto 39
	term  goto 41


state 59
	or_expr : or_expr OR . and_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	and_expr  goto 89
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41


state 60
	eq_expr : eq_expr GT . simple_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	simple_expr  goto 90
	term  goto 41


state 61
	eq_expr : eq_expr LT . simple_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	simple_expr  goto 91
	term  goto 41


state 62
	eq_expr : eq_expr GE . simple_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	simple_expr  goto 92
	term  goto 41


state 63
	eq_expr : eq_expr LE . simple_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	simple_expr  goto 93
	term  goto 41


state 64
	eq_expr : eq_expr NEQ . simple_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	simple_expr  goto 94
	term  goto 41


state 65
	eq_expr : eq_expr LM . simple_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	simple_expr  goto 95
	term  goto 41


state 66
	eq_expr : eq_expr RM . simple_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	simple_expr  goto 96
	term  goto 41


state 67
	eq_expr : eq_expr EQ . simple_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	simple_expr  goto 97
	term  goto 41


state 68
	simple_expr : simple_expr PLUS . simple_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	simple_expr  goto 98
	term  goto 41


state 69
	simple_expr : simple_expr MINUS . simple_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	simple_expr  goto 99
	term  goto 41


state 70
	simple_expr : simple_expr MUL . simple_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	simple_expr  goto 100
	term  goto 41


state 71
	simple_expr : simple_expr DIV . simple_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	simple_expr  goto 101
	term  goto 41


state 72
	simple_expr : simple_expr MOD . simple_expr

	ID  shift 51
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	simple_expr  goto 102
	term  goto 41


state 73
	simple_expr : simple_expr DPLUS .  (50)

	.  reduce 50


state 74
	simple_expr : simple_expr DMINUS .  (51)

	.  reduce 51


state 75
	expr : ID . ASSIGN expr
	term : ID .  (54)
	func_stmt : type_var ID . LP func_var RP block
	func_asked_stmt : type_var ID . ASSIGN func_asked_stmt1

	ASSIGN  shift 103
	LP  shift 104
	.  reduce 54


state 76
	var_stmt : type_var id_list . SEMI

	SEMI  shift 105


state 77
	id_list : expr . COMMA id_list
	id_list : expr .  (21)

	COMMA  shift 106
	.  reduce 21


state 78
	expr_stmt : expr SEMI .  (28)

	.  reduce 28


state 79
	if_stmt : IF LP expr . RP stmt ELSE stmt
	if_stmt : IF LP expr . RP stmt

	RP  shift 107


state 80
	for_stmt : FOR LP SEMI . expr SEMI RP stmt
	for_stmt : FOR LP SEMI . expr SEMI expr RP stmt
	for_stmt : FOR LP SEMI . SEMI expr RP stmt
	for_stmt : FOR LP SEMI . SEMI RP stmt

	ID  shift 53
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	SEMI  shift 108
	LP  shift 21

	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 109


state 81
	for_stmt : FOR LP expr . SEMI expr SEMI RP stmt
	for_stmt : FOR LP expr . SEMI expr SEMI expr RP stmt
	for_stmt : FOR LP expr . SEMI SEMI expr RP stmt
	for_stmt : FOR LP expr . SEMI SEMI RP stmt

	SEMI  shift 110


state 82
	while_stmt : WHILE LP expr . RP stmt

	RP  shift 111


state 83
	input_stmt : CIN RM ID . SEMI

	SEMI  shift 112


state 84
	output_stmt : COUT LM term . SEMI

	SEMI  shift 113


state 85
	expr : ID ASSIGN expr .  (30)

	.  reduce 30


state 86
	func_asked_stmt1 : ID LP expr . RP SEMI

	RP  shift 114


state 87
	term : LP expr RP .  (53)

	.  reduce 53


state 88
	eq_expr : eq_expr . RM simple_expr
	eq_expr : eq_expr . NEQ simple_expr
	eq_expr : eq_expr . LM simple_expr
	eq_expr : eq_expr . GT simple_expr
	eq_expr : eq_expr . LT simple_expr
	eq_expr : eq_expr . EQ simple_expr
	and_expr : and_expr AND eq_expr .  (34)
	eq_expr : eq_expr . LE simple_expr
	eq_expr : eq_expr . GE simple_expr

	GT  shift 60
	LT  shift 61
	GE  shift 62
	LE  shift 63
	NEQ  shift 64
	LM  shift 65
	RM  shift 66
	EQ  shift 67
	.  reduce 34


state 89
	or_expr : or_expr OR and_expr .  (32)
	and_expr : and_expr . AND eq_expr

	AND  shift 58
	.  reduce 32


state 90
	eq_expr : eq_expr GT simple_expr .  (39)
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr . PLUS simple_expr
	simple_expr : simple_expr . MINUS simple_expr

	PLUS  shift 68
	MINUS  shift 69
	MUL  shift 70
	DIV  shift 71
	MOD  shift 72
	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 39


state 91
	eq_expr : eq_expr LT simple_expr .  (40)
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr . PLUS simple_expr
	simple_expr : simple_expr . MINUS simple_expr

	PLUS  shift 68
	MINUS  shift 69
	MUL  shift 70
	DIV  shift 71
	MOD  shift 72
	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 40


state 92
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr . PLUS simple_expr
	eq_expr : eq_expr GE simple_expr .  (37)
	simple_expr : simple_expr . MINUS simple_expr

	PLUS  shift 68
	MINUS  shift 69
	MUL  shift 70
	DIV  shift 71
	MOD  shift 72
	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 37


state 93
	eq_expr : eq_expr LE simple_expr .  (38)
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr . PLUS simple_expr
	simple_expr : simple_expr . MINUS simple_expr

	PLUS  shift 68
	MINUS  shift 69
	MUL  shift 70
	DIV  shift 71
	MOD  shift 72
	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 38


state 94
	eq_expr : eq_expr NEQ simple_expr .  (41)
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr . PLUS simple_expr
	simple_expr : simple_expr . MINUS simple_expr

	PLUS  shift 68
	MINUS  shift 69
	MUL  shift 70
	DIV  shift 71
	MOD  shift 72
	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 41


state 95
	eq_expr : eq_expr LM simple_expr .  (42)
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr . PLUS simple_expr
	simple_expr : simple_expr . MINUS simple_expr

	PLUS  shift 68
	MINUS  shift 69
	MUL  shift 70
	DIV  shift 71
	MOD  shift 72
	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 42


state 96
	eq_expr : eq_expr RM simple_expr .  (43)
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr . PLUS simple_expr
	simple_expr : simple_expr . MINUS simple_expr

	PLUS  shift 68
	MINUS  shift 69
	MUL  shift 70
	DIV  shift 71
	MOD  shift 72
	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 43


state 97
	eq_expr : eq_expr EQ simple_expr .  (36)
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr . PLUS simple_expr
	simple_expr : simple_expr . MINUS simple_expr

	PLUS  shift 68
	MINUS  shift 69
	MUL  shift 70
	DIV  shift 71
	MOD  shift 72
	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 36


state 98
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr PLUS simple_expr .  (45)
	simple_expr : simple_expr . PLUS simple_expr
	simple_expr : simple_expr . MINUS simple_expr

	MUL  shift 70
	DIV  shift 71
	MOD  shift 72
	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 45


state 99
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr . PLUS simple_expr
	simple_expr : simple_expr MINUS simple_expr .  (46)
	simple_expr : simple_expr . MINUS simple_expr

	MUL  shift 70
	DIV  shift 71
	MOD  shift 72
	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 46


state 100
	simple_expr : simple_expr MUL simple_expr .  (47)
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr . PLUS simple_expr
	simple_expr : simple_expr . MINUS simple_expr

	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 47


state 101
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr DIV simple_expr .  (48)
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr . PLUS simple_expr
	simple_expr : simple_expr . MINUS simple_expr

	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 48


state 102
	simple_expr : simple_expr . MUL simple_expr
	simple_expr : simple_expr . DIV simple_expr
	simple_expr : simple_expr MOD simple_expr .  (49)
	simple_expr : simple_expr . MOD simple_expr
	simple_expr : simple_expr . DPLUS
	simple_expr : simple_expr . DMINUS
	simple_expr : simple_expr . PLUS simple_expr
	simple_expr : simple_expr . MINUS simple_expr

	DPLUS  shift 73
	DMINUS  shift 74
	.  reduce 49


state 103
	expr : ID ASSIGN . expr
	func_asked_stmt : type_var ID ASSIGN . func_asked_stmt1

	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	func_asked_stmt1  goto 115
	expr  goto 85


state 104
	func_stmt : type_var ID LP . func_var RP block

	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15

	func_var  goto 116
	type_var  goto 117
	func_var1  goto 118


state 105
	var_stmt : type_var id_list SEMI .  (24)

	.  reduce 24


state 106
	id_list : expr COMMA . id_list

	ID  shift 53
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21

	and_expr  goto 36
	id_list  goto 119
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 77


state 107
	if_stmt : IF LP expr RP . stmt ELSE stmt
	if_stmt : IF LP expr RP . stmt

	IF  shift 7
	FOR  shift 8
	WHILE  shift 9
	CIN  shift 10
	COUT  shift 11
	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15
	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LFP  shift 5
	SEMI  shift 20
	LP  shift 21
	RETURN  shift 22

	stmt  goto 120
	while_stmt  goto 24
	output_stmt  goto 25
	expr_stmt  goto 26
	if_stmt  goto 27
	input_stmt  goto 28
	func_stmt  goto 29
	func_asked_stmt  goto 30
	return_stmt  goto 31
	block  goto 32
	for_stmt  goto 33
	var_stmt  goto 35
	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	type_var  goto 40
	term  goto 41
	func_asked_stmt1  goto 42
	expr  goto 43


state 108
	for_stmt : FOR LP SEMI SEMI . expr RP stmt
	for_stmt : FOR LP SEMI SEMI . RP stmt

	ID  shift 53
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21
	RP  shift 121

	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 122


state 109
	for_stmt : FOR LP SEMI expr . SEMI RP stmt
	for_stmt : FOR LP SEMI expr . SEMI expr RP stmt

	SEMI  shift 123


state 110
	for_stmt : FOR LP expr SEMI . expr SEMI RP stmt
	for_stmt : FOR LP expr SEMI . expr SEMI expr RP stmt
	for_stmt : FOR LP expr SEMI . SEMI expr RP stmt
	for_stmt : FOR LP expr SEMI . SEMI RP stmt

	ID  shift 53
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	SEMI  shift 124
	LP  shift 21

	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 125


state 111
	while_stmt : WHILE LP expr RP . stmt

	IF  shift 7
	FOR  shift 8
	WHILE  shift 9
	CIN  shift 10
	COUT  shift 11
	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15
	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LFP  shift 5
	SEMI  shift 20
	LP  shift 21
	RETURN  shift 22

	stmt  goto 126
	while_stmt  goto 24
	output_stmt  goto 25
	expr_stmt  goto 26
	if_stmt  goto 27
	input_stmt  goto 28
	func_stmt  goto 29
	func_asked_stmt  goto 30
	return_stmt  goto 31
	block  goto 32
	for_stmt  goto 33
	var_stmt  goto 35
	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	type_var  goto 40
	term  goto 41
	func_asked_stmt1  goto 42
	expr  goto 43


state 112
	input_stmt : CIN RM ID SEMI .  (22)

	.  reduce 22


state 113
	output_stmt : COUT LM term SEMI .  (23)

	.  reduce 23


state 114
	func_asked_stmt1 : ID LP expr RP . SEMI

	SEMI  shift 127


state 115
	func_asked_stmt : type_var ID ASSIGN func_asked_stmt1 .  (70)

	.  reduce 70


state 116
	func_stmt : type_var ID LP func_var . RP block

	RP  shift 128


state 117
	func_var1 : type_var . ID

	ID  shift 129


state 118
	func_var : func_var1 . COMMA func_var
	func_var : func_var1 .  (26)

	COMMA  shift 130
	.  reduce 26


state 119
	id_list : expr COMMA id_list .  (20)

	.  reduce 20


state 120
	if_stmt : IF LP expr RP stmt . ELSE stmt
	if_stmt : IF LP expr RP stmt .  (58)

	ELSE  shift 131
	.  reduce 58


state 121
	for_stmt : FOR LP SEMI SEMI RP . stmt

	IF  shift 7
	FOR  shift 8
	WHILE  shift 9
	CIN  shift 10
	COUT  shift 11
	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15
	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LFP  shift 5
	SEMI  shift 20
	LP  shift 21
	RETURN  shift 22

	stmt  goto 132
	while_stmt  goto 24
	output_stmt  goto 25
	expr_stmt  goto 26
	if_stmt  goto 27
	input_stmt  goto 28
	func_stmt  goto 29
	func_asked_stmt  goto 30
	return_stmt  goto 31
	block  goto 32
	for_stmt  goto 33
	var_stmt  goto 35
	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	type_var  goto 40
	term  goto 41
	func_asked_stmt1  goto 42
	expr  goto 43


state 122
	for_stmt : FOR LP SEMI SEMI expr . RP stmt

	RP  shift 133


state 123
	for_stmt : FOR LP SEMI expr SEMI . RP stmt
	for_stmt : FOR LP SEMI expr SEMI . expr RP stmt

	ID  shift 53
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21
	RP  shift 134

	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 135


state 124
	for_stmt : FOR LP expr SEMI SEMI . expr RP stmt
	for_stmt : FOR LP expr SEMI SEMI . RP stmt

	ID  shift 53
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21
	RP  shift 136

	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 137


state 125
	for_stmt : FOR LP expr SEMI expr . SEMI RP stmt
	for_stmt : FOR LP expr SEMI expr . SEMI expr RP stmt

	SEMI  shift 138


state 126
	while_stmt : WHILE LP expr RP stmt .  (68)

	.  reduce 68


state 127
	func_asked_stmt1 : ID LP expr RP SEMI .  (72)

	.  reduce 72


state 128
	func_stmt : type_var ID LP func_var RP . block

	LFP  shift 5

	block  goto 139


state 129
	func_var1 : type_var ID .  (27)

	.  reduce 27


state 130
	func_var : func_var1 COMMA . func_var

	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15

	func_var  goto 140
	type_var  goto 117
	func_var1  goto 118


state 131
	if_stmt : IF LP expr RP stmt ELSE . stmt

	IF  shift 7
	FOR  shift 8
	WHILE  shift 9
	CIN  shift 10
	COUT  shift 11
	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15
	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LFP  shift 5
	SEMI  shift 20
	LP  shift 21
	RETURN  shift 22

	stmt  goto 141
	while_stmt  goto 24
	output_stmt  goto 25
	expr_stmt  goto 26
	if_stmt  goto 27
	input_stmt  goto 28
	func_stmt  goto 29
	func_asked_stmt  goto 30
	return_stmt  goto 31
	block  goto 32
	for_stmt  goto 33
	var_stmt  goto 35
	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	type_var  goto 40
	term  goto 41
	func_asked_stmt1  goto 42
	expr  goto 43


state 132
	for_stmt : FOR LP SEMI SEMI RP stmt .  (67)

	.  reduce 67


state 133
	for_stmt : FOR LP SEMI SEMI expr RP . stmt

	IF  shift 7
	FOR  shift 8
	WHILE  shift 9
	CIN  shift 10
	COUT  shift 11
	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15
	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LFP  shift 5
	SEMI  shift 20
	LP  shift 21
	RETURN  shift 22

	stmt  goto 142
	while_stmt  goto 24
	output_stmt  goto 25
	expr_stmt  goto 26
	if_stmt  goto 27
	input_stmt  goto 28
	func_stmt  goto 29
	func_asked_stmt  goto 30
	return_stmt  goto 31
	block  goto 32
	for_stmt  goto 33
	var_stmt  goto 35
	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	type_var  goto 40
	term  goto 41
	func_asked_stmt1  goto 42
	expr  goto 43


state 134
	for_stmt : FOR LP SEMI expr SEMI RP . stmt

	IF  shift 7
	FOR  shift 8
	WHILE  shift 9
	CIN  shift 10
	COUT  shift 11
	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15
	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LFP  shift 5
	SEMI  shift 20
	LP  shift 21
	RETURN  shift 22

	stmt  goto 143
	while_stmt  goto 24
	output_stmt  goto 25
	expr_stmt  goto 26
	if_stmt  goto 27
	input_stmt  goto 28
	func_stmt  goto 29
	func_asked_stmt  goto 30
	return_stmt  goto 31
	block  goto 32
	for_stmt  goto 33
	var_stmt  goto 35
	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	type_var  goto 40
	term  goto 41
	func_asked_stmt1  goto 42
	expr  goto 43


state 135
	for_stmt : FOR LP SEMI expr SEMI expr . RP stmt

	RP  shift 144


state 136
	for_stmt : FOR LP expr SEMI SEMI RP . stmt

	IF  shift 7
	FOR  shift 8
	WHILE  shift 9
	CIN  shift 10
	COUT  shift 11
	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15
	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LFP  shift 5
	SEMI  shift 20
	LP  shift 21
	RETURN  shift 22

	stmt  goto 145
	while_stmt  goto 24
	output_stmt  goto 25
	expr_stmt  goto 26
	if_stmt  goto 27
	input_stmt  goto 28
	func_stmt  goto 29
	func_asked_stmt  goto 30
	return_stmt  goto 31
	block  goto 32
	for_stmt  goto 33
	var_stmt  goto 35
	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	type_var  goto 40
	term  goto 41
	func_asked_stmt1  goto 42
	expr  goto 43


state 137
	for_stmt : FOR LP expr SEMI SEMI expr . RP stmt

	RP  shift 146


state 138
	for_stmt : FOR LP expr SEMI expr SEMI . RP stmt
	for_stmt : FOR LP expr SEMI expr SEMI . expr RP stmt

	ID  shift 53
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LP  shift 21
	RP  shift 147

	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	term  goto 41
	expr  goto 148


state 139
	func_stmt : type_var ID LP func_var RP block .  (69)

	.  reduce 69


state 140
	func_var : func_var1 COMMA func_var .  (25)

	.  reduce 25


state 141
	if_stmt : IF LP expr RP stmt ELSE stmt .  (59)

	.  reduce 59


state 142
	for_stmt : FOR LP SEMI SEMI expr RP stmt .  (64)

	.  reduce 64


state 143
	for_stmt : FOR LP SEMI expr SEMI RP stmt .  (65)

	.  reduce 65


state 144
	for_stmt : FOR LP SEMI expr SEMI expr RP . stmt

	IF  shift 7
	FOR  shift 8
	WHILE  shift 9
	CIN  shift 10
	COUT  shift 11
	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15
	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LFP  shift 5
	SEMI  shift 20
	LP  shift 21
	RETURN  shift 22

	stmt  goto 149
	while_stmt  goto 24
	output_stmt  goto 25
	expr_stmt  goto 26
	if_stmt  goto 27
	input_stmt  goto 28
	func_stmt  goto 29
	func_asked_stmt  goto 30
	return_stmt  goto 31
	block  goto 32
	for_stmt  goto 33
	var_stmt  goto 35
	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	type_var  goto 40
	term  goto 41
	func_asked_stmt1  goto 42
	expr  goto 43


state 145
	for_stmt : FOR LP expr SEMI SEMI RP stmt .  (66)

	.  reduce 66


state 146
	for_stmt : FOR LP expr SEMI SEMI expr RP . stmt

	IF  shift 7
	FOR  shift 8
	WHILE  shift 9
	CIN  shift 10
	COUT  shift 11
	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15
	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LFP  shift 5
	SEMI  shift 20
	LP  shift 21
	RETURN  shift 22

	stmt  goto 150
	while_stmt  goto 24
	output_stmt  goto 25
	expr_stmt  goto 26
	if_stmt  goto 27
	input_stmt  goto 28
	func_stmt  goto 29
	func_asked_stmt  goto 30
	return_stmt  goto 31
	block  goto 32
	for_stmt  goto 33
	var_stmt  goto 35
	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	type_var  goto 40
	term  goto 41
	func_asked_stmt1  goto 42
	expr  goto 43


state 147
	for_stmt : FOR LP expr SEMI expr SEMI RP . stmt

	IF  shift 7
	FOR  shift 8
	WHILE  shift 9
	CIN  shift 10
	COUT  shift 11
	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15
	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LFP  shift 5
	SEMI  shift 20
	LP  shift 21
	RETURN  shift 22

	stmt  goto 151
	while_stmt  goto 24
	output_stmt  goto 25
	expr_stmt  goto 26
	if_stmt  goto 27
	input_stmt  goto 28
	func_stmt  goto 29
	func_asked_stmt  goto 30
	return_stmt  goto 31
	block  goto 32
	for_stmt  goto 33
	var_stmt  goto 35
	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	type_var  goto 40
	term  goto 41
	func_asked_stmt1  goto 42
	expr  goto 43


state 148
	for_stmt : FOR LP expr SEMI expr SEMI expr . RP stmt

	RP  shift 152


state 149
	for_stmt : FOR LP SEMI expr SEMI expr RP stmt .  (61)

	.  reduce 61


state 150
	for_stmt : FOR LP expr SEMI SEMI expr RP stmt .  (62)

	.  reduce 62


state 151
	for_stmt : FOR LP expr SEMI expr SEMI RP stmt .  (63)

	.  reduce 63


state 152
	for_stmt : FOR LP expr SEMI expr SEMI expr RP . stmt

	IF  shift 7
	FOR  shift 8
	WHILE  shift 9
	CIN  shift 10
	COUT  shift 11
	INT  shift 12
	CHAR  shift 13
	VOID  shift 14
	BOOL  shift 15
	ID  shift 16
	NUMBER  shift 17
	Constchar  shift 18
	NOT  shift 19
	LFP  shift 5
	SEMI  shift 20
	LP  shift 21
	RETURN  shift 22

	stmt  goto 153
	while_stmt  goto 24
	output_stmt  goto 25
	expr_stmt  goto 26
	if_stmt  goto 27
	input_stmt  goto 28
	func_stmt  goto 29
	func_asked_stmt  goto 30
	return_stmt  goto 31
	block  goto 32
	for_stmt  goto 33
	var_stmt  goto 35
	and_expr  goto 36
	or_expr  goto 37
	eq_expr  goto 38
	simple_expr  goto 39
	type_var  goto 40
	term  goto 41
	func_asked_stmt1  goto 42
	expr  goto 43


state 153
	for_stmt : FOR LP expr SEMI expr SEMI expr RP stmt .  (60)

	.  reduce 60


Rules never reduced
	expr_func : expr COMMA expr_func  (73)
	expr_func : expr  (74)


##############################################################################
# Summary
##############################################################################

42 token(s), 27 nonterminal(s)
76 grammar rule(s), 154 state(s)


##############################################################################
# End of File
##############################################################################
