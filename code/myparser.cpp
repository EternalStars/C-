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
* myparser.cpp
* C++ source file generated from myparser.y.
* 
* Date: 12/26/19
* Time: 18:51:03
* 
* AYACC Version: 2.07
****************************************************************************/

#include <yycpars.h>

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#line 1 ".\\myparser.y"

/****************************************************************************
myparser.y
ParserWizard generated YACC file.

Date: 2019年11月9日
****************************************************************************/

#include "mylexer.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
#pragma warning(disable:4996)

#define MAX 6
enum nodekind{Stmt,Expr,Decl};
enum Statement{If,While,For,Block,Input,Output,Func,Return,Expr_func,Func_asked,Empty};//stmt的种类
enum Expression{Op,Const_num,Const_char,Idk,Type};
enum Declaration{Var,FuncVar};
enum Type1{Int,Char,Void,Bool};

map<string,Type1> str_index;

struct Label{
		char* true_label;
		char* false_label;

		char* begin_label;
		char* next_label;
};//维护标号，表达式使用true和false进行控制，for、while、if使用begin和next进行控制

struct TreeNode
{
  struct TreeNode*child[MAX];
  struct TreeNode*sibling;
  int nodekind;
  int kind;
  
  Type1 type;
  union{
   int op;
   int val;
   char charval;
   char* symbol;
  }attr;
  int lineo=0;
  int temp_var;//临时变量的标号
  Label label;//各种L
};

int line=0;
TreeNode*root;

TreeNode * newStmtNode(int kind)
{
	TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
	if(t==NULL)
		printf("Out of memory error at line %d\n",line);
	else{
		for(i=0;i<MAX;i++)
			t->child[i]=NULL;
		t->sibling=NULL;
		t->nodekind=Stmt;
		t->kind=kind;
		t->lineo=line++;
		t->label.true_label="";
		t->label.false_label="";
		t->label.begin_label="";
		t->label.next_label="";
	}
	return t;
}
TreeNode * newDeclNode(int kind)
{
	TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
	if(t==NULL)
		printf("Out of memory error at line %d\n",line);
	else{
		for(i=0;i<MAX;i++)
			t->child[i]=NULL;
		t->sibling=NULL;
		t->nodekind=Decl;
		t->kind=kind;
		t->type=Void;
		t->lineo=line++;
		t->label.true_label="";
		t->label.false_label="";
		t->label.begin_label="";
		t->label.next_label="";
	}
	return t;
}
TreeNode * newExprNode(int kind)
{
	TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
	if(t==NULL)
		printf("Out of memory error at line %d\n",line);
	else{
		for(i=0;i<MAX;i++)
			t->child[i]=NULL;
		t->sibling=NULL;
		t->nodekind=Expr;
		t->kind=kind;
		t->lineo=line++;
		t->type=Void;
		t->label.true_label="";
		t->label.false_label="";
		t->label.begin_label="";
		t->label.next_label="";
	}
	return t;
}
//代码生成辅助函数
void gen_code(ostream &out);//大框架函数
void gen_header(ostream &out);//打印头部信息
void gen_decl(ostream &out, TreeNode *t);//打印声明语句
void recursive_gen_code(ostream &out, TreeNode *t);//递归代码生成函数
void expr_gen_code(ostream &out, TreeNode *t);
void stmt_gen_code(ostream &out, TreeNode *t);

//临时变量的分配
int temp_var_seq=0;//所需临时变量总数，用该值来为每一个节点的临时变量索引属性进行赋值
//临时变量的处理
void set_temp_var(TreeNode *t){
	if(t->nodekind!=Expr)
		return;
		
	//表达式节点才进行临时变量的使用
	if(t->child[0]->nodekind==Expr && t->child[0]->kind==Op)//若子节点为op表达式
		temp_var_seq--;//实现临时变量的重复使用
	if(t->child[1]!=NULL && t->child[1]->nodekind==Expr && t->child[1]->kind==Op)//这里注意单目的判空
		temp_var_seq--;
		
	t->temp_var=temp_var_seq;
	temp_var_seq++;
} 
int label_seq=0;//记录标号的总数
char* newlabel(){
	char* temp=new char[15];
	sprintf(temp,"L%d",label_seq);
	label_seq++;
	return temp;
}
//标号设置的辅助函数
void gen_label();
void recursive_gen_label(TreeNode *t);
void stmt_gen_label(TreeNode *t);
void expr_gen_label(TreeNode *t);

#line 195 "myparser.cpp"
// repeated because of possible precompiled header
#include <yycpars.h>

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#include ".\myparser.h"

/////////////////////////////////////////////////////////////////////////////
// constructor

YYPARSERNAME::YYPARSERNAME()
{
	yytables();
#line 174 ".\\myparser.y"

	// place any extra initialisation code here

#line 219 "myparser.cpp"
}

/////////////////////////////////////////////////////////////////////////////
// destructor

YYPARSERNAME::~YYPARSERNAME()
{
	// allows virtual functions to be called properly for correct cleanup
	yydestroy();
#line 179 ".\\myparser.y"

	// place any extra cleanup code here

#line 233 "myparser.cpp"
}

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYSTACK_SIZE
#define YYSTACK_SIZE 100
#endif
#ifndef YYSTACK_MAX
#define YYSTACK_MAX 0
#endif

/****************************************************************************
* N O T E
* 
* If the compiler generates a YYPARSERNAME error then you have not declared
* the name of the parser. The easiest way to do this is to use a name
* declaration. This is placed in the declarations section of your YACC
* source file and is introduced with the %name keyword. For instance, the
* following name declaration declares the parser myparser:
* 
* %name myparser
* 
* For more information see help.
****************************************************************************/

// yyattribute
#ifdef YYDEBUG
void YYFAR* YYPARSERNAME::yyattribute1(int index) const
{
	YYSTYPE YYFAR* p = &((YYSTYPE YYFAR*)yyattributestackptr)[yytop + index];
	return p;
}
#define yyattribute(index) (*(YYSTYPE YYFAR*)yyattribute1(index))
#else
#define yyattribute(index) (((YYSTYPE YYFAR*)yyattributestackptr)[yytop + (index)])
#endif

void YYPARSERNAME::yystacktoval(int index)
{
	yyassert(index >= 0);
	*(YYSTYPE YYFAR*)yyvalptr = ((YYSTYPE YYFAR*)yyattributestackptr)[index];
}

void YYPARSERNAME::yyvaltostack(int index)
{
	yyassert(index >= 0);
	((YYSTYPE YYFAR*)yyattributestackptr)[index] = *(YYSTYPE YYFAR*)yyvalptr;
}

void YYPARSERNAME::yylvaltoval()
{
	*(YYSTYPE YYFAR*)yyvalptr = *(YYSTYPE YYFAR*)yylvalptr;
}

void YYPARSERNAME::yyvaltolval()
{
	*(YYSTYPE YYFAR*)yylvalptr = *(YYSTYPE YYFAR*)yyvalptr;
}

void YYPARSERNAME::yylvaltostack(int index)
{
	yyassert(index >= 0);
	((YYSTYPE YYFAR*)yyattributestackptr)[index] = *(YYSTYPE YYFAR*)yylvalptr;
}

void YYFAR* YYPARSERNAME::yynewattribute(int count)
{
	yyassert(count >= 0);
	return new YYFAR YYSTYPE[count];
}

void YYPARSERNAME::yydeleteattribute(void YYFAR* attribute)
{
	delete[] (YYSTYPE YYFAR*)attribute;
}

void YYPARSERNAME::yycopyattribute(void YYFAR* dest, const void YYFAR* src, int count)
{
	for (int i = 0; i < count; i++) {
		((YYSTYPE YYFAR*)dest)[i] = ((YYSTYPE YYFAR*)src)[i];
	}
}

#ifdef YYDEBUG
void YYPARSERNAME::yyinitdebug(void YYFAR** p, int count) const
{
	yyassert(p != NULL);
	yyassert(count >= 1);

	YYSTYPE YYFAR** p1 = (YYSTYPE YYFAR**)p;
	for (int i = 0; i < count; i++) {
		p1[i] = &((YYSTYPE YYFAR*)yyattributestackptr)[yytop + i - (count - 1)];
	}
}
#endif

void YYPARSERNAME::yyaction(int action)
{
	switch (action) {
	case 0:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 215 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(4 - 4);root=yyattribute(4 - 4);int con=1;Display(root,&con);
#line 343 "myparser.cpp"
			}
		}
		break;
	case 1:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 217 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtNode(Block);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(2 - 3);
#line 356 "myparser.cpp"
			}
		}
		break;
	case 2:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 219 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 2);(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(2 - 2);
#line 369 "myparser.cpp"
			}
		}
		break;
	case 3:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 220 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 382 "myparser.cpp"
			}
		}
		break;
	case 4:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 222 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 395 "myparser.cpp"
			}
		}
		break;
	case 5:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 223 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 408 "myparser.cpp"
			}
		}
		break;
	case 6:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 224 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 421 "myparser.cpp"
			}
		}
		break;
	case 7:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 225 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 434 "myparser.cpp"
			}
		}
		break;
	case 8:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 226 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 447 "myparser.cpp"
			}
		}
		break;
	case 9:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 227 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 460 "myparser.cpp"
			}
		}
		break;
	case 10:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 228 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 473 "myparser.cpp"
			}
		}
		break;
	case 11:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 229 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 486 "myparser.cpp"
			}
		}
		break;
	case 12:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 230 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 499 "myparser.cpp"
			}
		}
		break;
	case 13:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 231 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 512 "myparser.cpp"
			}
		}
		break;
	case 14:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 232 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 525 "myparser.cpp"
			}
		}
		break;
	case 15:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 234 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Type);(*(YYSTYPE YYFAR*)yyvalptr)->type=Int;
