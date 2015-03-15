/*	$Id: parser.y,v 1.4 1997/11/23 12:52:22 sandro Exp $	*/

/*
 * Copyright (c) 1997 Sandro Sigala <ssigala@globalnet.it>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * ISO C parser.
 *
 * Based on the ISO C 9899:1990 international standard.
 */

%{
#include <stdio.h>

extern int lineno;

static void yyerror(const char *s);
%}

%token IDENTIFIER TYPEDEF_NAME INTEGER FLOATING CHARACTER STRING

%token ELLIPSIS ADDEQ SUBEQ MULEQ DIVEQ MODEQ XOREQ ANDEQ OREQ SL SR
%token SLEQ SREQ EQ NOTEQ LTEQ GTEQ ANDAND OROR PLUSPLUS MINUSMINUS ARROW

%token AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE ENUM
%token EXTERN FLOAT FOR GOTO IF INT LONG REGISTER RETURN SHORT SIGNED SIZEOF
%token STATIC STRUCT SWITCH TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE

%start translation_unit

%%

/* B.2.1 Expressions. */

primary_expression:
	identifier
	| INTEGER
	| CHARACTER
	| FLOATING
	| STRING
	| '(' expression ')'
	;

identifier:
	IDENTIFIER
	;

postfix_expression:
	primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '(' ')'
	| postfix_expression '.' identifier
	| postfix_expression ARROW identifier
	| postfix_expression PLUSPLUS
	| postfix_expression MINUSMINUS
	;

argument_expression_list:
	assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression:
	postfix_expression
	| PLUSPLUS unary_expression
	| MINUSMINUS unary_expression
	| unary_operator cast_expression
	| SIZEOF unary_expression
	| SIZEOF '(' type_name ')'
	;

unary_operator:
	'&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression:
	unary_expression
	| '(' type_name ')' cast_expression
	;

multiplicative_expression:
	cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression:
	multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression:
	additive_expression
	| shift_expression SL additive_expression
	| shift_expression SR additive_expression
	;

relational_expression:
	shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LTEQ shift_expression
	| relational_expression GTEQ shift_expression
	;

equality_expression:
	relational_expression
	| equality_expression EQ relational_expression
	| equality_expression NOTEQ relational_expression
	;

and_expression:
	equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression:
	and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression:
	exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression:
	inclusive_or_expression
	| logical_and_expression ANDAND inclusive_or_expression
	;

logical_or_expression:
	logical_and_expression
	| logical_or_expression OROR logical_and_expression
	;

conditional_expression:
	logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression:
	conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator:
	'='
	| MULEQ
	| DIVEQ
	| MODEQ
	| ADDEQ
	| SUBEQ
	| SLEQ
	| SREQ
	| ANDEQ
	| XOREQ
	| OREQ
	;

expression:
	assignment_expression
	| expression ',' assignment_expression
	;

constant_expression:
	conditional_expression
	;

declaration:
	declaration_specifiers init_declarator_list ';'
	| declaration_specifiers ';'
	;

declaration_specifiers:
	storage_class_specifier declaration_specifiers
	| storage_class_specifier
	| type_specifier declaration_specifiers
	| type_specifier
	| type_qualifier declaration_specifiers
	| type_qualifier
	;

init_declarator_list:
	init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator:
	declarator
	| declarator '=' initializer
	;

storage_class_specifier:
	TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier:
	VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| struct_or_union_specifier
	| enum_specifier
	| TYPEDEF_NAME
	;

struct_or_union_specifier:
	struct_or_union identifier '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union identifier
	;

struct_or_union:
	STRUCT
	| UNION
	;

struct_declaration_list:
	struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration:
	specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list:
	type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list:
	struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator:
	declarator
	|  ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier:
	ENUM identifier '{' enumerator_list '}'
	| ENUM '{' enumerator_list '}'
	| ENUM identifier
	;

enumerator_list:
	enumerator
	| enumerator_list ',' enumerator
	;

enumerator:
	identifier
	| identifier '=' constant_expression
	;

type_qualifier:
	CONST
	| VOLATILE
	;

declarator:
	pointer direct_declarator
	| direct_declarator
	;

direct_declarator:
	identifier
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
	;

pointer:
	'*' type_qualifier_list
	| '*'
	| '*' type_qualifier_list pointer
	| '*' pointer
	;

type_qualifier_list:
	type_qualifier
	| type_qualifier_list type_qualifier
	;

parameter_type_list:
	parameter_list
	| parameter_list ',' ELLIPSIS
	;

parameter_list:
	parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration:
	declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list:
	identifier
	| identifier_list ',' identifier
	;

type_name:
	specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator:
	pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator:
	'(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer:
	assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list:
	initializer
	| initializer_list ',' initializer
	;

/* B.2.3 Statements. */

statement:
	labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement:
	identifier ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement:
	'{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

declaration_list:
	declaration
	| declaration_list declaration
	;

statement_list:
	statement
	| statement_list statement
	;

expression_statement:
	';'
	| expression ';'
	;

selection_statement:
	IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
	;

iteration_statement:
	WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' ';' ';' ')' statement
	| FOR '(' expression ';' ';' ')' statement
	| FOR '(' ';' expression ';' ')' statement
	| FOR '(' expression ';' expression ';' ')' statement
	| FOR '(' ';' ';' expression ')' statement
	| FOR '(' expression ';' ';' expression ')' statement
	| FOR '(' ';' expression ';' expression ')' statement
	| FOR '(' expression ';' expression ';' expression ')' statement
	;

jump_statement:
	GOTO identifier ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

/* B.2.4 External definitions. */

translation_unit:
	external_declaration
	| translation_unit external_declaration
	;

external_declaration:
	function_definition
	| declaration
	;

function_definition:
	declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

%%

static void
yyerror(const char *s)
{
	fprintf(stderr, "%d: %s\n", lineno, s);
}

int
main(void)
{
	lineno = 1;
	yyparse();

	return 0;
}
