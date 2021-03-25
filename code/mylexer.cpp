/****************************************************************************
*                     U N R E G I S T E R E D   C O P Y
* 
* You are on day 70 of your 30 day trial period.
* 
* This file was produced by an UNREGISTERED COPY of Parser Generator. It is
* for evaluation purposes only. If you continue to use Parser Generator 30
* days after installation then you are required to purchase a license. For
* more information see the online help or go to the Bumble-Bee Software
* homepage at:
* 
* http://www.bumblebeesoftware.com
* 
* This notice must remain present in the file. It cannot be removed.
****************************************************************************/

/****************************************************************************
* mylexer.cpp
* C++ source file generated from mylexer.l.
* 
* Date: 12/26/19
* Time: 18:51:03
* 
* ALex Version: 2.07
****************************************************************************/

#include <yyclex.h>

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#line 1 ".\\mylexer.l"

#include "myparser.h"
#include <stdlib.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
#pragma warning(disable:4996)

#define MAX 6
enum NodeType{Stmt,Expr,Decl};
enum Statement{If,While,For,Block,Input,Output,Func,Return,Expr_func,Func_asked,Empty};
enum Expression{Op,Const_num,Const_char,Idk,Type};
enum Declaration{Var,FuncVar};
enum Type1{Int,Char,Void,Bool};


extern map<string,Type1> str_index;

struct TreeNode
{
  struct TreeNode*child[MAX];
  struct TreeNode*sibling;//由于匹配的时候可以匹配出一整句话，故可以知道其兄弟节点，但是无法知道其父节点
  int nodekind;
  int kind;
  
  Type1 type;
  union{
   int op;//由于是token定义，返回int型操作符号的值
   int val;//数字的值
   char charval;
   char* symbol;//id的值
  }attr;//只有id,const和op类型有attr值
  int lineo=0;//节点序号
};

extern int line;

#line 81 "mylexer.cpp"
// repeated because of possible precompiled header
#include <yyclex.h>

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#include ".\mylexer.h"

/////////////////////////////////////////////////////////////////////////////
// constructor

YYLEXERNAME::YYLEXERNAME()
{
	yytables();
}

/////////////////////////////////////////////////////////////////////////////
// destructor

YYLEXERNAME::~YYLEXERNAME()
{
}

#ifndef YYTEXT_SIZE
#define YYTEXT_SIZE 100
#endif
#ifndef YYUNPUT_SIZE
#define YYUNPUT_SIZE YYTEXT_SIZE
#endif
#ifndef YYTEXT_MAX
#define YYTEXT_MAX 0
#endif
#ifndef YYUNPUT_MAX
#define YYUNPUT_MAX YYTEXT_MAX
#endif

/****************************************************************************
* N O T E
* 
* If the compiler generates a YYLEXERNAME error then you have not declared
* the name of the lexical analyser. The easiest way to do this is to use a
* name declaration. This is placed in the declarations section of your Lex
* source file and is introduced with the %name keyword. For instance, the
* following name declaration declares the lexer mylexer:
* 
* %name mylexer
* 
* For more information see help.
****************************************************************************/

// backwards compatability with lex
#ifdef input
int YYLEXERNAME::yyinput()
{
	return input();
}
#else
#define input yyinput
#endif

#ifdef output
void YYLEXERNAME::yyoutput(int ch)
{
	output(ch);
}
#else
#define output yyoutput
#endif

#ifdef unput
void YYLEXERNAME::yyunput(int ch)
{
	unput(ch);
}
#else
#define unput yyunput
#endif

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn -rch		// <warning: unreachable code> off
#endif
#endif