#line 538 "myparser.cpp"
			}
		}
		break;
	case 16:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 235 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Type);(*(YYSTYPE YYFAR*)yyvalptr)->type=Char;
#line 551 "myparser.cpp"
			}
		}
		break;
	case 17:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 236 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Type);(*(YYSTYPE YYFAR*)yyvalptr)->type=Void;
#line 564 "myparser.cpp"
			}
		}
		break;
	case 18:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 237 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Type);(*(YYSTYPE YYFAR*)yyvalptr)->type=Bool;
#line 577 "myparser.cpp"
			}
		}
		break;
	case 19:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 239 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(3 - 3);
#line 590 "myparser.cpp"
			}
		}
		break;
	case 20:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 240 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 603 "myparser.cpp"
			}
		}
		break;
	case 21:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 242 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtNode(Input);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 4);
#line 616 "myparser.cpp"
			}
		}
		break;
	case 22:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 244 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtNode(Output);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 4);
#line 629 "myparser.cpp"
			}
		}
		break;
	case 23:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 246 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newDeclNode(Var);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 3);
										TreeNode *p=yyattribute(2 - 3);
										while(p!=NULL){
											p->type=yyattribute(1 - 3)->type;
											string str;
											for(int i=0;i<strlen(p->attr.symbol);i++)str+=p->attr.symbol[i];
											str_index[str]=yyattribute(1 - 3)->type;
											p=p->sibling;										
										}
									 
#line 651 "myparser.cpp"
			}
		}
		break;
	case 24:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 257 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->sibling=yyattribute(3 - 3);
#line 664 "myparser.cpp"
			}
		}
		break;
	case 25:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 258 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 677 "myparser.cpp"
			}
		}
		break;
	case 26:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 260 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newDeclNode(FuncVar);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 2);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 2);
#line 690 "myparser.cpp"
			}
		}
		break;
	case 27:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 262 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 2);
#line 703 "myparser.cpp"
			}
		}
		break;
	case 28:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 263 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtNode(Empty);
#line 716 "myparser.cpp"
			}
		}
		break;
	case 29:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 266 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=ASSIGN;set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 729 "myparser.cpp"
			}
		}
		break;
	case 30:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 267 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 742 "myparser.cpp"
			}
		}
		break;
	case 31:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 270 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=OR;set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 755 "myparser.cpp"
			}
		}
		break;
	case 32:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 271 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 768 "myparser.cpp"
			}
		}
		break;
	case 33:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 273 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=AND;set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 781 "myparser.cpp"
			}
		}
		break;
	case 34:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 274 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 794 "myparser.cpp"
			}
		}
		break;
	case 35:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 277 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=EQ;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 807 "myparser.cpp"
			}
		}
		break;
	case 36:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 278 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=GE;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 820 "myparser.cpp"
			}
		}
		break;
	case 37:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 279 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=LE;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 833 "myparser.cpp"
			}
		}
		break;
	case 38:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 280 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=GT;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 846 "myparser.cpp"
			}
		}
		break;
	case 39:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 281 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=LT;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 859 "myparser.cpp"
			}
		}
		break;
	case 40:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 282 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=NEQ;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 872 "myparser.cpp"
			}
		}
		break;
	case 41:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 283 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=LM;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 885 "myparser.cpp"
			}
		}
		break;
	case 42:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 284 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=RM;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 898 "myparser.cpp"
			}
		}
		break;
	case 43:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 285 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 911 "myparser.cpp"
			}
		}
		break;
	case 44:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 288 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=PLUS;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 924 "myparser.cpp"
			}
		}
		break;
	case 45:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 289 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=MINUS;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 937 "myparser.cpp"
			}
		}
		break;
	case 46:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 290 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=MUL;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 950 "myparser.cpp"
			}
		}
		break;
	case 47:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 291 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=DIV;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 963 "myparser.cpp"
			}
		}
		break;
	case 48:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 292 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=MOD;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 976 "myparser.cpp"
			}
		}
		break;
	case 49:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 293 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=DPLUS;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 2);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 989 "myparser.cpp"
			}
		}
		break;
	case 50:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 294 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=DMINUS;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 2);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 1002 "myparser.cpp"
			}
		}
		break;
	case 51:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 295 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 1015 "myparser.cpp"
			}
		}
		break;
	case 52:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 297 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(2 - 3);
#line 1028 "myparser.cpp"
			}
		}
		break;
	case 53:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 298 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 1041 "myparser.cpp"
			}
		}
		break;
	case 54:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 299 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 1054 "myparser.cpp"
			}
		}
		break;
	case 55:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 300 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 1067 "myparser.cpp"
			}
		}
		break;
	case 56:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 301 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newExprNode(Op);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=NOT;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(2 - 2);set_temp_var((*(YYSTYPE YYFAR*)yyvalptr));
#line 1080 "myparser.cpp"
			}
		}
		break;
	case 57:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 304 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtNode(If);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 5);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
#line 1093 "myparser.cpp"
			}
		}
		break;
	case 58:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 305 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtNode(If);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 7);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 7);(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(7 - 7);
#line 1106 "myparser.cpp"
			}
		}
		break;
	case 59:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[10];
			yyinitdebug((void YYFAR**)yya, 10);
#endif
			{
#line 307 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr) = newStmtNode(For);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=1;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 9);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 9);(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(7 - 9);(*(YYSTYPE YYFAR*)yyvalptr)->child[3]=yyattribute(9 - 9);
#line 1119 "myparser.cpp"
			}
		}
		break;
	case 60:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[9];
			yyinitdebug((void YYFAR**)yya, 9);
#endif
			{
#line 308 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr) = newStmtNode(For);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=0;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(4 - 8);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(6 - 8);(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(8 - 8);
#line 1132 "myparser.cpp"
			}
		}
		break;
	case 61:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[9];
			yyinitdebug((void YYFAR**)yya, 9);
#endif
			{
#line 309 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr) = newStmtNode(For);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=-1;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 8);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(6 - 8);(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(8 - 8);
#line 1145 "myparser.cpp"
			}
		}
		break;
	case 62:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[9];
			yyinitdebug((void YYFAR**)yya, 9);
#endif
			{
#line 310 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr) = newStmtNode(For);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=1;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 8);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 8);(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(8 - 8);
#line 1158 "myparser.cpp"
			}
		}
		break;
	case 63:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 311 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr) = newStmtNode(For);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=-1;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(5 - 7);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(7 - 7);
#line 1171 "myparser.cpp"
			}
		}
		break;
	case 64:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 312 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr) = newStmtNode(For);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=0;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(4 - 7);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(7 - 7);
#line 1184 "myparser.cpp"
			}
		}
		break;
	case 65:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 313 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr) = newStmtNode(For);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=-1;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 7);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(7 - 7);
#line 1197 "myparser.cpp"
			}
		}
		break;
	case 66:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 314 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr) = newStmtNode(For);(*(YYSTYPE YYFAR*)yyvalptr)->attr.op=-1;(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(6 - 6);
#line 1210 "myparser.cpp"
			}
		}
		break;
	case 67:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 316 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtNode(While);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(3 - 5);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(5 - 5);
#line 1223 "myparser.cpp"
			}
		}
		break;
	case 68:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 318 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtNode(Func);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 6);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 6);(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(4 - 6);(*(YYSTYPE YYFAR*)yyvalptr)->child[3]=yyattribute(6 - 6);
#line 1236 "myparser.cpp"
			}
		}
		break;
	case 69:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 320 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtNode(Func);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 4);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(2 - 4);(*(YYSTYPE YYFAR*)yyvalptr)->child[2]=yyattribute(4 - 4);
#line 1249 "myparser.cpp"
			}
		}
		break;
	case 70:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 321 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=yyattribute(1 - 1);
#line 1262 "myparser.cpp"
			}
		}
		break;
	case 71:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 323 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtNode(Func_asked);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 5);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 5);
#line 1275 "myparser.cpp"
			}
		}
		break;
	case 72:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 325 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtNode(Expr_func);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 3);(*(YYSTYPE YYFAR*)yyvalptr)->child[1]=yyattribute(3 - 3);
#line 1288 "myparser.cpp"
			}
		}
		break;
	case 73:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 326 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtNode(Expr_func);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(1 - 1);
#line 1301 "myparser.cpp"
			}
		}
		break;
	case 74:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 328 ".\\myparser.y"
(*(YYSTYPE YYFAR*)yyvalptr)=newStmtNode(Return);(*(YYSTYPE YYFAR*)yyvalptr)->child[0]=yyattribute(2 - 2);
#line 1314 "myparser.cpp"
			}
		}
		break;
	default:
		yyassert(0);
		break;
	}
}

