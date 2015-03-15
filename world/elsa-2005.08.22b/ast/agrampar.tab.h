#ifndef BISON_AGRAMPAR_TAB_H
# define BISON_AGRAMPAR_TAB_H

#ifndef YYSTYPE
typedef union YYSTYPE {
  ASTSpecFile *file;
  ASTList<ToplevelForm> *formList;
  TF_class *tfClass;
  ASTList<CtorArg> *ctorArgList;
  ASTList<Annotation> *userDeclList;
  string *str;
  enum AccessCtl accessCtl;
  AccessMod *accessMod;
  ToplevelForm *verbatim;
  Annotation *annotation;
  TF_option *tfOption;
  ASTList<string> *stringList;
  TF_enum *tfEnum;
  ASTList<string> *enumeratorList;
  string *enumerator;
  ASTList<BaseClass> *baseClassList;
  BaseClass *baseClass;
  CustomCode *customCode;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	TOK_NAME	257
# define	TOK_INTLIT	258
# define	TOK_EMBEDDED_CODE	259
# define	TOK_LBRACE	260
# define	TOK_RBRACE	261
# define	TOK_SEMICOLON	262
# define	TOK_ARROW	263
# define	TOK_LPAREN	264
# define	TOK_RPAREN	265
# define	TOK_LANGLE	266
# define	TOK_RANGLE	267
# define	TOK_STAR	268
# define	TOK_AMPERSAND	269
# define	TOK_COMMA	270
# define	TOK_EQUALS	271
# define	TOK_COLON	272
# define	TOK_CLASS	273
# define	TOK_PUBLIC	274
# define	TOK_PRIVATE	275
# define	TOK_PROTECTED	276
# define	TOK_VERBATIM	277
# define	TOK_IMPL_VERBATIM	278
# define	TOK_CTOR	279
# define	TOK_DTOR	280
# define	TOK_PURE_VIRTUAL	281
# define	TOK_CUSTOM	282
# define	TOK_OPTION	283
# define	TOK_NEW	284
# define	TOK_ENUM	285


#endif /* not BISON_AGRAMPAR_TAB_H */
