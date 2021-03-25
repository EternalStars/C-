%{
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
%}

/////////////////////////////////////////////////////////////////////////////
// declarations section

// parser name
%name myparser

// class definition
{
	// place any extra class members here
public:
	void Display(struct TreeNode*t,int *con);
	void ShowNode(struct TreeNode*t);
	int Check(struct TreeNode*t);
}

// constructor
{
	// place any extra initialisation code here
}

// destructor
{
	// place any extra cleanup code here
}

// attribute type
%include {
#ifndef YYSTYPE
#define YYSTYPE TreeNode*
#endif
}

// place any declarations here
%token IF MAIN FOR WHILE CIN COUT//关键字
%token INT CHAR VOID BOOL STRING
%token ID NUMBER Constchar
%token PLUS MINUS MUL DIV MOD DPLUS DMINUS//操作符
%token GT LT GE LE NEQ AND OR NOT ASSIGN//逻辑关系
%token LFP RFP LSP RSP COMMA SEMI LP RP LM RM//标点符号
%token RETURN

%left COMMA
%right ASSIGN
%left EQ NEQ
%left LT LE GT GE
%left PLUS MINUS
%left MUL DIV MOD
%left   DPLUS DMINUS
%left	LP RP LSP RSP LFP RFP LM RM
%right ELSE

%%

/////////////////////////////////////////////////////////////////////////////
// rules section

// place your YACC rules here (there must be at least one)
start	:MAIN LP RP block	{$$ = $4;root=$4;int con=1;Display(root,&con);}
		;
block	:LFP stmts RFP	{$$=newStmtNode(Block);$$->child[0]=$2;}
		;
stmts	:stmt stmts	{$$=$1;$$->sibling=$2;}
		|stmt	{$$=$1;}
		;	
stmt	:expr_stmt	{$$=$1;}
		|var_stmt	{$$=$1;}
		|if_stmt	{$$=$1;}
		|while_stmt	{$$=$1;}
		|for_stmt	{$$=$1;}
		|block	{$$=$1;}
		|input_stmt	{$$=$1;}
		|output_stmt	{$$=$1;}
		|func_stmt	{$$=$1;}
		|func_asked_stmt	{$$=$1;}
		|return_stmt	{$$=$1;}
		;
type_var	:INT	{$$=newExprNode(Type);$$->type=Int;}
			|CHAR	{$$=newExprNode(Type);$$->type=Char;}
			|VOID	{$$=newExprNode(Type);$$->type=Void;}
			|BOOL	{$$=newExprNode(Type);$$->type=Bool;}
			;
id_list	:expr COMMA id_list	{$$=$1;$$->sibling=$3;}
		|expr	{$$=$1;}
		;
input_stmt	:CIN RM ID SEMI	{$$=newStmtNode(Input);$$->child[0]=$3;}
			;
output_stmt	:COUT LM term SEMI	{$$=newStmtNode(Output);$$->child[0]=$3;}
			;
var_stmt	:type_var id_list SEMI	{$$=newDeclNode(Var);$$->child[0]=$1;$$->child[1]=$2;
										TreeNode *p=$2;
										while(p!=NULL){
											p->type=$1->type;
											string str;
											for(int i=0;i<strlen(p->attr.symbol);i++)str+=p->attr.symbol[i];
											str_index[str]=$1->type;
											p=p->sibling;										
										}
									 }
			;
func_var	:func_var1 COMMA func_var	{$$=$1;$$->sibling=$3;}
			|func_var1	{$$=$1;}
			;
func_var1	:type_var ID	{$$=newDeclNode(FuncVar);$$->child[0]=$1;$$->child[1]=$2;}
			;
expr_stmt	:expr SEMI	{$$=$1;}
			|SEMI{$$=newStmtNode(Empty);}
			;
//赋值
expr	:ID ASSIGN expr	{$$=newExprNode(Op);$$->child[0]=$1;$$->child[1]=$3;$$->attr.op=ASSIGN;set_temp_var($$);}
		|or_expr	{$$=$1;}
		;
//与或非
or_expr	:or_expr OR and_expr	{$$=newExprNode(Op);$$->child[0]=$1;$$->child[1]=$3;$$->attr.op=OR;set_temp_var($$);}
		|and_expr	{$$=$1;}
		;
and_expr	:and_expr AND eq_expr	{$$=newExprNode(Op);$$->child[0]=$1;$$->child[1]=$3;$$->attr.op=AND;set_temp_var($$);}
			|eq_expr	{$$=$1;}
			;
//逻辑运算
eq_expr	:eq_expr EQ simple_expr   {$$=newExprNode(Op);$$->attr.op=EQ;$$->child[0]=$1;$$->child[1]=$3;set_temp_var($$);}
        |eq_expr GE simple_expr   {$$=newExprNode(Op);$$->attr.op=GE;$$->child[0]=$1;$$->child[1]=$3;set_temp_var($$);}
        |eq_expr LE simple_expr   {$$=newExprNode(Op);$$->attr.op=LE;$$->child[0]=$1;$$->child[1]=$3;set_temp_var($$);}
        |eq_expr GT simple_expr   {$$=newExprNode(Op);$$->attr.op=GT;$$->child[0]=$1;$$->child[1]=$3;set_temp_var($$);}//>
        |eq_expr LT simple_expr   {$$=newExprNode(Op);$$->attr.op=LT;$$->child[0]=$1;$$->child[1]=$3;set_temp_var($$);}
        |eq_expr NEQ simple_expr  {$$=newExprNode(Op);$$->attr.op=NEQ;$$->child[0]=$1;$$->child[1]=$3;set_temp_var($$);}
        |eq_expr LM simple_expr   {$$=newExprNode(Op);$$->attr.op=LM;$$->child[0]=$1;$$->child[1]=$3;set_temp_var($$);}
        |eq_expr RM simple_expr   {$$=newExprNode(Op);$$->attr.op=RM;$$->child[0]=$1;$$->child[1]=$3;set_temp_var($$);}
        |simple_expr	{$$=$1;}
        ;