void YYPARSERNAME::yytables()
{
	yyattribute_size = sizeof(YYSTYPE);
	yysstack_size = YYSTACK_SIZE;
	yystack_max = YYSTACK_MAX;

#ifdef YYDEBUG
	static const yysymbol_t YYNEARFAR YYBASED_CODE symbol[] = {
		{ "$end", 0 },
		{ "error", 256 },
		{ "IF", 257 },
		{ "MAIN", 258 },
		{ "FOR", 259 },
		{ "WHILE", 260 },
		{ "CIN", 261 },
		{ "COUT", 262 },
		{ "INT", 263 },
		{ "CHAR", 264 },
		{ "VOID", 265 },
		{ "BOOL", 266 },
		{ "ID", 268 },
		{ "NUMBER", 269 },
		{ "Constchar", 270 },
		{ "PLUS", 271 },
		{ "MINUS", 272 },
		{ "MUL", 273 },
		{ "DIV", 274 },
		{ "MOD", 275 },
		{ "DPLUS", 276 },
		{ "DMINUS", 277 },
		{ "GT", 278 },
		{ "LT", 279 },
		{ "GE", 280 },
		{ "LE", 281 },
		{ "NEQ", 282 },
		{ "AND", 283 },
		{ "OR", 284 },
		{ "NOT", 285 },
		{ "ASSIGN", 286 },
		{ "LFP", 287 },
		{ "RFP", 288 },
		{ "COMMA", 291 },
		{ "SEMI", 292 },
		{ "LP", 293 },
		{ "RP", 294 },
		{ "LM", 295 },
		{ "RM", 296 },
		{ "RETURN", 297 },
		{ "EQ", 298 },
		{ "ELSE", 299 },
		{ NULL, 0 }
	};
	yysymbol = symbol;

	static const char* const YYNEARFAR YYBASED_CODE rule[] = {
		"$accept: start",
		"start: MAIN LP RP block",
		"block: LFP stmts RFP",
		"stmts: stmt stmts",
		"stmts: stmt",
		"stmt: expr_stmt",
		"stmt: var_stmt",
		"stmt: if_stmt",
		"stmt: while_stmt",
		"stmt: for_stmt",
		"stmt: block",
		"stmt: input_stmt",
		"stmt: output_stmt",
		"stmt: func_stmt",
		"stmt: func_asked_stmt",
		"stmt: return_stmt",
		"type_var: INT",
		"type_var: CHAR",
		"type_var: VOID",
		"type_var: BOOL",
		"id_list: expr COMMA id_list",
		"id_list: expr",
		"input_stmt: CIN RM ID SEMI",
		"output_stmt: COUT LM term SEMI",
		"var_stmt: type_var id_list SEMI",
		"func_var: func_var1 COMMA func_var",
		"func_var: func_var1",
		"func_var1: type_var ID",
		"expr_stmt: expr SEMI",
		"expr_stmt: SEMI",
		"expr: ID ASSIGN expr",
		"expr: or_expr",
		"or_expr: or_expr OR and_expr",
		"or_expr: and_expr",
		"and_expr: and_expr AND eq_expr",
		"and_expr: eq_expr",
		"eq_expr: eq_expr EQ simple_expr",
		"eq_expr: eq_expr GE simple_expr",
		"eq_expr: eq_expr LE simple_expr",
		"eq_expr: eq_expr GT simple_expr",
		"eq_expr: eq_expr LT simple_expr",
		"eq_expr: eq_expr NEQ simple_expr",
		"eq_expr: eq_expr LM simple_expr",
		"eq_expr: eq_expr RM simple_expr",
		"eq_expr: simple_expr",
		"simple_expr: simple_expr PLUS simple_expr",
		"simple_expr: simple_expr MINUS simple_expr",
		"simple_expr: simple_expr MUL simple_expr",
		"simple_expr: simple_expr DIV simple_expr",
		"simple_expr: simple_expr MOD simple_expr",
		"simple_expr: simple_expr DPLUS",
		"simple_expr: simple_expr DMINUS",
		"simple_expr: term",
		"term: LP expr RP",
		"term: ID",
		"term: NUMBER",
		"term: Constchar",
		"term: NOT term",
		"if_stmt: IF LP expr RP stmt",
		"if_stmt: IF LP expr RP stmt ELSE stmt",
		"for_stmt: FOR LP expr SEMI expr SEMI expr RP stmt",
		"for_stmt: FOR LP SEMI expr SEMI expr RP stmt",
		"for_stmt: FOR LP expr SEMI SEMI expr RP stmt",
		"for_stmt: FOR LP expr SEMI expr SEMI RP stmt",
		"for_stmt: FOR LP SEMI SEMI expr RP stmt",
		"for_stmt: FOR LP SEMI expr SEMI RP stmt",
		"for_stmt: FOR LP expr SEMI SEMI RP stmt",
		"for_stmt: FOR LP SEMI SEMI RP stmt",
		"while_stmt: WHILE LP expr RP stmt",
		"func_stmt: type_var ID LP func_var RP block",
		"func_asked_stmt: type_var ID ASSIGN func_asked_stmt1",
		"func_asked_stmt: func_asked_stmt1",
		"func_asked_stmt1: ID LP expr RP SEMI",
		"expr_func: expr COMMA expr_func",
		"expr_func: expr",
		"return_stmt: RETURN term"
	};
	yyrule = rule;
#endif

	static const yyreduction_t YYNEARFAR YYBASED_CODE reduction[] = {
		{ 0, 1, -1 },
		{ 1, 4, 0 },
		{ 2, 3, 1 },
		{ 3, 2, 2 },
		{ 3, 1, 3 },
		{ 4, 1, 4 },
		{ 4, 1, 5 },
		{ 4, 1, 6 },
		{ 4, 1, 7 },
		{ 4, 1, 8 },
		{ 4, 1, 9 },
		{ 4, 1, 10 },
		{ 4, 1, 11 },
		{ 4, 1, 12 },
		{ 4, 1, 13 },
		{ 4, 1, 14 },
		{ 5, 1, 15 },
		{ 5, 1, 16 },
		{ 5, 1, 17 },
		{ 5, 1, 18 },
		{ 6, 3, 19 },
		{ 6, 1, 20 },
		{ 7, 4, 21 },
		{ 8, 4, 22 },
		{ 9, 3, 23 },
		{ 10, 3, 24 },
		{ 10, 1, 25 },
		{ 11, 2, 26 },
		{ 12, 2, 27 },
		{ 12, 1, 28 },
		{ 13, 3, 29 },
		{ 13, 1, 30 },
		{ 14, 3, 31 },
		{ 14, 1, 32 },
		{ 15, 3, 33 },
		{ 15, 1, 34 },
		{ 16, 3, 35 },
		{ 16, 3, 36 },
		{ 16, 3, 37 },
		{ 16, 3, 38 },
		{ 16, 3, 39 },
		{ 16, 3, 40 },
		{ 16, 3, 41 },
		{ 16, 3, 42 },
		{ 16, 1, 43 },
		{ 17, 3, 44 },
		{ 17, 3, 45 },
		{ 17, 3, 46 },
		{ 17, 3, 47 },
		{ 17, 3, 48 },
		{ 17, 2, 49 },
		{ 17, 2, 50 },
		{ 17, 1, 51 },
		{ 18, 3, 52 },
		{ 18, 1, 53 },
		{ 18, 1, 54 },
		{ 18, 1, 55 },
		{ 18, 2, 56 },
		{ 19, 5, 57 },
		{ 19, 7, 58 },
		{ 20, 9, 59 },
		{ 20, 8, 60 },
		{ 20, 8, 61 },
		{ 20, 8, 62 },
		{ 20, 7, 63 },
		{ 20, 7, 64 },
		{ 20, 7, 65 },
		{ 20, 6, 66 },
		{ 21, 5, 67 },
		{ 22, 6, 68 },
		{ 23, 4, 69 },
		{ 23, 1, 70 },
		{ 24, 5, 71 },
		{ 25, 3, 72 },
		{ 25, 1, 73 },
		{ 26, 2, 74 }
	};
	yyreduction = reduction;

	yytokenaction_size = 185;

	static const yytokenaction_t YYNEARFAR YYBASED_CODE tokenaction[] = {
		{ 23, YYAT_SHIFT, 7 },
		{ 148, YYAT_SHIFT, 152 },
		{ 23, YYAT_SHIFT, 8 },
		{ 23, YYAT_SHIFT, 9 },
		{ 23, YYAT_SHIFT, 10 },
		{ 23, YYAT_SHIFT, 11 },
		{ 23, YYAT_SHIFT, 12 },
		{ 23, YYAT_SHIFT, 13 },
		{ 23, YYAT_SHIFT, 14 },
		{ 23, YYAT_SHIFT, 15 },
		{ 137, YYAT_SHIFT, 146 },
		{ 23, YYAT_SHIFT, 16 },
		{ 23, YYAT_SHIFT, 17 },
		{ 23, YYAT_SHIFT, 18 },
		{ 152, YYAT_SHIFT, 7 },
		{ 135, YYAT_SHIFT, 144 },
		{ 152, YYAT_SHIFT, 8 },
		{ 152, YYAT_SHIFT, 9 },
		{ 152, YYAT_SHIFT, 10 },
		{ 152, YYAT_SHIFT, 11 },
		{ 152, YYAT_SHIFT, 12 },
		{ 152, YYAT_SHIFT, 13 },
		{ 152, YYAT_SHIFT, 14 },
		{ 152, YYAT_SHIFT, 15 },
		{ 128, YYAT_SHIFT, 5 },
		{ 138, YYAT_SHIFT, 53 },
		{ 138, YYAT_SHIFT, 17 },
		{ 138, YYAT_SHIFT, 18 },
		{ 23, YYAT_SHIFT, 19 },
		{ 125, YYAT_SHIFT, 138 },
		{ 23, YYAT_SHIFT, 5 },
		{ 130, YYAT_SHIFT, 12 },
		{ 130, YYAT_SHIFT, 13 },
		{ 130, YYAT_SHIFT, 14 },
		{ 130, YYAT_SHIFT, 15 },
		{ 23, YYAT_SHIFT, 20 },
		{ 23, YYAT_SHIFT, 21 },
		{ 124, YYAT_SHIFT, 136 },
		{ 75, YYAT_SHIFT, 103 },
		{ 16, YYAT_SHIFT, 49 },
		{ 23, YYAT_SHIFT, 22 },
		{ 123, YYAT_SHIFT, 134 },
		{ 138, YYAT_SHIFT, 19 },
		{ 122, YYAT_SHIFT, 133 },
		{ 152, YYAT_SHIFT, 5 },
		{ 75, YYAT_SHIFT, 104 },
		{ 16, YYAT_SHIFT, 50 },
		{ 102, YYAT_SHIFT, 73 },
		{ 102, YYAT_SHIFT, 74 },
		{ 152, YYAT_SHIFT, 20 },
		{ 138, YYAT_SHIFT, 21 },
		{ 138, YYAT_SHIFT, 147 },
		{ 101, YYAT_SHIFT, 73 },
		{ 101, YYAT_SHIFT, 74 },
		{ 152, YYAT_SHIFT, 22 },
		{ 88, YYAT_SHIFT, 60 },
		{ 88, YYAT_SHIFT, 61 },
		{ 88, YYAT_SHIFT, 62 },
		{ 88, YYAT_SHIFT, 63 },
		{ 88, YYAT_SHIFT, 64 },
		{ 38, YYAT_SHIFT, 60 },
		{ 38, YYAT_SHIFT, 61 },
		{ 38, YYAT_SHIFT, 62 },
		{ 38, YYAT_SHIFT, 63 },
		{ 38, YYAT_SHIFT, 64 },
		{ 97, YYAT_SHIFT, 68 },
		{ 97, YYAT_SHIFT, 69 },
		{ 97, YYAT_SHIFT, 70 },
		{ 97, YYAT_SHIFT, 71 },
		{ 97, YYAT_SHIFT, 72 },
		{ 97, YYAT_SHIFT, 73 },
		{ 97, YYAT_SHIFT, 74 },
		{ 88, YYAT_SHIFT, 65 },
		{ 88, YYAT_SHIFT, 66 },
		{ 120, YYAT_SHIFT, 131 },
		{ 88, YYAT_SHIFT, 67 },
		{ 118, YYAT_SHIFT, 130 },
		{ 38, YYAT_SHIFT, 65 },
		{ 38, YYAT_SHIFT, 66 },
		{ 117, YYAT_SHIFT, 129 },
		{ 38, YYAT_SHIFT, 67 },
		{ 96, YYAT_SHIFT, 68 },
		{ 96, YYAT_SHIFT, 69 },
		{ 96, YYAT_SHIFT, 70 },
		{ 96, YYAT_SHIFT, 71 },
		{ 96, YYAT_SHIFT, 72 },
		{ 96, YYAT_SHIFT, 73 },
		{ 96, YYAT_SHIFT, 74 },
		{ 95, YYAT_SHIFT, 68 },
		{ 95, YYAT_SHIFT, 69 },
		{ 95, YYAT_SHIFT, 70 },
		{ 95, YYAT_SHIFT, 71 },
		{ 95, YYAT_SHIFT, 72 },
		{ 95, YYAT_SHIFT, 73 },
		{ 95, YYAT_SHIFT, 74 },
		{ 94, YYAT_SHIFT, 68 },
		{ 94, YYAT_SHIFT, 69 },
		{ 94, YYAT_SHIFT, 70 },
		{ 94, YYAT_SHIFT, 71 },
		{ 94, YYAT_SHIFT, 72 },
		{ 94, YYAT_SHIFT, 73 },
		{ 94, YYAT_SHIFT, 74 },
		{ 93, YYAT_SHIFT, 68 },
		{ 93, YYAT_SHIFT, 69 },
		{ 93, YYAT_SHIFT, 70 },
		{ 93, YYAT_SHIFT, 71 },
		{ 93, YYAT_SHIFT, 72 },
		{ 93, YYAT_SHIFT, 73 },
		{ 93, YYAT_SHIFT, 74 },
		{ 92, YYAT_SHIFT, 68 },
		{ 92, YYAT_SHIFT, 69 },
		{ 92, YYAT_SHIFT, 70 },
		{ 92, YYAT_SHIFT, 71 },
		{ 92, YYAT_SHIFT, 72 },
		{ 92, YYAT_SHIFT, 73 },
		{ 92, YYAT_SHIFT, 74 },
		{ 91, YYAT_SHIFT, 68 },
		{ 91, YYAT_SHIFT, 69 },
		{ 91, YYAT_SHIFT, 70 },
		{ 91, YYAT_SHIFT, 71 },
		{ 91, YYAT_SHIFT, 72 },
		{ 91, YYAT_SHIFT, 73 },
		{ 91, YYAT_SHIFT, 74 },
		{ 90, YYAT_SHIFT, 68 },
		{ 90, YYAT_SHIFT, 69 },
		{ 90, YYAT_SHIFT, 70 },
		{ 90, YYAT_SHIFT, 71 },
		{ 90, YYAT_SHIFT, 72 },
		{ 90, YYAT_SHIFT, 73 },
		{ 90, YYAT_SHIFT, 74 },
		{ 39, YYAT_SHIFT, 68 },
		{ 39, YYAT_SHIFT, 69 },
		{ 39, YYAT_SHIFT, 70 },
		{ 39, YYAT_SHIFT, 71 },
		{ 39, YYAT_SHIFT, 72 },
		{ 39, YYAT_SHIFT, 73 },
		{ 39, YYAT_SHIFT, 74 },
		{ 99, YYAT_SHIFT, 70 },
		{ 99, YYAT_SHIFT, 71 },
		{ 99, YYAT_SHIFT, 72 },
		{ 99, YYAT_SHIFT, 73 },
		{ 99, YYAT_SHIFT, 74 },
		{ 98, YYAT_SHIFT, 70 },
		{ 98, YYAT_SHIFT, 71 },
		{ 98, YYAT_SHIFT, 72 },
		{ 98, YYAT_SHIFT, 73 },
		{ 98, YYAT_SHIFT, 74 },
		{ 100, YYAT_SHIFT, 73 },
		{ 100, YYAT_SHIFT, 74 },
		{ 116, YYAT_SHIFT, 128 },
		{ 114, YYAT_SHIFT, 127 },
		{ 110, YYAT_SHIFT, 124 },
		{ 109, YYAT_SHIFT, 123 },
		{ 108, YYAT_SHIFT, 121 },
		{ 106, YYAT_ERROR, 0 },
		{ 103, YYAT_SHIFT, 16 },
		{ 89, YYAT_SHIFT, 58 },
		{ 86, YYAT_SHIFT, 114 },
		{ 84, YYAT_SHIFT, 113 },
		{ 83, YYAT_SHIFT, 112 },
		{ 82, YYAT_SHIFT, 111 },
		{ 81, YYAT_SHIFT, 110 },
		{ 80, YYAT_SHIFT, 108 },
		{ 79, YYAT_SHIFT, 107 },
		{ 77, YYAT_SHIFT, 106 },
		{ 76, YYAT_SHIFT, 105 },
		{ 72, YYAT_SHIFT, 51 },
		{ 54, YYAT_SHIFT, 87 },
		{ 53, YYAT_SHIFT, 49 },
		{ 47, YYAT_SHIFT, 83 },
		{ 45, YYAT_SHIFT, 80 },
		{ 43, YYAT_SHIFT, 78 },
		{ 40, YYAT_SHIFT, 75 },
		{ 37, YYAT_SHIFT, 59 },
		{ 36, YYAT_SHIFT, 58 },
		{ 34, YYAT_SHIFT, 57 },
		{ 11, YYAT_SHIFT, 48 },
		{ 10, YYAT_SHIFT, 47 },
		{ 9, YYAT_SHIFT, 46 },
		{ 8, YYAT_SHIFT, 45 },
		{ 7, YYAT_SHIFT, 44 },
		{ 3, YYAT_SHIFT, 4 },
		{ 2, YYAT_ACCEPT, 0 },
		{ 1, YYAT_SHIFT, 3 },
		{ 0, YYAT_SHIFT, 1 }
	};
	yytokenaction = tokenaction;

	static const yystateaction_t YYNEARFAR YYBASED_CODE stateaction[] = {
		{ -74, 1, YYAT_ERROR, 0 },
		{ -110, 1, YYAT_ERROR, 0 },
		{ 182, 1, YYAT_ERROR, 0 },
		{ -113, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 128 },
		{ 0, 0, YYAT_DEFAULT, 152 },
		{ 0, 0, YYAT_REDUCE, 1 },
		{ -113, 1, YYAT_ERROR, 0 },
		{ -114, 1, YYAT_ERROR, 0 },
		{ -115, 1, YYAT_ERROR, 0 },
		{ -119, 1, YYAT_ERROR, 0 },
		{ -119, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 16 },
		{ 0, 0, YYAT_REDUCE, 17 },
		{ 0, 0, YYAT_REDUCE, 18 },
		{ 0, 0, YYAT_REDUCE, 19 },
		{ -247, 1, YYAT_REDUCE, 54 },
		{ 0, 0, YYAT_REDUCE, 55 },
		{ 0, 0, YYAT_REDUCE, 56 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_REDUCE, 29 },
		{ 0, 0, YYAT_DEFAULT, 106 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ -257, 1, YYAT_REDUCE, 4 },
		{ 0, 0, YYAT_REDUCE, 8 },
		{ 0, 0, YYAT_REDUCE, 12 },
		{ 0, 0, YYAT_REDUCE, 5 },
		{ 0, 0, YYAT_REDUCE, 7 },
		{ 0, 0, YYAT_REDUCE, 11 },
		{ 0, 0, YYAT_REDUCE, 13 },
		{ 0, 0, YYAT_REDUCE, 14 },
		{ 0, 0, YYAT_REDUCE, 15 },
		{ 0, 0, YYAT_REDUCE, 10 },
		{ 0, 0, YYAT_REDUCE, 9 },
		{ -113, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 6 },
		{ -109, 1, YYAT_REDUCE, 33 },
		{ -111, 1, YYAT_REDUCE, 31 },
		{ -218, 1, YYAT_REDUCE, 35 },
		{ -141, 1, YYAT_REDUCE, 44 },
		{ -96, 1, YYAT_DEFAULT, 106 },
		{ 0, 0, YYAT_REDUCE, 52 },
		{ 0, 0, YYAT_REDUCE, 71 },
		{ -121, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 106 },
		{ -122, 1, YYAT_DEFAULT, 110 },
		{ 0, 0, YYAT_DEFAULT, 106 },
		{ -99, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 106 },
		{ 0, 0, YYAT_DEFAULT, 106 },
		{ 0, 0, YYAT_REDUCE, 54 },
		{ 0, 0, YYAT_REDUCE, 57 },
		{ -118, 1, YYAT_REDUCE, 54 },
		{ -127, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 75 },
		{ 0, 0, YYAT_REDUCE, 3 },
		{ 0, 0, YYAT_REDUCE, 2 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ -102, 1, YYAT_DEFAULT, 106 },
		{ 0, 0, YYAT_REDUCE, 50 },
		{ 0, 0, YYAT_REDUCE, 51 },
		{ -248, 1, YYAT_REDUCE, 54 },
		{ -127, 1, YYAT_ERROR, 0 },
		{ -127, 1, YYAT_REDUCE, 21 },
		{ 0, 0, YYAT_REDUCE, 28 },
		{ -131, 1, YYAT_ERROR, 0 },
		{ -130, 1, YYAT_DEFAULT, 110 },
		{ -131, 1, YYAT_ERROR, 0 },
		{ -134, 1, YYAT_ERROR, 0 },
		{ -133, 1, YYAT_ERROR, 0 },
		{ -134, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 30 },
		{ -137, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 53 },
		{ -223, 1, YYAT_REDUCE, 34 },
		{ -127, 1, YYAT_REDUCE, 32 },
		{ -148, 1, YYAT_REDUCE, 39 },
		{ -155, 1, YYAT_REDUCE, 40 },
		{ -162, 1, YYAT_REDUCE, 37 },
		{ -169, 1, YYAT_REDUCE, 38 },
		{ -176, 1, YYAT_REDUCE, 41 },
		{ -183, 1, YYAT_REDUCE, 42 },
		{ -190, 1, YYAT_REDUCE, 43 },
		{ -206, 1, YYAT_REDUCE, 36 },
		{ -131, 1, YYAT_REDUCE, 45 },
		{ -136, 1, YYAT_REDUCE, 46 },
		{ -129, 1, YYAT_REDUCE, 47 },
		{ -224, 1, YYAT_REDUCE, 48 },
		{ -229, 1, YYAT_REDUCE, 49 },
		{ -113, 1, YYAT_DEFAULT, 106 },
		{ 0, 0, YYAT_DEFAULT, 130 },
		{ 0, 0, YYAT_REDUCE, 24 },
		{ -140, 1, YYAT_DEFAULT, 138 },
		{ 0, 0, YYAT_DEFAULT, 152 },
		{ -141, 1, YYAT_DEFAULT, 138 },
		{ -140, 1, YYAT_ERROR, 0 },
		{ -141, 1, YYAT_DEFAULT, 106 },
		{ 0, 0, YYAT_DEFAULT, 152 },
		{ 0, 0, YYAT_REDUCE, 22 },
		{ 0, 0, YYAT_REDUCE, 23 },
		{ -142, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 70 },
		{ -145, 1, YYAT_ERROR, 0 },
		{ -189, 1, YYAT_ERROR, 0 },
		{ -215, 1, YYAT_REDUCE, 26 },
		{ 0, 0, YYAT_REDUCE, 20 },
		{ -225, 1, YYAT_REDUCE, 58 },
		{ 0, 0, YYAT_DEFAULT, 152 },
		{ -251, 1, YYAT_ERROR, 0 },
		{ -253, 1, YYAT_DEFAULT, 138 },
		{ -257, 1, YYAT_DEFAULT, 138 },
		{ -263, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 68 },
		{ 0, 0, YYAT_REDUCE, 72 },
		{ -263, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 27 },
		{ -232, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 152 },
		{ 0, 0, YYAT_REDUCE, 67 },
		{ 0, 0, YYAT_DEFAULT, 152 },
		{ 0, 0, YYAT_DEFAULT, 152 },
		{ -279, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 152 },
		{ -284, 1, YYAT_ERROR, 0 },
		{ -243, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 69 },
		{ 0, 0, YYAT_REDUCE, 25 },
		{ 0, 0, YYAT_REDUCE, 59 },
		{ 0, 0, YYAT_REDUCE, 64 },
		{ 0, 0, YYAT_REDUCE, 65 },
		{ 0, 0, YYAT_DEFAULT, 152 },
		{ 0, 0, YYAT_REDUCE, 66 },
		{ 0, 0, YYAT_DEFAULT, 152 },
		{ 0, 0, YYAT_DEFAULT, 152 },
		{ -293, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 61 },
		{ 0, 0, YYAT_REDUCE, 62 },
		{ 0, 0, YYAT_REDUCE, 63 },
		{ -243, 1, YYAT_DEFAULT, 103 },
		{ 0, 0, YYAT_REDUCE, 60 }
	};
	yystateaction = stateaction;

	yynontermgoto_size = 74;

	static const yynontermgoto_t YYNEARFAR YYBASED_CODE nontermgoto[] = {
		{ 152, 32 },
		{ 147, 151 },
		{ 152, 153 },
		{ 152, 40 },
		{ 146, 150 },
		{ 152, 28 },
		{ 152, 25 },
		{ 152, 35 },
		{ 130, 117 },
		{ 106, 119 },
		{ 152, 26 },
		{ 152, 43 },
		{ 144, 149 },
		{ 130, 140 },
		{ 130, 118 },
		{ 136, 145 },
		{ 106, 77 },
		{ 152, 27 },
		{ 152, 33 },
		{ 152, 24 },
		{ 152, 29 },
		{ 152, 30 },
		{ 152, 42 },
		{ 134, 143 },
		{ 152, 31 },
		{ 138, 148 },
		{ 138, 37 },
		{ 138, 36 },
		{ 72, 102 },
		{ 72, 41 },
		{ 59, 89 },
		{ 59, 38 },
		{ 58, 88 },
		{ 58, 39 },
		{ 23, 56 },
		{ 23, 23 },
		{ 133, 142 },
		{ 131, 141 },
		{ 128, 139 },
		{ 124, 137 },
		{ 123, 135 },
		{ 121, 132 },
		{ 111, 126 },
		{ 110, 125 },
		{ 108, 122 },
		{ 107, 120 },
		{ 104, 116 },
		{ 103, 115 },
		{ 80, 109 },
		{ 71, 101 },
		{ 70, 100 },
		{ 69, 99 },
		{ 68, 98 },
		{ 67, 97 },
		{ 66, 96 },
		{ 65, 95 },
		{ 64, 94 },
		{ 63, 93 },
		{ 62, 92 },
		{ 61, 91 },
		{ 60, 90 },
		{ 50, 86 },
		{ 49, 85 },
		{ 48, 84 },
		{ 46, 82 },
		{ 45, 81 },
		{ 44, 79 },
		{ 40, 76 },
		{ 22, 55 },
		{ 21, 54 },
		{ 19, 52 },
		{ 5, 34 },
		{ 4, 6 },
		{ 0, 2 }
	};
	yynontermgoto = nontermgoto;

	static const yystategoto_t YYNEARFAR YYBASED_CODE stategoto[] = {
		{ 72, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 70, -1 },
		{ 68, 23 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 52, -1 },
		{ 0, -1 },
		{ 56, 138 },
		{ 50, -1 },
		{ 31, 152 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 61, 106 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 53, 138 },
		{ 52, 138 },
		{ 51, 138 },
		{ 0, -1 },
		{ 45, -1 },
		{ 49, 138 },
		{ 48, 138 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 16, 72 },
		{ 15, 58 },
		{ 43, 72 },
		{ 42, 72 },
		{ 41, 72 },
		{ 40, 72 },
		{ 39, 72 },
		{ 38, 72 },
		{ 37, 72 },
		{ 36, 72 },
		{ 35, 72 },
		{ 34, 72 },
		{ 33, 72 },
		{ 32, 72 },
		{ 11, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 35, 138 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 23, 49 },
		{ 36, 130 },
		{ 0, -1 },
		{ 3, 138 },
		{ 41, 152 },
		{ 31, 138 },
		{ 0, -1 },
		{ 30, 138 },
		{ 38, 152 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 37, 152 },
		{ 0, -1 },
		{ 27, 138 },
		{ 26, 138 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 36, -1 },
		{ 0, -1 },
		{ 3, -1 },
		{ 33, 152 },
		{ 0, -1 },
		{ 32, 152 },
		{ 19, 152 },
		{ 0, -1 },
		{ 11, 152 },
		{ 0, -1 },
		{ 12, 59 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 8, 152 },
		{ 0, -1 },
		{ 0, 152 },
		{ -3, 152 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ -2, 138 },
		{ 0, -1 }
	};
	yystategoto = stategoto;

	yydestructorptr = NULL;

	yytokendestptr = NULL;
	yytokendest_size = 0;

	yytokendestbaseptr = NULL;
	yytokendestbase_size = 0;
}
#line 331 ".\\myparser.y"


