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
* myparser.h
* C++ header file generated from myparser.y.
* 
* Date: 12/26/19
* Time: 18:51:03
* 
* AYACC Version: 2.07
****************************************************************************/

#ifndef _MYPARSER_H
#define _MYPARSER_H

#include <yycpars.h>

/////////////////////////////////////////////////////////////////////////////
// myparser

#ifndef YYEXPPARSER
#define YYEXPPARSER
#endif

class YYEXPPARSER YYFAR myparser : public _YL yyfparser {
public:
	myparser();
	virtual ~myparser();

protected:
	void yytables();
	virtual void yyaction(int action);
#ifdef YYDEBUG
	void YYFAR* yyattribute1(int index) const;
	void yyinitdebug(void YYFAR** p, int count) const;
#endif

	// attribute functions
	virtual void yystacktoval(int index);
	virtual void yyvaltostack(int index);
	virtual void yylvaltoval();
	virtual void yyvaltolval();
	virtual void yylvaltostack(int index);

	virtual void YYFAR* yynewattribute(int count);
	virtual void yydeleteattribute(void YYFAR* attribute);
	virtual void yycopyattribute(void YYFAR* dest, const void YYFAR* src, int count);

public:
#line 165 ".\\myparser.y"

	// place any extra class members here
public:
	void Display(struct TreeNode*t,int *con);
	void ShowNode(struct TreeNode*t);
	int Check(struct TreeNode*t);

#line 73 "myparser.h"
};

#ifndef YYPARSERNAME
#define YYPARSERNAME myparser
#endif

#line 184 ".\\myparser.y"

#ifndef YYSTYPE
#define YYSTYPE TreeNode*
#endif

#line 86 "myparser.h"
#define IF 257
#define MAIN 258
#define FOR 259
#define WHILE 260
#define CIN 261
#define COUT 262
#define INT 263
#define CHAR 264
#define VOID 265
#define BOOL 266
#define STRING 267
#define ID 268
#define NUMBER 269
#define Constchar 270
#define PLUS 271
#define MINUS 272
#define MUL 273
#define DIV 274
#define MOD 275
#define DPLUS 276
#define DMINUS 277
#define GT 278
#define LT 279
#define GE 280
#define LE 281
#define NEQ 282
#define AND 283
#define OR 284
#define NOT 285
#define ASSIGN 286
#define LFP 287
#define RFP 288
#define LSP 289
#define RSP 290
#define COMMA 291
#define SEMI 292
#define LP 293
#define RP 294
#define LM 295
#define RM 296
#define RETURN 297
#define EQ 298
#define ELSE 299
#endif
