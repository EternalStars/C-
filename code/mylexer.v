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
# mylexer.v
# Lex verbose file generated from mylexer.l.
# 
# Date: 12/26/19
# Time: 18:51:03
# 
# ALex Version: 2.07
#############################################################################


#############################################################################
# Expressions
#############################################################################

    1  \/\*([^\*"]|(\".*\")|((\*)+[^\/]?))*\*\/

    2  \/\/[^\n]*

    3  [ \n\t]*+

    4  ","

    5  ";"

    6  "("

    7  ")"

    8  "{"

    9  "}"

   10  "["

   11  "]"

   12  "if"

   13  "else"

   14  "while"

   15  "for"

   16  "cin"

   17  "cout"

   18  "void"

   19  "int"

   20  "char"

   21  "bool"

   22  "string"

   23  "="

   24  "main"

   25  "return"

   26  "+"

   27  "-"

   28  "*"

   29  "/"

   30  "%"

   31  "++"

   32  "--"

   33  "=="

   34  "<<"

   35  ">>"

   36  ">="

   37  "<="

   38  ">"

   39  "<"

   40  "!="

   41  "&&"

   42  "||"

   43  "!"

   44  [A-Za-z_]([A-Za-z_]|[0-9])*

   45  [0-9]+(\.[0-9]+)?(E[+-]?[0-9]+)?

   46  \'.\'


#############################################################################
# States
#############################################################################

state 1
	INITIAL

	0x09 - 0x0a (2)    goto 3
	0x20               goto 3
	0x21               goto 4
	0x25               goto 5
	0x26               goto 6
	0x27               goto 7
	0x28               goto 8
	0x29               goto 9
	0x2a               goto 10
	0x2b               goto 11
	0x2c               goto 12
	0x2d               goto 13
	0x2f               goto 14
	0x30 - 0x39 (10)   goto 15
	0x3b               goto 16
	0x3c               goto 17
	0x3d               goto 18
	0x3e               goto 19
	0x41 - 0x5a (26)   goto 20
	0x5b               goto 21
	0x5d               goto 22
	0x5f               goto 20
	0x61               goto 20
	0x62               goto 23
	0x63               goto 24
	0x64               goto 20
	0x65               goto 25
	0x66               goto 26
	0x67 - 0x68 (2)    goto 20
	0x69               goto 27
	0x6a - 0x6c (3)    goto 20
	0x6d               goto 28
	0x6e - 0x71 (4)    goto 20
	0x72               goto 29
	0x73               goto 30
	0x74 - 0x75 (2)    goto 20
	0x76               goto 31
	0x77               goto 32
	0x78 - 0x7a (3)    goto 20
	0x7b               goto 33
	0x7c               goto 34
	0x7d               goto 35


state 2
	^INITIAL

	0x09 - 0x0a (2)    goto 3
	0x20               goto 3
	0x21               goto 4
	0x25               goto 5
	0x26               goto 6
	0x27               goto 7
	0x28               goto 8
	0x29               goto 9
	0x2a               goto 10
	0x2b               goto 11
	0x2c               goto 12
	0x2d               goto 13
	0x2f               goto 14
	0x30 - 0x39 (10)   goto 15
	0x3b               goto 16
	0x3c               goto 17
	0x3d               goto 18
	0x3e               goto 19
	0x41 - 0x5a (26)   goto 20
	0x5b               goto 21
	0x5d               goto 22
	0x5f               goto 20
	0x61               goto 20
	0x62               goto 23
	0x63               goto 24
	0x64               goto 20
	0x65               goto 25
	0x66               goto 26
	0x67 - 0x68 (2)    goto 20
	0x69               goto 27
	0x6a - 0x6c (3)    goto 20
	0x6d               goto 28
	0x6e - 0x71 (4)    goto 20
	0x72               goto 29
	0x73               goto 30
	0x74 - 0x75 (2)    goto 20
	0x76               goto 31
	0x77               goto 32
	0x78 - 0x7a (3)    goto 20
	0x7b               goto 33
	0x7c               goto 34
	0x7d               goto 35


state 3
	0x09 - 0x0a (2)    goto 3
	0x20               goto 3

	match 3


state 4
	0x3d               goto 36

	match 43


state 5
	match 30


state 6
	0x26               goto 37


state 7
	0x00 - 0x09 (10)   goto 38
	0x0b - 0xff (245)  goto 38


state 8
	match 6


state 9
	match 7


state 10
	match 28


state 11
	0x2b               goto 39

	match 26


state 12
	match 4


state 13
	0x2d               goto 40

	match 27


state 14
	0x2a               goto 41
	0x2f               goto 42

	match 29


state 15
	0x2e               goto 43
	0x30 - 0x39 (10)   goto 15
	0x45               goto 44

	match 45


state 16
	match 5


state 17
	0x3c               goto 45
	0x3d               goto 46

	match 39


state 18
	0x3d               goto 47

	match 23


state 19
	0x3d               goto 48
	0x3e               goto 49

	match 38


state 20
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 44


state 21
	match 10


state 22
	match 11


state 23
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x6e (14)   goto 20
	0x6f               goto 50
	0x70 - 0x7a (11)   goto 20

	match 44


state 24
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x67 (7)    goto 20
	0x68               goto 51
	0x69               goto 52
	0x6a - 0x6e (5)    goto 20
	0x6f               goto 53
	0x70 - 0x7a (11)   goto 20

	match 44


state 25
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x6b (11)   goto 20
	0x6c               goto 54
	0x6d - 0x7a (14)   goto 20

	match 44


state 26
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x6e (14)   goto 20
	0x6f               goto 55
	0x70 - 0x7a (11)   goto 20

	match 44


state 27
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x65 (5)    goto 20
	0x66               goto 56
	0x67 - 0x6d (7)    goto 20
	0x6e               goto 57
	0x6f - 0x7a (12)   goto 20

	match 44


state 28
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61               goto 58
	0x62 - 0x7a (25)   goto 20

	match 44


state 29
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x64 (4)    goto 20
	0x65               goto 59
	0x66 - 0x7a (21)   goto 20

	match 44


state 30
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x73 (19)   goto 20
	0x74               goto 60
	0x75 - 0x7a (6)    goto 20

	match 44


state 31
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x6e (14)   goto 20
	0x6f               goto 61
	0x70 - 0x7a (11)   goto 20

	match 44


state 32
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x67 (7)    goto 20
	0x68               goto 62
	0x69 - 0x7a (18)   goto 20

	match 44


state 33
	match 8


state 34
	0x7c               goto 63


state 35
	match 9


state 36
	match 40


state 37
	match 41


state 38
	0x27               goto 64


state 39
	match 31


state 40
	match 32


state 41
	0x00 - 0x21 (34)   goto 41
	0x22               goto 65
	0x23 - 0x29 (7)    goto 41
	0x2a               goto 66
	0x2b - 0xff (213)  goto 41


state 42
	0x00 - 0x09 (10)   goto 42
	0x0b - 0xff (245)  goto 42

	match 2


state 43
	0x30 - 0x39 (10)   goto 67


state 44
	0x2b               goto 68
	0x2d               goto 68
	0x30 - 0x39 (10)   goto 69


state 45
	match 34


state 46
	match 37


state 47
	match 33


state 48
	match 36


state 49
	match 35


state 50
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x6e (14)   goto 20
	0x6f               goto 70
	0x70 - 0x7a (11)   goto 20

	match 44


state 51
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61               goto 71
	0x62 - 0x7a (25)   goto 20

	match 44


state 52
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x6d (13)   goto 20
	0x6e               goto 72
	0x6f - 0x7a (12)   goto 20

	match 44


state 53
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x74 (20)   goto 20
	0x75               goto 73
	0x76 - 0x7a (5)    goto 20

	match 44


state 54
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x72 (18)   goto 20
	0x73               goto 74
	0x74 - 0x7a (7)    goto 20

	match 44


state 55
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x71 (17)   goto 20
	0x72               goto 75
	0x73 - 0x7a (8)    goto 20

	match 44


state 56
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 12


state 57
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x73 (19)   goto 20
	0x74               goto 76
	0x75 - 0x7a (6)    goto 20

	match 44


state 58
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x68 (8)    goto 20
	0x69               goto 77
	0x6a - 0x7a (17)   goto 20

	match 44


state 59
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x73 (19)   goto 20
	0x74               goto 78
	0x75 - 0x7a (6)    goto 20

	match 44


state 60
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x71 (17)   goto 20
	0x72               goto 79
	0x73 - 0x7a (8)    goto 20

	match 44


state 61
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x68 (8)    goto 20
	0x69               goto 80
	0x6a - 0x7a (17)   goto 20

	match 44


state 62
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x68 (8)    goto 20
	0x69               goto 81
	0x6a - 0x7a (17)   goto 20

	match 44


state 63
	match 42


state 64
	match 46


state 65
	0x00 - 0x09 (10)   goto 65
	0x0b - 0x21 (23)   goto 65
	0x22               goto 82
	0x23 - 0xff (221)  goto 65


state 66
	0x00 - 0x21 (34)   goto 41
	0x22               goto 82
	0x23 - 0x29 (7)    goto 41
	0x2a               goto 66
	0x2b - 0x2e (4)    goto 41
	0x2f               goto 83
	0x30 - 0xff (208)  goto 41


state 67
	0x30 - 0x39 (10)   goto 67
	0x45               goto 44

	match 45


state 68
	0x30 - 0x39 (10)   goto 69


state 69
	0x30 - 0x39 (10)   goto 69

	match 45


state 70
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x6b (11)   goto 20
	0x6c               goto 84
	0x6d - 0x7a (14)   goto 20

	match 44


state 71
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x71 (17)   goto 20
	0x72               goto 85
	0x73 - 0x7a (8)    goto 20

	match 44


state 72
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 16


state 73
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x73 (19)   goto 20
	0x74               goto 86
	0x75 - 0x7a (6)    goto 20

	match 44


state 74
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x64 (4)    goto 20
	0x65               goto 87
	0x66 - 0x7a (21)   goto 20

	match 44


state 75
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 15


state 76
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 19


state 77
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x6d (13)   goto 20
	0x6e               goto 88
	0x6f - 0x7a (12)   goto 20

	match 44


state 78
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x74 (20)   goto 20
	0x75               goto 89
	0x76 - 0x7a (5)    goto 20

	match 44


state 79
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x68 (8)    goto 20
	0x69               goto 90
	0x6a - 0x7a (17)   goto 20

	match 44


state 80
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x63 (3)    goto 20
	0x64               goto 91
	0x65 - 0x7a (22)   goto 20

	match 44


state 81
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x6b (11)   goto 20
	0x6c               goto 92
	0x6d - 0x7a (14)   goto 20

	match 44


state 82
	0x00 - 0x09 (10)   goto 82
	0x0a               goto 41
	0x0b - 0x21 (23)   goto 82
	0x22               goto 82
	0x23 - 0x29 (7)    goto 82
	0x2a               goto 93
	0x2b - 0xff (213)  goto 82


state 83
	0x00 - 0x21 (34)   goto 41
	0x22               goto 65
	0x23 - 0x29 (7)    goto 41
	0x2a               goto 66
	0x2b - 0xff (213)  goto 41

	match 1


state 84
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 21


state 85
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 20


state 86
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 17


state 87
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 13


state 88
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 24


state 89
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x71 (17)   goto 20
	0x72               goto 94
	0x73 - 0x7a (8)    goto 20

	match 44


state 90
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x6d (13)   goto 20
	0x6e               goto 95
	0x6f - 0x7a (12)   goto 20

	match 44


state 91
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 18


state 92
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x64 (4)    goto 20
	0x65               goto 96
	0x66 - 0x7a (21)   goto 20

	match 44


state 93
	0x00 - 0x09 (10)   goto 82
	0x0a               goto 41
	0x0b - 0x21 (23)   goto 82
	0x22               goto 82
	0x23 - 0x29 (7)    goto 82
	0x2a               goto 93
	0x2b - 0x2e (4)    goto 82
	0x2f               goto 97
	0x30 - 0xff (208)  goto 82


state 94
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x6d (13)   goto 20
	0x6e               goto 98
	0x6f - 0x7a (12)   goto 20

	match 44


state 95
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x66 (6)    goto 20
	0x67               goto 99
	0x68 - 0x7a (19)   goto 20

	match 44


state 96
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 14


state 97
	0x00 - 0x09 (10)   goto 82
	0x0a               goto 41
	0x0b - 0x21 (23)   goto 82
	0x22               goto 82
	0x23 - 0x29 (7)    goto 82
	0x2a               goto 93
	0x2b - 0xff (213)  goto 82

	match 1


state 98
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 25


state 99
	0x30 - 0x39 (10)   goto 20
	0x41 - 0x5a (26)   goto 20
	0x5f               goto 20
	0x61 - 0x7a (26)   goto 20

	match 22


#############################################################################
# Summary
#############################################################################

1 start state(s)
46 expression(s), 99 state(s)


#############################################################################
# End of File
#############################################################################