/////////////////////////////////////////////////////////////////////////////
// programs section
void myparser::ShowNode(struct TreeNode *p)
{
	struct TreeNode *temp;
	cout<<std::left<<setw(3)<<p->lineo<<":";
	switch(p->nodekind)
	{
		case Stmt:
		{
			string names[11]={"If_statement,",  "While_statement," , "For_statement," , "Compound_statement,","Input_statement,","Output_statement,","Function_statement","Return_statement","Expression_fuction" ,"Function_asked","Empty_statement,"};
			cout<<std::left<<setw(30)<<names[p->kind]<<"\t";
			p->type=Void;
			break;
		}
		case Expr:
		{
			string names[5]={"Expr," , "Const Number,", "Const Char,","ID Declaration,","Type Specifier," };
			cout<<std::left<<setw(30)<<names[p->kind]<<"\t";
			string types[4]={"integer, ","Char\t","Void","Bool"};
			switch(p->kind)
			{
				case Op:
				{
					switch(p->attr.op)
					{
						case PLUS:
						{
							cout<<"op:+"<<'\t';
							break;
						}
						case MINUS:
						{
							cout<<"op:-"<<'\t';
							break;
						}
						case MUL:
						{
							cout<<"op:*"<<'\t';
							break;
						}
						case DIV:
						{
							cout<<"op:/"<<'\t';
							break;
						}
						case MOD:
						{
							cout<<"op:%"<<'\t';
							break;
						}
						case DPLUS:
						{
							cout<<"op:++"<<'\t';
							break;
						}
						case DMINUS:
						{
							cout<<"op:--"<<'\t';
							break;
						}
						case LT:
						{
							cout<<"op:<"<<'\t';
							break;
						}
						case GT:
						{
							cout<<"op:>"<<'\t';
							break;
						}
						case LE:
						{
							cout<<"op:<="<<'\t';
							break;
						}
						case GE:
						{
							cout<<"op:>="<<'\t';
							break;
						}
						case EQ:
						{
							cout<<"op:=="<<'\t';
							break;
						}
						case ASSIGN:
						{
							cout<<"op:="<<'\t';
							break;
						}
						case NEQ:
						{
							cout<<"op:!="<<'\t';
							break;
						}
						case LM:
						{
							cout<<"op:<<"<<'\t';
							break;
						}
						case RM:
						{
							cout<<"op:>>"<<'\t';
							break;
						}
						case NOT:
						{
							cout<<"op:!"<<'\t';
							break;
						}
						case OR:
						{
							cout<<"op:||"<<'\t';
							break;
						}
						case AND:
						{
							cout<<"op:&&"<<'\t';
							break;
						}
					}
					cout<<'\t';
					break;
				}
				case Const_num:
				{
					cout<<"value:"<<p->attr.val<<"\t";
					break;
				}
				case Const_char:
				{
					cout<<"value:"<<p->attr.charval<<"\t";
					break;
				}
				case Idk:
				{
					cout<<"symbol:"<<p->attr.symbol<<'\t';
					break;	
				}
				case Type:
				{
					cout<<types[p->type]<<'\t';
					break;
				}
			}
			break;
		}
		case Decl:
		{
			string names[2]={"Var Declaration, ", "Func Declaration"};
			cout<<std::left<<setw(30)<<names[p->kind]<<"\t\t";
			break;
		}
	}
	cout<<"children:";
	for(int i=0;i<MAX;i++)
	{
		if(p->child[i]!=NULL)
		{
			cout<<p->child[i]->lineo<<" ";
			temp=p->child[i]->sibling;
			while(temp!=NULL)
			{
				cout<<temp->lineo<<" ";
				temp=temp->sibling; 
			}
		}
	}
	cout<<endl;
	return;
}
int myparser::Check(struct TreeNode *p)
{
	switch(p->nodekind)
	{
		case Stmt:
		{
			switch(p->kind){
				case If:{
					if(p->child[0]->type!=Bool){
						cout<<"If Error"<<endl;
						return 0;
					}
					else p->type=Void;
					break;
				}
				case While:{
					if(p->child[0]->type!=Bool){
						cout<<"While Error"<<endl;
						return 0;
					}
					else p->type=Void;
					break;
				}
				case For:{
					if(p->attr.op>=0){
					if(p->child[p->attr.op]->type!=Bool){
						cout<<"For Error"<<endl;
						return 0;
					}
					else p->type=Void;
					}
					else p->type=Void;
					break;
				}
				case Func_asked:{
					if(p->child[1]->type==Bool){
						cout<<"Func_asked Error"<<endl;
						return 0;
					}
					else p->type=Void;
					break;
				}
									
			}
			break;
		}
		case Expr:
		{
			switch(p->kind)
			{
				case Op:
				{
					switch(p->attr.op)
					{
						case PLUS:
						{
							if(p->child[0]->type!=p->child[1]->type){
								cout<<"+ Error"<<endl;
								return 0;
								}
							else p->type=p->child[0]->type;
							break;
						}
						case MINUS:
						{
							if(p->child[0]->type!=p->child[1]->type)
								return 0;
							else p->type=p->child[0]->type;
							break;
						}
						case MUL:
						{
							if(p->child[0]->type!=p->child[1]->type)
								return 0;
							else p->type=p->child[0]->type;
							break;;
						}
						case DIV:
						{
							if(p->child[0]->type!=p->child[1]->type)
								return 0;
							else p->type=p->child[0]->type;
							break;
						}
						case MOD:
						{
							if(p->child[0]->type!=Int||p->child[1]->type!=Int)
								return 0;
							else
								p->type=p->child[0]->type;
							break;
						}
						case DPLUS:
						{
							if(p->child[0]->type!=Int)
								return 0;
							else
								p->type=p->child[0]->type;
							break;
						}
						case DMINUS:
						{
							if(p->child[0]->type!=Int)
								return 0;
							else
								p->type=p->child[0]->type;
							break;
						}
						case LT:
						{
							if(p->child[0]->type!=Int||p->child[1]->type!=Int)
								return 0;
							else
								p->type=Bool;
							break;
						}
						case GT:
						{
							if(p->child[0]->type!=Int||p->child[1]->type!=Int)
								return 0;
							else
								p->type=Bool;
							break;
						}
						case LE:
						{
							if(p->child[0]->type!=Int||p->child[1]->type!=Int){
								cout<<"<= Error"<<endl;
								return 0;}
								
							else
								p->type=Bool;
							break;
						}
						case GE:
						{
							if(p->child[0]->type!=Int||p->child[1]->type!=Int)
								return 0;
							else
								p->type=Bool;
							break;
						}
						case EQ:
						{
							if(p->child[0]->type!=p->child[1]->type)
								return 0;
							else p->type=Bool;
							break;
						}
						case ASSIGN:
						{
							if(p->child[0]->type!=p->child[1]->type){
								cout<<"= Error"<<endl;
								return 0;
							}
							else p->type=p->child[0]->type;
							break;
						}
						case NEQ:
						{
							if(p->child[0]->type!=p->child[1]->type)
								return 0;
							else p->type=Bool;
							break;
						}
						case LM:
						{
							if(p->child[0]->type!=p->child[1]->type)
								return 0;
							else p->type=p->child[0]->type;
							break;
						}
						case RM:
						{
							if(p->child[0]->type!=p->child[1]->type)
								return 0;
							else p->type=p->child[0]->type;
							break;
						}
						case NOT:
						{
							if(p->child[0]->type!=Bool){
								cout<<"NOT Error"<<endl;
								return 0;}
							else
								p->type=p->child[0]->type;
							break;
						}
						case OR:
						{
							if(p->child[0]->type==Bool&&p->child[1]->type==Bool)
								p->type=Bool;
							else{
								cout<<"OR Error"<<endl;
								return 0;
								}
							break;
						}
						case AND:
						{
							if(p->child[0]->type==Bool&&p->child[1]->type==Bool)
								p->type=Bool;
							else
								return 0;
							break;
						}
					}
					break;
				}
				case Const_num:
				{
					p->type=Int;
					break;
				}
				case Const_char:
				{
					p->type=Char;
					break;
				}
				case Idk:
				{
					if(p->type!=Int&&p->type!=Char&&p->type!=Bool){
						
						string str;
						for(int i=0;i<strlen(p->attr.symbol);i++)str+=p->attr.symbol[i];
						if(str=="output"){
							return 1;
						}
						cout<<p->attr.symbol<<"	";
						cout<<"404 NOT FOUND"<<endl;
						
						return 0;
					}
				}
				

			}
		}
	}
	return 1;
}


