/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     tokALL0 = 258,
     tokALL1 = 259,
     tokALL2 = 260,
     tokAND = 261,
     tokARROW = 262,
     tokASSERT = 263,
     tokBIIMPL = 264,
     tokCOLON = 265,
     tokCOMMA = 266,
     tokCONST = 267,
     tokDEFAULT1 = 268,
     tokDEFAULT2 = 269,
     tokDOT = 270,
     tokEMPTY = 271,
     tokEQUAL = 272,
     tokEX0 = 273,
     tokEX1 = 274,
     tokEX2 = 275,
     tokFALSE = 276,
     tokGREATER = 277,
     tokGREATEREQ = 278,
     tokGUIDE = 279,
     tokIMPL = 280,
     tokIN = 281,
     tokINTER = 282,
     tokINTERVAL = 283,
     tokLBRACE = 284,
     tokLBRACKET = 285,
     tokLESS = 286,
     tokLESSEQ = 287,
     tokLET0 = 288,
     tokLET1 = 289,
     tokLET2 = 290,
     tokLPAREN = 291,
     tokMACRO = 292,
     tokMAX = 293,
     tokMIN = 294,
     tokMINUS = 295,
     tokMODULO = 296,
     tokNOT = 297,
     tokNOTEQUAL = 298,
     tokNOTIN = 299,
     tokOR = 300,
     tokPLUS = 301,
     tokPRED = 302,
     tokRBRACE = 303,
     tokRESTRICT = 304,
     tokRBRACKET = 305,
     tokUNIVROOT = 306,
     tokRPAREN = 307,
     tokSEMICOLON = 308,
     tokSETMINUS = 309,
     tokSLASH = 310,
     tokSTAR = 311,
     tokVERIFY = 312,
     tokSUB = 313,
     tokTREE = 314,
     tokTRUE = 315,
     tokUNION = 316,
     tokUNIVERSE = 317,
     tokUP = 318,
     tokVAR0 = 319,
     tokVAR1 = 320,
     tokVAR2 = 321,
     tokWHERE = 322,
     tokINCLUDE = 323,
     tokIMPORT = 324,
     tokEXPORT = 325,
     tokPREFIX = 326,
     tokM2LSTR = 327,
     tokM2LTREE = 328,
     tokLASTPOS = 329,
     tokINSTATESPACE = 330,
     tokEXECUTE = 331,
     tokTYPE = 332,
     tokSOMETYPE = 333,
     tokVARIANT = 334,
     tokSUCC = 335,
     tokWS1S = 336,
     tokWS2S = 337,
     tokTREEROOT = 338,
     tokCONSTTREE = 339,
     tokALLPOS = 340,
     tokINT = 341,
     tokNAME = 342,
     tokSTRING = 343,
     LOW = 344
   };
#endif
/* Tokens.  */
#define tokALL0 258
#define tokALL1 259
#define tokALL2 260
#define tokAND 261
#define tokARROW 262
#define tokASSERT 263
#define tokBIIMPL 264
#define tokCOLON 265
#define tokCOMMA 266
#define tokCONST 267
#define tokDEFAULT1 268
#define tokDEFAULT2 269
#define tokDOT 270
#define tokEMPTY 271
#define tokEQUAL 272
#define tokEX0 273
#define tokEX1 274
#define tokEX2 275
#define tokFALSE 276
#define tokGREATER 277
#define tokGREATEREQ 278
#define tokGUIDE 279
#define tokIMPL 280
#define tokIN 281
#define tokINTER 282
#define tokINTERVAL 283
#define tokLBRACE 284
#define tokLBRACKET 285
#define tokLESS 286
#define tokLESSEQ 287
#define tokLET0 288
#define tokLET1 289
#define tokLET2 290
#define tokLPAREN 291
#define tokMACRO 292
#define tokMAX 293
#define tokMIN 294
#define tokMINUS 295
#define tokMODULO 296
#define tokNOT 297
#define tokNOTEQUAL 298
#define tokNOTIN 299
#define tokOR 300
#define tokPLUS 301
#define tokPRED 302
#define tokRBRACE 303
#define tokRESTRICT 304
#define tokRBRACKET 305
#define tokUNIVROOT 306
#define tokRPAREN 307
#define tokSEMICOLON 308
#define tokSETMINUS 309
#define tokSLASH 310
#define tokSTAR 311
#define tokVERIFY 312
#define tokSUB 313
#define tokTREE 314
#define tokTRUE 315
#define tokUNION 316
#define tokUNIVERSE 317
#define tokUP 318
#define tokVAR0 319
#define tokVAR1 320
#define tokVAR2 321
#define tokWHERE 322
#define tokINCLUDE 323
#define tokIMPORT 324
#define tokEXPORT 325
#define tokPREFIX 326
#define tokM2LSTR 327
#define tokM2LTREE 328
#define tokLASTPOS 329
#define tokINSTATESPACE 330
#define tokEXECUTE 331
#define tokTYPE 332
#define tokSOMETYPE 333
#define tokVARIANT 334
#define tokSUCC 335
#define tokWS1S 336
#define tokWS2S 337
#define tokTREEROOT 338
#define tokCONSTTREE 339
#define tokALLPOS 340
#define tokINT 341
#define tokNAME 342
#define tokSTRING 343
#define LOW 344




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 51 "parser.ypp"
{ 
  char *string;
  int integer;
  MonaUntypedAST *monaUntypedAST;
  DeclarationList *declarationList;
  Declaration *declaration;
  UntypedExp *untypedExp;
  ArithExp *arithExp;
  ParDeclList *parDeclList;
  BindExpList *bindExpList;
  BindExp *bindExp;
  UntypedExpList *untypedExpList;
  NameList *nameList;
  Name *name;
  VarDeclList *varDeclList;
  GuideFuncList *guideFuncList;
  GuideFunc *guideFunc;
  UnivList *univList;
  Univ *univ;
  ImportMapList *mapList;
  VariantList *variantList;
  ComponentList *componentList;
  ConstNode *constNode;
  ConstNodeList *constNodeList;
}
/* Line 1489 of yacc.c.  */
#line 253 "parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