int YYLEXERNAME::yyaction(int action)
{
#line 59 ".\\mylexer.l"

	// extract yylval for use later on in actions
	YYSTYPE YYFAR& yylval = *(YYSTYPE YYFAR*)yyparserptr->yylvalptr;

#line 178 "mylexer.cpp"
	yyreturnflg = yytrue;
	switch (action) {
	case 1:
		{
#line 67 ".\\mylexer.l"
/* do nothing */
#line 185 "mylexer.cpp"
		}
		break;
	case 2:
		{
#line 68 ".\\mylexer.l"
/* do nothing */
#line 192 "mylexer.cpp"
		}
		break;
	case 3:
		{
#line 69 ".\\mylexer.l"
/*doing nothing*/
#line 199 "mylexer.cpp"
		}
		break;
	case 4:
		{
#line 70 ".\\mylexer.l"
return COMMA;
#line 206 "mylexer.cpp"
		}
		break;
	case 5:
		{
#line 71 ".\\mylexer.l"
return SEMI;
#line 213 "mylexer.cpp"
		}
		break;
	case 6:
		{
#line 72 ".\\mylexer.l"
return LP;
#line 220 "mylexer.cpp"
		}
		break;
	case 7:
		{
#line 73 ".\\mylexer.l"
return RP;
#line 227 "mylexer.cpp"
		}
		break;
	case 8:
		{
#line 74 ".\\mylexer.l"
return LFP;
#line 234 "mylexer.cpp"
		}
		break;
	case 9:
		{
#line 75 ".\\mylexer.l"
return RFP;
#line 241 "mylexer.cpp"
		}
		break;
	case 10:
		{
#line 76 ".\\mylexer.l"
return LSP;
#line 248 "mylexer.cpp"
		}
		break;
	case 11:
		{
#line 77 ".\\mylexer.l"
return RSP;
#line 255 "mylexer.cpp"
		}
		break;
	case 12:
		{
#line 79 ".\\mylexer.l"
return IF;
#line 262 "mylexer.cpp"
		}
		break;
	case 13:
		{
#line 80 ".\\mylexer.l"
return ELSE;
#line 269 "mylexer.cpp"
		}
		break;
	case 14:
		{
#line 81 ".\\mylexer.l"
return WHILE;
#line 276 "mylexer.cpp"
		}
		break;
	case 15:
		{
#line 82 ".\\mylexer.l"
return FOR;
#line 283 "mylexer.cpp"
		}
		break;
	case 16:
		{
#line 83 ".\\mylexer.l"
return CIN;
#line 290 "mylexer.cpp"
		}
		break;
	case 17:
		{
#line 84 ".\\mylexer.l"
return COUT;
#line 297 "mylexer.cpp"
		}
		break;
	case 18:
		{
#line 85 ".\\mylexer.l"
return VOID;
#line 304 "mylexer.cpp"
		}
		break;
	case 19:
		{
#line 86 ".\\mylexer.l"
return INT;
#line 311 "mylexer.cpp"
		}
		break;
	case 20:
		{
#line 87 ".\\mylexer.l"
return CHAR;
#line 318 "mylexer.cpp"
		}
		break;
	case 21:
		{
#line 88 ".\\mylexer.l"
return BOOL;
#line 325 "mylexer.cpp"
		}
		break;
	case 22:
		{
#line 89 ".\\mylexer.l"
return STRING;
#line 332 "mylexer.cpp"
		}
		break;
	case 23:
		{
#line 90 ".\\mylexer.l"
return ASSIGN;
#line 339 "mylexer.cpp"
		}
		break;
	case 24:
		{
#line 91 ".\\mylexer.l"
return MAIN;
#line 346 "mylexer.cpp"
		}
		break;
	case 25:
		{
#line 92 ".\\mylexer.l"
return RETURN;
#line 353 "mylexer.cpp"
		}
		break;
	case 26:
		{
#line 94 ".\\mylexer.l"
return PLUS;
#line 360 "mylexer.cpp"
		}
		break;
	case 27:
		{
#line 95 ".\\mylexer.l"
return MINUS;
#line 367 "mylexer.cpp"
		}
		break;
	case 28:
		{
#line 96 ".\\mylexer.l"
return MUL;
#line 374 "mylexer.cpp"
		}
		break;
	case 29:
		{
#line 97 ".\\mylexer.l"
return DIV;
#line 381 "mylexer.cpp"
		}
		break;
	case 30:
		{
#line 98 ".\\mylexer.l"
return MOD;
#line 388 "mylexer.cpp"
		}
		break;
	case 31:
		{
#line 99 ".\\mylexer.l"
return DPLUS;
#line 395 "mylexer.cpp"
		}
		break;
	case 32:
		{
#line 100 ".\\mylexer.l"
return DMINUS;
#line 402 "mylexer.cpp"
		}
		break;
	case 33:
		{
#line 101 ".\\mylexer.l"
return EQ;
#line 409 "mylexer.cpp"
		}
		break;
	case 34:
		{
#line 103 ".\\mylexer.l"
return LM;
#line 416 "mylexer.cpp"
		}
		break;
	case 35:
		{
#line 104 ".\\mylexer.l"
return RM;
#line 423 "mylexer.cpp"
		}
		break;
	case 36:
		{
#line 105 ".\\mylexer.l"
return GE;
#line 430 "mylexer.cpp"
		}
		break;
	case 37:
		{
#line 106 ".\\mylexer.l"
return LE;
#line 437 "mylexer.cpp"
		}
		break;
	case 38:
		{
#line 107 ".\\mylexer.l"
return GT;
#line 444 "mylexer.cpp"
		}
		break;
	case 39:
		{
#line 108 ".\\mylexer.l"
return LT;
#line 451 "mylexer.cpp"
		}
		break;
	case 40:
		{
#line 109 ".\\mylexer.l"
return NEQ;
#line 458 "mylexer.cpp"
		}
		break;
	case 41:
		{
#line 110 ".\\mylexer.l"
return AND;
#line 465 "mylexer.cpp"
		}
		break;
	case 42:
		{
#line 111 ".\\mylexer.l"
return OR;
#line 472 "mylexer.cpp"
		}
		break;
	case 43:
		{
#line 112 ".\\mylexer.l"
return NOT;
#line 479 "mylexer.cpp"
		}
		break;
	case 44:
		{
#line 115 ".\\mylexer.l"

					struct TreeNode * t = (TreeNode *)malloc(sizeof(TreeNode));
					for(int i=0;i<MAX;i++)
						t->child[i]=NULL;
					t->sibling=NULL;
					t->nodekind=Expr;
					t->kind=Idk;
					t->type=Void;
					t->lineo=line++;
					
					//由于是字符串指针，所以注意要进行深拷贝
					//否则yytext最后的值是}，会赋给所有的symbol
					t->attr.symbol=new char[10];
					strncpy(t->attr.symbol, yytext, strlen(yytext) + 1); 
					string str;
						for(int i=0;i<strlen(t->attr.symbol);i++)str+=t->attr.symbol[i];
						if(str_index.find(str)==str_index.end()){
						str_index[str]=Void;
						}
						else {t->type=str_index[str];}
					yylval=t;
					return ID;
				
#line 508 "mylexer.cpp"
		}
		break;
	case 45:
		{
#line 138 ".\\mylexer.l"

			struct TreeNode * t = (TreeNode *)malloc(sizeof(TreeNode));
			for(int i=0;i<MAX;i++)
					t->child[i]=NULL;
				t->sibling=NULL;
				t->nodekind=Expr;
				t->kind=Const_num;
				t->type=Int;
				t->lineo=line++;
				t->attr.val=atoi(yytext);
				yylval=t;
				return NUMBER;
		
#line 527 "mylexer.cpp"
		}
		break;
	case 46:
		{
#line 151 ".\\mylexer.l"

			struct TreeNode * t = (TreeNode *)malloc(sizeof(TreeNode));
			for(int i=0;i<MAX;i++)
					t->child[i]=NULL;
				t->sibling=NULL;
				t->nodekind=Expr;
				t->kind=Const_char;
				t->type=Char;
				t->lineo=line++;
				t->attr.charval=yytext[1];
				yylval=t;
				return Constchar;
		
#line 546 "mylexer.cpp"
		}
		break;
	default:
		yyassert(0);
		break;
	}
	yyreturnflg = yyfalse;
	return 0;
}

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn .rch		// <warning: unreachable code> to the old state
#endif
#endif