void myparser::Display(struct TreeNode *p,int *con)
{
	for(int i=0;i<MAX;i++)
		if(p->child[i]!=NULL&&*con==1)
			Display(p->child[i],con);
	if(*con==1){
		ShowNode(p);
		
		*con=Check(p);
		cout<<p->type<<endl;
	}
	if((p->sibling)!=NULL&&*con==1)
		Display(p->sibling,con);
	return;
}

void gen_code(ostream &out)
{
  int i=0;
  gen_header(out);//程序头部的打印（固定格式）
  TreeNode *p = root->child[0];
  
  out << endl << endl << "\t.data" << endl;
  for(;p;p=p->sibling){
		if(p->nodekind == Decl)
		gen_decl(out, p);//输出变量声明语句
	}
	//临时变量的声明语句
	for (i=0; i < temp_var_seq; i++)
		out << "\t\tt" <<  i << " DWORD 0" << endl;
	out << "\t\tbuffer BYTE 128 dup(0)" << endl;
	out << "\t\tLF BYTE 13, 10, 0" << endl;
	out<<"\thint_end BYTE '请按任意键继续',0"<<endl;
	
	p = root->child[0];
	out << endl << endl << "\t.code" << endl;
	out<<"_start:"<<endl;
	//TreeNode *p2;
	for(;p;p=p->sibling){
			recursive_gen_code(out, p);//输出代码生成语句
	}
	out<<"\tinvoke crt_printf,  addr hint_end"<<endl;
	out<<"\tinvoke crt__getch"<<endl<<"\tinvoke crt__exit, 0"<<endl; //实现输入任意键退出 
	out<<"END _start"<<endl;
}

