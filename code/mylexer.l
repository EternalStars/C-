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
  struct TreeNode*sibling;//����ƥ���ʱ�����ƥ���һ���仰���ʿ���֪�����ֵܽڵ㣬�����޷�֪���丸�ڵ�
  int nodekind;
  int kind;
  
  Type1 type;
  union{
   int op;//������token���壬����int�Ͳ������ŵ�ֵ
   int val;//���ֵ�ֵ
   char charval;
   char* symbol;//id��ֵ
  }attr;//ֻ��id,const��op������attrֵ
  int lineo=0;//�ڵ����
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
/*���͡��������ؼ���*/
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
/*��������*/
"+"				    	{return PLUS;}
"-"				    	{return MINUS;}
"*"				    	{return MUL;}
"/"				    	{return DIV;}
"%"				    	{return MOD;}
"++"				    {return DPLUS;}
"--"				   	{return DMINUS;}
"=="				   	{return EQ;}
/*�߼�����*/
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
					
					//�������ַ���ָ�룬����ע��Ҫ�������
					//����yytext����ֵ��}���ḳ�����е�symbol
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