//算术运算
simple_expr  :simple_expr PLUS simple_expr    {$$=newExprNode(Op);$$->attr.op=PLUS;$$->child[0]=$1;$$->child[1]=$3;set_temp_var($$);}
             |simple_expr MINUS simple_expr   {$$=newExprNode(Op);$$->attr.op=MINUS;$$->child[0]=$1;$$->child[1]=$3;set_temp_var($$);}
             |simple_expr MUL simple_expr     {$$=newExprNode(Op);$$->attr.op=MUL;$$->child[0]=$1;$$->child[1]=$3;set_temp_var($$);}
             |simple_expr DIV simple_expr     {$$=newExprNode(Op);$$->attr.op=DIV;$$->child[0]=$1;$$->child[1]=$3;set_temp_var($$);}
             |simple_expr MOD simple_expr	{$$=newExprNode(Op);$$->attr.op=MOD;$$->child[0]=$1;$$->child[1]=$3;set_temp_var($$);}
             |simple_expr DPLUS		{$$=newExprNode(Op);$$->attr.op=DPLUS;$$->child[0]=$1;set_temp_var($$);}
             |simple_expr DMINUS	{$$=newExprNode(Op);$$->attr.op=DMINUS;$$->child[0]=$1;set_temp_var($$);}
             |term	{$$=$1;}
             ;
term	:LP expr RP	{$$=$2;}
		|ID	{$$=$1;}
		|NUMBER	{$$=$1;}
		|Constchar	{$$=$1;}
		|NOT term	{$$=newExprNode(Op);$$->attr.op=NOT;$$->child[0]=$2;set_temp_var($$);}
		;

if_stmt	:IF LP expr RP stmt	{$$=newStmtNode(If);$$->child[0]=$3;$$->child[1]=$5;}
		|IF LP expr RP stmt ELSE stmt	{$$=newStmtNode(If);$$->child[0]=$3;$$->child[1]=$5;$$->child[2]=$7;}
		;
for_stmt	:FOR LP expr SEMI expr SEMI expr RP stmt{$$ = newStmtNode(For);$$->attr.op=1;$$->child[0]=$3;$$->child[1]=$5;$$->child[2]=$7;$$->child[3]=$9;}
			|FOR LP SEMI expr SEMI expr RP stmt{$$ = newStmtNode(For);$$->attr.op=0;$$->child[0]=$4;$$->child[1]=$6;$$->child[2]=$8;}
			|FOR LP expr SEMI SEMI expr RP stmt{$$ = newStmtNode(For);$$->attr.op=-1;$$->child[0]=$3;$$->child[1]=$6;$$->child[2]=$8;}
			|FOR LP expr SEMI expr SEMI RP stmt{$$ = newStmtNode(For);$$->attr.op=1;$$->child[0]=$3;$$->child[1]=$5;$$->child[2]=$8;}
			|FOR LP SEMI SEMI expr RP stmt{$$ = newStmtNode(For);$$->attr.op=-1;$$->child[0]=$5;$$->child[1]=$7;}
			|FOR LP SEMI expr SEMI RP stmt{$$ = newStmtNode(For);$$->attr.op=0;$$->child[0]=$4;$$->child[1]=$7;}
			|FOR LP expr SEMI SEMI RP stmt{$$ = newStmtNode(For);$$->attr.op=-1;$$->child[0]=$3;$$->child[1]=$7;}
			|FOR LP SEMI SEMI RP stmt{$$ = newStmtNode(For);$$->attr.op=-1;$$->child[0]=$6;}
			;
while_stmt	:WHILE LP expr RP stmt	{$$=newStmtNode(While);$$->child[0]=$3;$$->child[1]=$5;}
			;
func_stmt	:type_var ID LP func_var RP block	{$$=newStmtNode(Func);$$->child[0]=$1;$$->child[1]=$2;$$->child[2]=$4;$$->child[3]=$6;}
			;
func_asked_stmt	:type_var ID ASSIGN func_asked_stmt1	{$$=newStmtNode(Func);$$->child[0]=$1;$$->child[1]=$2;$$->child[2]=$4;}
				|func_asked_stmt1	{$$=$1;}
				;
func_asked_stmt1	:ID LP expr RP SEMI	{$$=newStmtNode(Func_asked);$$->child[0]=$1;$$->child[1]=$3;}
					;
expr_func	:expr COMMA expr_func	{$$=newStmtNode(Expr_func);$$->child[0]=$1;$$->child[1]=$3;}
			|expr	{$$=newStmtNode(Expr_func);$$->child[0]=$1;}
			;
return_stmt	:RETURN term	{$$=newStmtNode(Return);$$->child[0]=$2;}
			;

%%

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