void gen_header(ostream &out)//打印程序头部
{
  out << "\t.486" << endl;
  out << "\t.model flat, stdcall" << endl;
  out << "\toption casemap :none" << endl;
  out << endl;
  out << "\tinclude C:\\masm32\\macros\\macros.asm" << endl;
  out << endl;
  out << "\tinclude C:\\masm32\\include\\msvcrt.inc" << endl;
  out << "\tincludelib C:\\masm32\\lib\\msvcrt.lib" << endl;
}

void gen_decl(ostream &out, TreeNode *t)// 针对每一个声明语句输出其汇编代码
{
  //在语句的声明产生式中，已将数据类型赋给Decl节点的type属性
  t=t->child[1];
  if(t->type == Int) {
	for (TreeNode *p = t; p; p = p->sibling)
		out << "\t\t_" << p->attr.symbol << " DWORD 0" << endl;//设置初始值为0
	return ;
  }
  if(t->type == Char) {
	for (TreeNode *p = t; p; p = p->sibling)
		out << "\t\t_" << p->attr.symbol << " BYTE 0" << endl;//设置初始值为0
  }
  else
	cout<<t->lineo<<" 声明的数据类型不是int或char\n";
  return ;
}

void recursive_gen_code(ostream &out, TreeNode *t)//递归代码生成函数入口,注意使用递归：树可能长得深！
{
  int i;
  if(t!=NULL){
	//为在分函数里执行递归！
  
	if (t->nodekind== Stmt)
		stmt_gen_code(out, t);
	else if (t->nodekind == Expr && t->kind==Op)
		expr_gen_code(out, t);
  }//if(t!=NULL)
}

