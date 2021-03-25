%{
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
%}

extern YYSTYPE yylval
// lexical analyser name
%name mylexer
// class definition
MUTICOMMENT \/\*([^\*"]|(\".*\")|((\*)+[^\/]?))*\*\/
SINGLECOMMENT \/\/[^\n]*
delim [ \n\t]*
ws {delim}+
letter [A-Za-z]
id [A-Za-z_]([A-Za-z_]|[0-9])*
number [0-9]
digit {number}+(\.{number}+)?(E[+-]?{number}+)?
con_char \'.\'
%%

%{
	// extract yylval for use later on in actions
	YYSTYPE YYFAR& yylval = *(YYSTYPE YYFAR*)yyparserptr->yylvalptr;
%}

// place your Lex rules here
/////////////////////////////////////////////////////////////////////////////
// rules section
{MUTICOMMENT}		{/* do nothing */}
{SINGLECOMMENT}		{/* do nothing */}
{ws}				{/*doing nothing*/}
","				        {return COMMA;}
";"					    {return SEMI;}
"("					    {return LP;}
")"					    {return RP;}
"{"					    {return LFP;}
"}"					    {return RFP;}
"["					    {return LSP;}
"]"				     	{return RSP;}
/*句型、变量、关键字*/
"if"					{return IF;}
"else"					{return ELSE;}
"while"					{return WHILE;}
"for"					{return FOR;}
"cin"					{return CIN;}
"cout"					{return COUT;}
"void"					{return VOID;}
"int"					{return INT;}
"char"					{return CHAR;}
"bool"					{return BOOL;}
"string"				{return STRING;}
"="				    	{return ASSIGN;}
"main"                  {return MAIN;}
"return"                {return RETURN;}
/*算术运算*/
"+"				    	{return PLUS;}
"-"				    	{return MINUS;}
"*"				    	{return MUL;}
"/"				    	{return DIV;}
"%"				    	{return MOD;}
"++"				    {return DPLUS;}
"--"				   	{return DMINUS;}
"=="				   	{return EQ;}
/*逻辑运算*/
"<<"                    {return LM;}
">>"                    {return RM;}
">="				   	{return GE;}
"<="				    {return LE;}
">"				    	{return GT;}
"<"				    	{return LT;}
"!="				   	{return NEQ;}
"&&"				   	{return AND;}
"||"				   	{return OR;}
"!"				    	{return NOT;}


{id}	{
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
				}
{digit}	{
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
		}
{con_char}	{
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
		}
%%

/////////////////////////////////////////////////////////////////////////////
// programs section