void YYLEXERNAME::yytables()
{
	yystext_size = YYTEXT_SIZE;
	yysunput_size = YYUNPUT_SIZE;
	yytext_max = YYTEXT_MAX;
	yyunput_max = YYUNPUT_MAX;

	static const yymatch_t YYNEARFAR YYBASED_CODE match[] = {
		0
	};
	yymatch = match;

	yytransitionmax = 208;
	static const yytransition_t YYNEARFAR YYBASED_CODE transition[] = {
		{ 0, 0 },
		{ 3, 1 },
		{ 3, 1 },
		{ 0, 65 },
		{ 82, 66 },
		{ 36, 4 },
		{ 41, 97 },
		{ 67, 67 },
		{ 67, 67 },
		{ 67, 67 },
		{ 67, 67 },
		{ 67, 67 },
		{ 67, 67 },
		{ 67, 67 },
		{ 67, 67 },
		{ 67, 67 },
		{ 67, 67 },
		{ 83, 66 },
		{ 56, 27 },
		{ 68, 44 },
		{ 58, 28 },
		{ 68, 44 },
		{ 45, 17 },
		{ 46, 17 },
		{ 3, 1 },
		{ 4, 1 },
		{ 57, 27 },
		{ 82, 65 },
		{ 44, 67 },
		{ 5, 1 },
		{ 6, 1 },
		{ 7, 1 },
		{ 8, 1 },
		{ 9, 1 },
		{ 10, 1 },
		{ 11, 1 },
		{ 12, 1 },
		{ 13, 1 },
		{ 93, 97 },
		{ 14, 1 },
		{ 15, 1 },
		{ 15, 1 },
		{ 15, 1 },
		{ 15, 1 },
		{ 15, 1 },
		{ 15, 1 },
		{ 15, 1 },
		{ 15, 1 },
		{ 15, 1 },
		{ 15, 1 },
		{ 65, 83 },
		{ 16, 1 },
		{ 17, 1 },
		{ 18, 1 },
		{ 19, 1 },
		{ 3, 3 },
		{ 3, 3 },
		{ 43, 15 },
		{ 66, 83 },
		{ 15, 15 },
		{ 15, 15 },
		{ 15, 15 },
		{ 15, 15 },
		{ 15, 15 },
		{ 15, 15 },
		{ 15, 15 },
		{ 15, 15 },
		{ 15, 15 },
		{ 15, 15 },
		{ 51, 24 },
		{ 52, 24 },
		{ 59, 29 },
		{ 41, 14 },
		{ 48, 19 },
		{ 49, 19 },
		{ 60, 30 },
		{ 53, 24 },
		{ 42, 14 },
		{ 3, 3 },
		{ 61, 31 },
		{ 62, 32 },
		{ 63, 34 },
		{ 64, 38 },
		{ 21, 1 },
		{ 0, 42 },
		{ 22, 1 },
		{ 0, 43 },
		{ 37, 6 },
		{ 70, 50 },
		{ 71, 51 },
		{ 23, 1 },
		{ 24, 1 },
		{ 72, 52 },
		{ 25, 1 },
		{ 26, 1 },
		{ 73, 53 },
		{ 74, 54 },
		{ 27, 1 },
		{ 75, 55 },
		{ 76, 57 },
		{ 77, 58 },
		{ 28, 1 },
		{ 78, 59 },
		{ 79, 60 },
		{ 80, 61 },
		{ 0, 7 },
		{ 29, 1 },
		{ 30, 1 },
		{ 81, 62 },
		{ 47, 18 },
		{ 31, 1 },
		{ 32, 1 },
		{ 39, 11 },
		{ 50, 23 },
		{ 84, 70 },
		{ 33, 1 },
		{ 34, 1 },
		{ 35, 1 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 85, 71 },
		{ 86, 73 },
		{ 87, 74 },
		{ 88, 77 },
		{ 89, 78 },
		{ 90, 79 },
		{ 91, 80 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 92, 81 },
		{ 40, 13 },
		{ 94, 89 },
		{ 95, 90 },
		{ 20, 99 },
		{ 96, 92 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 20, 99 },
		{ 69, 69 },
		{ 69, 69 },
		{ 69, 69 },
		{ 69, 69 },
		{ 69, 69 },
		{ 69, 69 },
		{ 69, 69 },
		{ 69, 69 },
		{ 69, 69 },
		{ 69, 69 },
		{ 97, 93 },
		{ 98, 94 },
		{ 99, 95 },
		{ 54, 25 },
		{ 55, 26 }
	};
	yytransition = transition;

	static const yystate_t YYNEARFAR YYBASED_CODE state[] = {
		{ 0, 0, 0 },
		{ 99, -8, 0 },
		{ 1, 0, 0 },
		{ 0, 46, 3 },
		{ 0, -56, 43 },
		{ 0, 0, 30 },
		{ 0, 49, 0 },
		{ -38, 95, 0 },
		{ 0, 0, 6 },
		{ 0, 0, 7 },
		{ 0, 0, 28 },
		{ 0, 69, 26 },
		{ 0, 0, 4 },
		{ 0, 117, 27 },
		{ 0, 30, 29 },
		{ 67, 11, 45 },
		{ 0, 0, 5 },
		{ 0, -38, 39 },
		{ 0, 48, 23 },
		{ 0, 12, 38 },
		{ 99, 0, 44 },
		{ 0, 0, 10 },
		{ 0, 0, 11 },
		{ 99, 2, 44 },
		{ 99, -35, 44 },
		{ 99, 98, 44 },
		{ 99, 96, 44 },
		{ 99, -84, 44 },
		{ 99, -77, 44 },
		{ 99, -30, 44 },
		{ 99, -41, 44 },
		{ 99, -32, 44 },
		{ 99, -24, 44 },
		{ 0, 0, 8 },
		{ 0, -43, 0 },
		{ 0, 0, 9 },
		{ 0, 0, 40 },
		{ 0, 0, 41 },
		{ 0, 43, 0 },
		{ 0, 0, 31 },
		{ 0, 0, 32 },
		{ 83, 0, 0 },
		{ -42, 74, 2 },
		{ 67, 17, 0 },
		{ 69, -24, 0 },
		{ 0, 0, 34 },
		{ 0, 0, 37 },
		{ 0, 0, 33 },
		{ 0, 0, 36 },
		{ 0, 0, 35 },
		{ 99, -23, 44 },
		{ 99, -8, 44 },
		{ 99, -18, 44 },
		{ 99, -22, 44 },
		{ 99, -19, 44 },
		{ 99, -16, 44 },
		{ 99, 0, 12 },
		{ 99, -17, 44 },
		{ 99, -5, 44 },
		{ 99, -14, 44 },
		{ 99, -11, 44 },
		{ 99, -1, 44 },
		{ 99, 3, 44 },
		{ 0, 0, 42 },
		{ 0, 0, 46 },
		{ -65, -7, 0 },
		{ 83, -30, 0 },
		{ 0, -41, 45 },
		{ 69, 0, 0 },
		{ 0, 145, 45 },
		{ 99, 6, 44 },
		{ 99, 14, 44 },
		{ 99, 0, 16 },
		{ 99, 13, 44 },
		{ 99, 29, 44 },
		{ 99, 0, 15 },
		{ 99, 0, 19 },
		{ 99, 21, 44 },
		{ 99, 15, 44 },
		{ 99, 28, 44 },
		{ 99, 34, 44 },
		{ 99, 53, 44 },
		{ 97, 0, 0 },
		{ -41, 16, 1 },
		{ 99, 0, 21 },
		{ 99, 0, 20 },
		{ 99, 0, 17 },
		{ 99, 0, 13 },
		{ 99, 0, 24 },
		{ 99, 49, 44 },
		{ 99, 54, 44 },
		{ 99, 0, 18 },
		{ 99, 65, 44 },
		{ 97, 156, 0 },
		{ 99, 94, 44 },
		{ 99, 102, 44 },
		{ 99, 0, 14 },
		{ -82, -4, 1 },
		{ 99, 0, 25 },
		{ 0, 70, 22 }
	};
	yystate = state;

	static const yybackup_t YYNEARFAR YYBASED_CODE backup[] = {
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};
	yybackup = backup;
}
#line 164 ".\\mylexer.l"


/////////////////////////////////////////////////////////////////////////////
// programs section