void expr_gen_code(ostream &out, TreeNode *t){
	int i;
	if(t->attr.op!=AND && t->attr.op!=OR && t->attr.op!=NOT)
		for(i=0;i<MAX && t->child[i]!=NULL ;i++)
			recursive_gen_code(out,t->child[i]);//这里调用递归，实现如1+2+3的运算
	TreeNode *e1 = t->child[0];
	TreeNode *e2 = t->child[1];
	switch (t->attr.op){
	case PLUS:
		out << "\tMOV eax, ";
		if (e1->kind == Idk)
			out << "_" << e1->attr.symbol;
		else if (e1->kind == Const_num)
			out << e1->attr.val;
		else if (e1->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e1->attr.charval);//16进制ASCII码
			out << buffer;
			}
		else out << "t" << e1->temp_var;
		out << endl;					//param1
		out << "\tADD eax, ";
		if (e2->kind == Idk)
			out << "_" << e2->attr.symbol;
		else if (e2->kind == Const_num)
			out << e2->attr.val;
		else if (e2->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e2->attr.charval);
			out << buffer;
			}
		else out << "t" << e2->temp_var;
		out << endl;					//param2
		out << "\tMOV t" << t->temp_var << ", eax" << endl;   //临时变量
		break;
	case MINUS:
		out << "\tMOV eax, ";
		if (e1->kind == Idk)
			out << "_" << e1->attr.symbol;
		else if (e1->kind == Const_num)
			out << e1->attr.val;
		else if (e1->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e1->attr.charval);
			out << buffer;
			}
		else out << "t" << e1->temp_var;
		out << endl;
		out << "\tSUB eax, ";
		if (e2->kind == Idk)
			out << "_" << e2->attr.symbol;
		else if (e2->kind == Const_num)
			out << e2->attr.val;
		else if (e2->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e2->attr.charval);
			out << buffer;
			}
		else out << "t" << e2->temp_var;
		out << endl;
		out << "\tMOV t" << t->temp_var << ", eax" << endl;
		break;
	case MUL:
		out << "\tMOV eax, ";
		if (e1->kind == Idk)
			out << "_" << e1->attr.symbol;
		else if (e1->kind == Const_num)
			out << e1->attr.val;
		else if (e1->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e1->attr.charval);
			out << buffer;
			}
		else out << "t" << e1->temp_var;
		out << endl;   //param1
		out<<"\tIMUL eax,";
		if (e2->kind == Idk)
			out << "_" << e2->attr.symbol;
		else if (e2->kind == Const_num)
			out << e2->attr.val;
		else if (e2->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e2->attr.charval);
			out << buffer;
			}
		else out << "t" << e2->temp_var;
		out << endl;
		out << "\tMOV t" << t->temp_var << ", eax" << endl;
		break;
	case DIV:
		out<<"\tXOR dx,dx"<<endl;//除法时，先将被除数高位清零（AX存放低16位，DX存放高16位）
		out << "\tMOV eax, ";//被除数放入eax中
		if (e1->kind == Idk)
			out << "_" << e1->attr.symbol;
		else if (e1->kind == Const_num)
			out << e1->attr.val;
		else if (e1->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e1->attr.charval);
			out << buffer;
			}
		else out << "t" << e1->temp_var;
		out << endl;   //param1
		out << "\tMOV ebx,";//除数放入ebx中
		if (e2->kind == Idk)
			out << "_" << e2->attr.symbol;
		else if (e2->kind == Const_num)
			out << e2->attr.val;
		else if (e2->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e2->attr.charval);
			out << buffer;
			}
		else out << "t" << e2->temp_var;
		out << endl;
		out<<"\tDIV bx"<<endl;//进行除法
		out<<"\tXOR ah,ah"<<endl;//将余数位置0
		out << "\tMOV t" << t->temp_var << ", eax" << endl;
		break;
	case ASSIGN:
		if(e1->type==Int)
				{
					out<<"\tMOV eax, ";
					if(e2->kind==Idk)
						out<<"_"<<e2->attr.symbol;
					else if(e2->kind==Const_num)
						out<<e2->attr.val;
					else
						out<<"t"<<e2->temp_var;
					out<<endl;
					out<<"\tMOV _"<<e1->attr.symbol<<", eax"<<endl;
				}
				if(e1->type==Char)
				{
						
					if(e2->kind==Idk)
					{
						out<<"\tMOV al, _"<<e2->attr.symbol;
					}
					else if(e2->kind==Const_char)
					{
						char buffer[3];
						sprintf(buffer, "%xh", e2->attr.charval);
						out<<"\tMOV eax, 0\n\tMOV al, "<<buffer;
					}
					else
					{
						out<<"\tMOV al, "<<"t"<<e2->temp_var;
					}
						
					out<<endl;
					out<<"\tMOV _"<<e1->attr.symbol<<", al"<<endl;
				}
		break;
	case DPLUS:
		out << "\tMOV eax,_"<< e1->attr.symbol<<endl;
		out << "\tADD eax, 1"<<endl;
		out << "\tMOV _" << e1->attr.symbol << ", eax" << endl;   //临时变量
		break;
	case DMINUS:
		out << "\tMOV eax,_"<< e1->attr.symbol<<endl;
		out << "\tSUB eax, 1"<<endl;
		out << "\tMOV _" << e1->attr.symbol << ", eax" << endl;   //临时变量
		break;
	case LE:   //<=
		out << "\tMOV eax, ";
		if (e1->kind == Idk)
			out << "_" << e1->attr.symbol;
		else if (e1->kind == Const_num)
			out << e1->attr.val;
		else if (e1->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e1->attr.charval);
			out << buffer;
			}
		else out << "t" << e1->temp_var;
		out << endl;   //param1
		out << "\tCMP eax, ";
		if (e2->kind == Idk)
			out << "_" << e2->attr.symbol;
		else if (e2->kind == Const_num)
			out << e2->attr.val;
		else if (e2->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e2->attr.charval);
			out << buffer;
			}
		else out << "t" << e2->temp_var;
		out << endl;//param2
		out << "\tJNG " << t->label.true_label << endl;
		out << "\tJMP " << t->label.false_label << endl;
		break;
	case GE:   //>=
		out << "\tMOV eax, ";
		if (e1->kind == Idk)
			out << "_" << e1->attr.symbol;
		else if (e1->kind == Const_num)
			out << e1->attr.val;
		else if (e1->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e1->attr.charval);
			out << buffer;
			}
		else out << "t" << e1->temp_var;
		out << endl;   //param1
		out << "\tCMP eax, ";
		if (e2->kind == Idk)
			out << "_" << e2->attr.symbol;
		else if (e2->kind == Const_num)
			out << e2->attr.val;
		else if (e2->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e2->attr.charval);
			out << buffer;
			}
		else out << "t" << e2->temp_var;
		out << endl;//param2
		out << "\tJGE " << t->label.true_label << endl;
		out << "\tJMP " << t->label.false_label << endl;
		break;
	case LT:   //<
		out << "\tMOV eax, ";
		if (e1->kind == Idk)
			out << "_" << e1->attr.symbol;
		else if (e1->kind == Const_num)
			out << e1->attr.val;
		else if (e1->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e1->attr.charval);
			out << buffer;
			}
		else out << "t" << e1->temp_var;
		out << endl;   //param1
		out << "\tCMP eax, ";
		if (e2->kind == Idk)
			out << "_" << e2->attr.symbol;
		else if (e2->kind == Const_num)
			out << e2->attr.val;
		else if (e2->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e2->attr.charval);
			out << buffer;
			}
		else out << "t" << e2->temp_var;
		out << endl;//param2
		out << "\tJL " << t->label.true_label << endl;
		out << "\tJMP " << t->label.false_label << endl;
		break;
	case GT:   //>
		out << "\tMOV eax, ";
		if (e1->kind == Idk)
			out << "_" << e1->attr.symbol;
		else if (e1->kind == Const_num)
			out << e1->attr.val;
		else if (e1->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e1->attr.charval);
			out << buffer;
			}
		else out << "t" << e1->temp_var;
		out << endl;   //param1
		out << "\tCMP eax, ";
		if (e2->kind == Idk)
			out << "_" << e2->attr.symbol;
		else if (e2->kind == Const_num)
			out << e2->attr.val;
		else if (e2->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e2->attr.charval);
			out << buffer;
			}
		else out << "t" << e2->temp_var;
		out << endl;//param2
		out << "\tJG " << t->label.true_label << endl;
		out << "\tJMP " << t->label.false_label << endl;
		break;
	case EQ:   //==
		out << "\tMOV eax, ";
		if (e1->kind == Idk)
			out << "_" << e1->attr.symbol;
		else if (e1->kind == Const_num)
			out << e1->attr.val;
		else if (e1->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e1->attr.charval);
			out << buffer;
			}
		else out << "t" << e1->temp_var;
		out << endl;   //param1
		out << "\tSUB eax, ";
		if (e2->kind == Idk)
			out << "_" << e2->attr.symbol;
		else if (e2->kind == Const_num)
			out << e2->attr.val;
		else if (e2->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e2->attr.charval);
			out << buffer;
			}
		else out << "t" << e2->temp_var;
		out << endl;//param2
		out << "\tJZ " << t->label.true_label << endl;
		out << "\tJMP " << t->label.false_label << endl;
		break;
	case NEQ:   //!=
		out << "\tMOV eax, ";
		if (e1->kind == Idk)
			out << "_" << e1->attr.symbol;
		else if (e1->kind == Const_num)
			out << e1->attr.val;
		else if (e1->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e1->attr.charval);
			out << buffer;
			}
		else out << "t" << e1->temp_var;
		out << endl;   //param1
		out << "\tSUB eax, ";
		if (e2->kind == Idk)
			out << "_" << e2->attr.symbol;
		else if (e2->kind == Const_num)
			out << e2->attr.val;
		else if (e2->kind == Const_char){
			char buffer[3];
			sprintf(buffer, "%xh", e2->attr.charval);
			out << buffer;
			}
		else out << "t" << e2->temp_var;
		out << endl;//param2
		out << "\tJNZ " << t->label.true_label << endl;
		out << "\tJMP " << t->label.false_label << endl;
		break;
	case AND:// if e1 && e2
		recursive_gen_code(out,e1);
		out<<e1->label.true_label<<":"<<endl;
		recursive_gen_code(out,e2);
		break;
	case OR:// if e1 || e2
		recursive_gen_code(out,e1);
		out<<e1->label.false_label<<":"<<endl;
		recursive_gen_code(out,e2);
		break;
	case NOT:// if ！e1 
		recursive_gen_code(out,e1);
		break;
	default:
		break;
	
	}//switch
}


void stmt_gen_code(ostream &out, TreeNode *t){

	if (t->kind == Block){    //复合语句
		for (TreeNode *p = t->child[0]; p; p = p->sibling)
			recursive_gen_code(out, p);//因为复合语句的各分语句是用sibling串联起来的
		out<<endl;
		return ;
    }
    if(t->kind == Input){  //输入
		TreeNode *p=t->child[0];
		if(p->kind==Idk){
			if(p->type==Int)
				out<<"\tinvoke crt_scanf, SADD(\"%d\",13,10),addr _"<<t->child[0]->attr.symbol<<endl;
			if(p->type==Char)
				out<<"\tinvoke crt_scanf, SADD(\"%c\"),addr _"<<t->child[0]->attr.symbol<<endl;

		}
		//out<<"\tinvoke crt_scanf,SADD('%d',0),addr _"<<t->child[0]->attr.symbol<<endl;
		return ;
    }
    if(t->kind == Output){   //输出
		TreeNode *p=t->child[0];
		if(p->kind==Idk){
			if(p->type==Int)
				out<<"\tinvoke crt_printf, SADD(\"%d\",13,10), _"<<t->child[0]->attr.symbol<<endl;
			else if(p->type==Char){
				out<<"\tMOV eax, 0\n\tMOV AL, _"<<t->child[0]->attr.symbol<<endl;
				out<<"\tinvoke crt_printf, SADD(\"%c\",13,10), eax"<<endl;
			}
		}
		else if(p->kind==Const_num)
			out<<"\tinvoke crt_printf, SADD(\"%d\",13,10), _"<<t->child[0]->attr.val<<endl;
		else if(p->kind==Const_char)
			out<<"\tinvoke crt_printf, SADD(\"%s\",13,10), _"<<t->child[0]->attr.charval<<endl;
		else{
			recursive_gen_code(out,t->child[0]);
			out<<"\tinvoke crt_printf, SADD(\"%d\",13,10), eax"<<endl;
		}
		return ;
    }
    if(t->kind == If){   //if
		TreeNode* e=t->child[0];TreeNode* s1=t->child[1];TreeNode* s2=t->child[2];
		recursive_gen_code(out,e);//e S1 +S2
		out<<e->label.true_label<<":"<<endl;
		recursive_gen_code(out,s1);
		if(s2!=NULL){//有else
			out<<"\tJMP "<<t->label.next_label<<endl;
			out<<e->label.false_label<<":"<<endl;
			recursive_gen_code(out,s2);
		}
		if(t->label.next_label!="")
			out<<t->label.next_label<<":"<<endl;
		return ;
    }
    if(t->kind == While){   //while循环
		TreeNode* e=t->child[0];TreeNode* s1=t->child[1];
		out<<t->label.begin_label<<":"<<endl;
		recursive_gen_code(out,e);
		out<<e->label.true_label<<":"<<endl;
		recursive_gen_code(out,s1);
		out<<"\tJMP "<<t->label.begin_label<<endl;
		if(t->label.next_label!="")
			out<<t->label.next_label<<":"<<endl;
		return ;
    }
    if(t->kind == For){   //for循环 for(e;s1;s2){s3}
		TreeNode* e=t->child[0];TreeNode* s1=t->child[1];TreeNode* s2=t->child[2];TreeNode* s3=t->child[3];
		recursive_gen_code(out,e);//初始化
		out<<t->label.begin_label<<":"<<endl;//开始的标志
		recursive_gen_code(out,s1);//判断语句
		out<<s1->label.true_label<<":"<<endl;//执行体标号
		recursive_gen_code(out,s3);//执行体
		recursive_gen_code(out,s2);//s2
		out<<"\tJMP "<<t->label.begin_label<<endl;
		if(t->label.next_label!="")
			out<<t->label.next_label<<":"<<endl;
		return ;
    }
    cout<<t->lineo<<" panic in stmt_gen_code"<<endl;
}

//**************


//**********************
//标号的产生
void gen_label()
{
  //recursive_gen_label(start);
  TreeNode *p = root->child[0];
  
  for(;p->nodekind == Decl;p=p->sibling);//先跳过声明语句
  for(;p;p=p->sibling)
		recursive_gen_label(p);
}
void recursive_gen_label(TreeNode *t)
{
  int i;
  if(t!=NULL){
	if (t->nodekind== Stmt)
		stmt_gen_label(t);
	else if (t->nodekind == Expr)
		expr_gen_label(t);
	for(i=0;i<MAX;i++)
		recursive_gen_label(t->child[i]);
	
  }//if(t!=NULL)
}

void stmt_gen_label(TreeNode *t)//标号的产生：if while for block
{
	
	TreeNode *e=t->child[0];
	TreeNode *s1=t->child[1];
	TreeNode *s2=t->child[2];
	TreeNode *s3=t->child[3];
	int i;
	switch(t->kind){
	case If:
		if(s2==NULL){//if e then s1
			if(e->label.true_label=="")
				e->label.true_label=newlabel();
			if(t->label.next_label=="")
				t->label.next_label=newlabel();
			e->label.false_label=t->label.next_label;
			s1->label.next_label=t->label.next_label;
		}
		else{
			if(e->label.true_label=="")
				e->label.true_label=newlabel();
			if(t->label.next_label=="")
				t->label.next_label=newlabel();
			e->label.false_label=newlabel();
			s1->label.next_label=t->label.next_label;
			s2->label.next_label=t->label.next_label;
		}
	break;
	case While://while(e)s1
		t->label.begin_label=newlabel();
		e->label.true_label=newlabel();
		if(t->label.next_label=="")
			t->label.next_label=newlabel();
		e->label.false_label=t->label.next_label;
		s1->label.next_label=t->label.begin_label;
	break;
	case For: //for(e,s1,s2)s3
		t->label.begin_label=newlabel();
		s1->label.true_label=newlabel();
		if(t->label.next_label=="")
			t->label.next_label=newlabel();
		s1->label.false_label=t->label.next_label;
		s1->label.next_label=t->label.begin_label;	
	break;
	case Block:
		//cout<<"in block"<<endl;
		TreeNode* p=t->child[0];
		TreeNode* pre=p;
		for(;p;p=p->sibling){
			pre=p;
			if(p->sibling==NULL)
				p->label.next_label=t->label.next_label;
			recursive_gen_label(p);
		}
		
		//pre->label.next_label=t->label.next_label;
	break;//对复合语句的每个直连语句建立顺序连接的关系
	}//switch
}

void expr_gen_label(TreeNode *t)// and or not 的label设置
{
	TreeNode *e1 = t->child[0];
	TreeNode *e2 = t->child[1];
	switch (t->attr.op){
	case AND:
		if(e1->label.true_label=="")
			e1->label.true_label=newlabel();
		if(t->label.false_label=="")
			t->label.false_label=newlabel();
		if(t->label.true_label=="")
			t->label.true_label=newlabel();
		e1->label.false_label=t->label.false_label;
		e2->label.true_label=t->label.true_label;
		e2->label.false_label=t->label.false_label;
	break;	
	case OR:
		if(t->label.true_label=="")
			t->label.true_label=newlabel();
		e1->label.true_label=t->label.true_label;
		e1->label.false_label=newlabel();
		e2->label.true_label=t->label.true_label;
		if(t->label.false_label=="")
			t->label.false_label=newlabel();
		e2->label.false_label=t->label.false_label;
	break;	
	case NOT:
		if(t->label.true_label=="")
			t->label.true_label=newlabel();
		if(t->label.false_label=="")
			t->label.false_label=newlabel();
		e1->label.false_label=t->label.true_label;
		e1->label.true_label=t->label.false_label;
	break;
	}
}

int main(void)
{
	int n = 1;
	mylexer lexer;
	myparser parser;
	ifstream in("test.txt");
	ofstream out("result.asm");
	if (parser.yycreate(&lexer)) {
		if (lexer.yycreate(&parser)) {
			lexer.yyin=&in;
			n = parser.yyparse();
		}
	}
	in.close();
	cout<<endl;
	gen_label();//根据语法树进行标号的设置
	gen_code(out);//代码生成
	cout<<"汇编代码生成完毕"<<endl;
	system("pause");
	return n;
}


