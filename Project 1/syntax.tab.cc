// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 1 "syntax.y"

#include<stdio.h>
#include "lex.yy.c"
#include <iostream>
#include <string>
#include "Node.hpp"
extern int yyparse();
extern FILE* yyin;
Node* root = nullptr;
void yyerror(const std::string& s);

#line 53 "syntax.tab.cc"


#include "syntax.tab.hh"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 131 "syntax.tab.cc"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}


  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_kind.
  parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // Program: ExtDefList
#line 41 "syntax.y"
                     {  (yylhs.value.node) = Node::makeNode(NodeType::Program, {(yystack_[0].value.node)});root = (yylhs.value.node);}
#line 587 "syntax.tab.cc"
    break;

  case 3: // ExtDefList: %empty
#line 43 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::ExtDefList);}
#line 593 "syntax.tab.cc"
    break;

  case 4: // ExtDefList: ExtDef ExtDefList
#line 44 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::ExtDefList,{(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 599 "syntax.tab.cc"
    break;

  case 5: // ExtDef: Specifier ExtDecList SEMI
#line 47 "syntax.y"
                                    { (yylhs.value.node) = Node::makeNode(NodeType::ExtDef,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)});}
#line 605 "syntax.tab.cc"
    break;

  case 6: // ExtDef: Specifier SEMI
#line 48 "syntax.y"
                                    { (yylhs.value.node) = Node::makeNode(NodeType::ExtDef,{(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 611 "syntax.tab.cc"
    break;

  case 7: // ExtDef: Specifier FunDec CompSt
#line 49 "syntax.y"
                                    { (yylhs.value.node) = Node::makeNode(NodeType::ExtDef,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 617 "syntax.tab.cc"
    break;

  case 8: // ExtDef: Specifier ExtDecList error
#line 50 "syntax.y"
                                    { (yylhs.value.node) = Node::makeNode(NodeType::ExtDef); yyerror("Type B,Missing semicolon \';\'") ;}
#line 623 "syntax.tab.cc"
    break;

  case 9: // ExtDef: Specifier error
#line 51 "syntax.y"
                                    { (yylhs.value.node) = Node::makeNode(NodeType::ExtDef);   yyerror("Type B,Missing semicolon \';\'"); }
#line 629 "syntax.tab.cc"
    break;

  case 10: // ExtDef: ExtDecList SEMI
#line 52 "syntax.y"
                              { (yylhs.value.node) = Node::makeNode(NodeType::ExtDef);  yyerror("Type B,Missing specifier \';\'"); }
#line 635 "syntax.tab.cc"
    break;

  case 11: // ExtDecList: VarDec
#line 55 "syntax.y"
                                { (yylhs.value.node) = Node::makeNode(NodeType::ExtDecList,{(yystack_[0].value.node)}); }
#line 641 "syntax.tab.cc"
    break;

  case 12: // ExtDecList: VarDec COMMA ExtDecList
#line 56 "syntax.y"
                                { (yylhs.value.node) = Node::makeNode(NodeType::ExtDecList,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 647 "syntax.tab.cc"
    break;

  case 13: // Specifier: TYPE
#line 60 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Specifier,{(yystack_[0].value.node)}); }
#line 653 "syntax.tab.cc"
    break;

  case 14: // Specifier: StructSpecifier
#line 61 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Specifier,{(yystack_[0].value.node)}); }
#line 659 "syntax.tab.cc"
    break;

  case 15: // StructSpecifier: STRUCT ID LC DefList RC
#line 64 "syntax.y"
                                            { (yylhs.value.node) = Node::makeNode(NodeType::StructSpecifier,{(yystack_[4].value.node),(yystack_[3].value.node),(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 665 "syntax.tab.cc"
    break;

  case 16: // StructSpecifier: STRUCT ID
#line 65 "syntax.y"
                                            { (yylhs.value.node) = Node::makeNode(NodeType::StructSpecifier,{(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 671 "syntax.tab.cc"
    break;

  case 17: // StructSpecifier: STRUCT ID LC DefList error
#line 66 "syntax.y"
                                            { (yylhs.value.node) = Node::makeNode(NodeType::StructSpecifier);  yyerror("Type B,Missing closing curly braces \'}\'") ;}
#line 677 "syntax.tab.cc"
    break;

  case 18: // StructSpecifier: STRUCT ID DefList RC
#line 67 "syntax.y"
                                            { (yylhs.value.node) = Node::makeNode(NodeType::StructSpecifier);   yyerror("Type B,Missing closing curly braces \'{\'") ; }
#line 683 "syntax.tab.cc"
    break;

  case 19: // VarDec: ID
#line 71 "syntax.y"
                            { (yylhs.value.node) = Node::makeNode(NodeType::VarDec,{(yystack_[0].value.node)}); }
#line 689 "syntax.tab.cc"
    break;

  case 20: // VarDec: VarDec LB INTEGER RB
#line 72 "syntax.y"
                               { (yylhs.value.node) = Node::makeNode(NodeType::VarDec,{(yystack_[3].value.node),(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 695 "syntax.tab.cc"
    break;

  case 21: // VarDec: VarDec LB INTEGER error
#line 73 "syntax.y"
                               { (yylhs.value.node) = Node::makeNode(NodeType::VarDec); yyerror("Type B,Missing closing braces \']\'");}
#line 701 "syntax.tab.cc"
    break;

  case 22: // VarDec: VarDec INTEGER RB
#line 74 "syntax.y"
                               { (yylhs.value.node) = Node::makeNode(NodeType::VarDec);  yyerror("Type B,Missing closing braces \']\'");}
#line 707 "syntax.tab.cc"
    break;

  case 23: // VarDec: INVALID
#line 75 "syntax.y"
                            { (yylhs.value.node) = Node::makeNode(NodeType::VarDec);  }
#line 713 "syntax.tab.cc"
    break;

  case 24: // FunDec: ID LP VarList RP
#line 78 "syntax.y"
                            { (yylhs.value.node) = Node::makeNode(NodeType::FunDec,{(yystack_[3].value.node),(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)});}
#line 719 "syntax.tab.cc"
    break;

  case 25: // FunDec: ID LP RP
#line 79 "syntax.y"
                            { (yylhs.value.node) = Node::makeNode(NodeType::FunDec,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 725 "syntax.tab.cc"
    break;

  case 26: // FunDec: ID LP VarList error
#line 80 "syntax.y"
                            { (yylhs.value.node) = Node::makeNode(NodeType::FunDec); yyerror("Type B,Missing closing parenthesis \')\'") ;}
#line 731 "syntax.tab.cc"
    break;

  case 27: // FunDec: ID RP
#line 81 "syntax.y"
                            { (yylhs.value.node) = Node::makeNode(NodeType::FunDec); yyerror("Type B,Missing closing parenthesis \'(\'") ;}
#line 737 "syntax.tab.cc"
    break;

  case 28: // FunDec: ID LP error
#line 82 "syntax.y"
                            { (yylhs.value.node) = Node::makeNode(NodeType::FunDec); yyerror("Type B,Missing closing parenthesis \')\'"); }
#line 743 "syntax.tab.cc"
    break;

  case 29: // FunDec: INVALID LP VarList RP
#line 83 "syntax.y"
                              { (yylhs.value.node) = Node::makeNode(NodeType::FunDec);  }
#line 749 "syntax.tab.cc"
    break;

  case 30: // FunDec: INVALID LP RP
#line 84 "syntax.y"
                                { (yylhs.value.node) = Node::makeNode(NodeType::FunDec);  }
#line 755 "syntax.tab.cc"
    break;

  case 31: // FunDec: INVALID LP VarList error
#line 85 "syntax.y"
                                 { (yylhs.value.node) = Node::makeNode(NodeType::FunDec);  }
#line 761 "syntax.tab.cc"
    break;

  case 32: // FunDec: INVALID RP
#line 86 "syntax.y"
                                 { (yylhs.value.node) = Node::makeNode(NodeType::FunDec);  }
#line 767 "syntax.tab.cc"
    break;

  case 33: // FunDec: INVALID LP error
#line 87 "syntax.y"
                                 { (yylhs.value.node) = Node::makeNode(NodeType::FunDec);  }
#line 773 "syntax.tab.cc"
    break;

  case 34: // VarList: ParamDec COMMA VarList
#line 90 "syntax.y"
                                    { (yylhs.value.node) = Node::makeNode(NodeType::VarList,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 779 "syntax.tab.cc"
    break;

  case 35: // VarList: ParamDec
#line 91 "syntax.y"
                                    { (yylhs.value.node) = Node::makeNode(NodeType::VarList,{(yystack_[0].value.node)}); }
#line 785 "syntax.tab.cc"
    break;

  case 36: // ParamDec: Specifier VarDec
#line 94 "syntax.y"
                            { (yylhs.value.node) = Node::makeNode(NodeType::ParamDec,{(yystack_[1].value.node),(yystack_[0].value.node)});  }
#line 791 "syntax.tab.cc"
    break;

  case 37: // CompSt: LC DefList StmtList RC
#line 98 "syntax.y"
                                { (yylhs.value.node) = Node::makeNode(NodeType::CompSt,{(yystack_[3].value.node),(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 797 "syntax.tab.cc"
    break;

  case 38: // CompSt: LC DefList StmtList error
#line 99 "syntax.y"
                                { (yylhs.value.node) = Node::makeNode(NodeType::CompSt); yyerror("Type B,Missing closing curly bracket \'}\'") ;}
#line 803 "syntax.tab.cc"
    break;

  case 39: // StmtList: %empty
#line 103 "syntax.y"
                                { (yylhs.value.node) = Node::makeNode(NodeType::StmtList);  }
#line 809 "syntax.tab.cc"
    break;

  case 40: // StmtList: Stmt StmtList
#line 104 "syntax.y"
                                { (yylhs.value.node) = Node::makeNode(NodeType::StmtList,{(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 815 "syntax.tab.cc"
    break;

  case 41: // StmtList: Stmt Def DefList StmtList
#line 105 "syntax.y"
                                { (yylhs.value.node) = Node::makeNode(NodeType::StmtList); yyerror("Type B,Missing specifier") ;}
#line 821 "syntax.tab.cc"
    break;

  case 42: // Stmt: SEMI
#line 108 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt,{(yystack_[0].value.node)}); }
#line 827 "syntax.tab.cc"
    break;

  case 43: // Stmt: Exp SEMI
#line 109 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt,{(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 833 "syntax.tab.cc"
    break;

  case 44: // Stmt: CompSt
#line 110 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt,{(yystack_[0].value.node)});}
#line 839 "syntax.tab.cc"
    break;

  case 45: // Stmt: RETURN Exp SEMI
#line 111 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)});}
#line 845 "syntax.tab.cc"
    break;

  case 46: // Stmt: IF LP Exp RP Stmt
#line 112 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt,{(yystack_[4].value.node),(yystack_[3].value.node),(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 851 "syntax.tab.cc"
    break;

  case 47: // Stmt: IF LP Exp RP Stmt ELSE Stmt
#line 113 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt,{(yystack_[6].value.node),(yystack_[5].value.node),(yystack_[4].value.node),(yystack_[3].value.node),(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)});  }
#line 857 "syntax.tab.cc"
    break;

  case 48: // Stmt: WHILE LP Exp RP Stmt
#line 114 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt,{(yystack_[4].value.node),(yystack_[3].value.node),(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)});}
#line 863 "syntax.tab.cc"
    break;

  case 49: // Stmt: Exp error
#line 115 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt); yyerror("Type B,Missing semicolon \';\'") ;}
#line 869 "syntax.tab.cc"
    break;

  case 50: // Stmt: RETURN Exp error
#line 116 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing semicolon \';\'") ; }
#line 875 "syntax.tab.cc"
    break;

  case 51: // Stmt: IF LP RP
#line 117 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing condition \';\'") ; }
#line 881 "syntax.tab.cc"
    break;

  case 52: // Stmt: IF LP RP ELSE
#line 118 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing condition \';\'") ; }
#line 887 "syntax.tab.cc"
    break;

  case 53: // Stmt: IF LP Exp RP error
#line 119 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expect Stmt after if") ; }
#line 893 "syntax.tab.cc"
    break;

  case 54: // Stmt: IF LP Exp RP error ELSE Stmt
#line 120 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expect Stmt after if") ;  }
#line 899 "syntax.tab.cc"
    break;

  case 55: // Stmt: IF error Exp RP Stmt
#line 121 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expected \'(\' after \'if\'") ; }
#line 905 "syntax.tab.cc"
    break;

  case 56: // Stmt: IF error Exp RP Stmt ELSE Stmt
#line 122 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expected \'(\' after \'if\'") ; }
#line 911 "syntax.tab.cc"
    break;

  case 57: // Stmt: IF LP Exp error Stmt
#line 123 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing closing parenthesis \')\'") ; }
#line 917 "syntax.tab.cc"
    break;

  case 58: // Stmt: IF LP Exp error Stmt ELSE Stmt
#line 124 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing closing parenthesis \')\'") ;  }
#line 923 "syntax.tab.cc"
    break;

  case 59: // Stmt: WHILE error Exp RP Stmt
#line 125 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Expected \'(\' after \'while\'") ; }
#line 929 "syntax.tab.cc"
    break;

  case 60: // Stmt: WHILE LP Exp error Stmt
#line 126 "syntax.y"
                                                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt);  yyerror("Type B,Missing closing parenthesis \')\'") ; }
#line 935 "syntax.tab.cc"
    break;

  case 61: // Stmt: ELSE Stmt
#line 127 "syntax.y"
                { (yylhs.value.node) = Node::makeNode(NodeType::Stmt); yyerror("Type B,Expected \'if\' before \'else\'"); }
#line 941 "syntax.tab.cc"
    break;

  case 62: // DefList: %empty
#line 131 "syntax.y"
                    { (yylhs.value.node) = Node::makeNode(NodeType::DefList); }
#line 947 "syntax.tab.cc"
    break;

  case 63: // DefList: Def DefList
#line 132 "syntax.y"
                    { (yylhs.value.node) = Node::makeNode(NodeType::DefList,{(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 953 "syntax.tab.cc"
    break;

  case 64: // Def: Specifier DecList SEMI
#line 135 "syntax.y"
                                { (yylhs.value.node) = Node::makeNode(NodeType::Def,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)});  }
#line 959 "syntax.tab.cc"
    break;

  case 65: // Def: Specifier DecList error
#line 136 "syntax.y"
                                { (yylhs.value.node) = Node::makeNode(NodeType::Def,{(yystack_[2].value.node),(yystack_[1].value.node)}); yyerror("Type B,Missing semicolon \';\'");}
#line 965 "syntax.tab.cc"
    break;

  case 66: // DecList: Dec
#line 139 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::DecList,{(yystack_[0].value.node)}); }
#line 971 "syntax.tab.cc"
    break;

  case 67: // DecList: Dec COMMA DecList
#line 140 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::DecList,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 977 "syntax.tab.cc"
    break;

  case 68: // Dec: VarDec
#line 143 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Dec,{(yystack_[0].value.node)});}
#line 983 "syntax.tab.cc"
    break;

  case 69: // Dec: VarDec ASSIGN Exp
#line 144 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Dec,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 989 "syntax.tab.cc"
    break;

  case 70: // Exp: Exp ASSIGN Exp
#line 148 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 995 "syntax.tab.cc"
    break;

  case 71: // Exp: Exp AND Exp
#line 149 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1001 "syntax.tab.cc"
    break;

  case 72: // Exp: Exp OR Exp
#line 150 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)});}
#line 1007 "syntax.tab.cc"
    break;

  case 73: // Exp: Exp LT Exp
#line 151 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1013 "syntax.tab.cc"
    break;

  case 74: // Exp: Exp LE Exp
#line 152 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1019 "syntax.tab.cc"
    break;

  case 75: // Exp: Exp GT Exp
#line 153 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1025 "syntax.tab.cc"
    break;

  case 76: // Exp: Exp GE Exp
#line 154 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1031 "syntax.tab.cc"
    break;

  case 77: // Exp: Exp NE Exp
#line 155 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1037 "syntax.tab.cc"
    break;

  case 78: // Exp: Exp EQ Exp
#line 156 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1043 "syntax.tab.cc"
    break;

  case 79: // Exp: Exp PLUS Exp
#line 157 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1049 "syntax.tab.cc"
    break;

  case 80: // Exp: Exp MINUS Exp
#line 158 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)});}
#line 1055 "syntax.tab.cc"
    break;

  case 81: // Exp: Exp MUL Exp
#line 159 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)});}
#line 1061 "syntax.tab.cc"
    break;

  case 82: // Exp: Exp DIV Exp
#line 160 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)});}
#line 1067 "syntax.tab.cc"
    break;

  case 83: // Exp: LP Exp RP
#line 161 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1073 "syntax.tab.cc"
    break;

  case 84: // Exp: PLUS Exp
#line 162 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[1].value.node),(yystack_[0].value.node)});}
#line 1079 "syntax.tab.cc"
    break;

  case 85: // Exp: MINUS Exp
#line 163 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1085 "syntax.tab.cc"
    break;

  case 86: // Exp: NOT Exp
#line 164 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1091 "syntax.tab.cc"
    break;

  case 87: // Exp: ID LP Args RP
#line 165 "syntax.y"
                        {  (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[3].value.node),(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1097 "syntax.tab.cc"
    break;

  case 88: // Exp: ID LP RP
#line 166 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1103 "syntax.tab.cc"
    break;

  case 89: // Exp: Exp LB Exp RB
#line 167 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[3].value.node),(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)});}
#line 1109 "syntax.tab.cc"
    break;

  case 90: // Exp: Exp DOT ID
#line 168 "syntax.y"
                        {(yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1115 "syntax.tab.cc"
    break;

  case 91: // Exp: Var
#line 169 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp,{(yystack_[0].value.node)}); }
#line 1121 "syntax.tab.cc"
    break;

  case 92: // Exp: Exp ASSIGN error
#line 170 "syntax.y"
                          { (yylhs.value.node) = Node::makeNode(NodeType::Exp); yyerror("Type B,Missing right operand");}
#line 1127 "syntax.tab.cc"
    break;

  case 93: // Exp: Exp AND error
#line 171 "syntax.y"
                          { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand"); }
#line 1133 "syntax.tab.cc"
    break;

  case 94: // Exp: Exp OR error
#line 172 "syntax.y"
                          { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand"); }
#line 1139 "syntax.tab.cc"
    break;

  case 95: // Exp: Exp LT error
#line 173 "syntax.y"
                          { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1145 "syntax.tab.cc"
    break;

  case 96: // Exp: Exp LE error
#line 174 "syntax.y"
                          { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1151 "syntax.tab.cc"
    break;

  case 97: // Exp: Exp GT error
#line 175 "syntax.y"
                          { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1157 "syntax.tab.cc"
    break;

  case 98: // Exp: Exp GE error
#line 176 "syntax.y"
                          { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1163 "syntax.tab.cc"
    break;

  case 99: // Exp: Exp NE error
#line 177 "syntax.y"
                          { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1169 "syntax.tab.cc"
    break;

  case 100: // Exp: Exp EQ error
#line 178 "syntax.y"
                          { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1175 "syntax.tab.cc"
    break;

  case 101: // Exp: Exp PLUS error
#line 179 "syntax.y"
                          { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1181 "syntax.tab.cc"
    break;

  case 102: // Exp: Exp MINUS error
#line 180 "syntax.y"
                          { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1187 "syntax.tab.cc"
    break;

  case 103: // Exp: Exp MUL error
#line 181 "syntax.y"
                          { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1193 "syntax.tab.cc"
    break;

  case 104: // Exp: Exp DIV error
#line 182 "syntax.y"
                          { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing right operand");}
#line 1199 "syntax.tab.cc"
    break;

  case 105: // Exp: Exp INVALID Exp
#line 184 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  }
#line 1205 "syntax.tab.cc"
    break;

  case 106: // Exp: LP Exp error
#line 186 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Missing closing parenthesis \')\'") ; }
#line 1211 "syntax.tab.cc"
    break;

  case 107: // Exp: ID LP Args error
#line 190 "syntax.y"
                        {(yylhs.value.node) = Node::makeNode(NodeType::Exp);   yyerror("Missing closing parenthesis \')\'") ; }
#line 1217 "syntax.tab.cc"
    break;

  case 108: // Exp: ID LP error
#line 192 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp);   yyerror("Missing closing parenthesis \')\'") ; }
#line 1223 "syntax.tab.cc"
    break;

  case 109: // Exp: Exp LB Exp error
#line 194 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Exp);  yyerror("Type B,Missing closing braces \']\'") ; }
#line 1229 "syntax.tab.cc"
    break;

  case 110: // Args: Exp COMMA Args
#line 197 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Args,{(yystack_[2].value.node),(yystack_[1].value.node),(yystack_[0].value.node)}); }
#line 1235 "syntax.tab.cc"
    break;

  case 111: // Args: Exp
#line 198 "syntax.y"
                        { (yylhs.value.node) = Node::makeNode(NodeType::Args,{(yystack_[0].value.node)}); }
#line 1241 "syntax.tab.cc"
    break;

  case 112: // Var: INTEGER
#line 201 "syntax.y"
                       { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1247 "syntax.tab.cc"
    break;

  case 113: // Var: ID
#line 212 "syntax.y"
                    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1253 "syntax.tab.cc"
    break;

  case 114: // Var: FLOAT
#line 223 "syntax.y"
                    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1259 "syntax.tab.cc"
    break;

  case 115: // Var: CHAR
#line 234 "syntax.y"
                    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1265 "syntax.tab.cc"
    break;

  case 116: // Var: INVALID
#line 245 "syntax.y"
                    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1271 "syntax.tab.cc"
    break;


#line 1275 "syntax.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char parser::yypact_ninf_ = -72;

  const signed char parser::yytable_ninf_ = -63;

  const short
  parser::yypact_[] =
  {
      86,   -72,   -72,   -12,   -72,    29,   -72,    86,    32,    10,
     -72,    -7,   167,   -72,   -72,   -72,   -72,    63,   -72,   122,
      94,    35,    11,    67,    39,   165,    11,    45,   165,   123,
     -72,   129,   -72,   -72,   -72,   165,   -72,   -72,     2,   -72,
       6,    -6,   150,    72,   -72,   -72,   -72,   -72,    11,    43,
      96,   -72,   -72,    50,   440,   -72,   -72,   -72,   -72,   468,
     -72,   -72,    11,   -10,   -72,   -72,   165,   -72,   -72,   -72,
     105,   440,   112,   468,   -72,   468,   468,   468,   468,    84,
     -72,   -72,   -72,   -72,    31,   403,   526,   -72,   750,   -72,
     -72,   468,   457,   -72,   468,   468,   554,   181,   181,    56,
     582,    47,   -72,   -72,   -72,   165,   -72,   468,    93,   -72,
     120,   144,   161,   185,   202,   226,   243,   267,   284,   308,
     325,   349,   366,   468,   672,   130,   614,   698,   646,   -72,
     -72,   -72,   -72,   -72,   -72,   724,    66,   440,   767,   -72,
     -72,   767,   -72,   368,   -72,   368,   -72,   368,   -72,   368,
     -72,   368,   -72,   368,   -72,   181,   -72,   181,   -72,    56,
     -72,    56,   -72,   800,   -72,   784,   498,   440,   -72,   440,
     102,   440,   440,   440,   468,   -72,   -72,   -72,   -72,   -72,
     139,   141,   148,   154,   -72,   -72,   -72,   -72,   440,   440,
     440,   440,   -72,   -72,   -72,   -72
  };

  const signed char
  parser::yydefact_[] =
  {
       3,    23,    13,     0,    19,     0,     2,     3,     0,     0,
      14,    11,    16,     1,     4,    10,     9,    23,     6,    19,
       0,     0,     0,     0,     0,    62,     0,     0,    62,     0,
      32,     0,    27,     8,     5,    62,     7,    12,     0,    22,
       0,    68,     0,    66,    18,    63,    33,    30,     0,     0,
      35,    28,    25,     0,    39,    21,    20,    17,    15,     0,
      65,    64,     0,    36,    31,    29,     0,    26,    24,   116,
       0,     0,     0,     0,    42,     0,     0,     0,     0,   113,
     112,   114,   115,    44,     0,    39,     0,    91,    69,    67,
      34,     0,     0,    61,     0,     0,     0,    84,    85,    86,
       0,     0,    38,    37,    40,    62,    49,     0,     0,    43,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,    50,
      45,   106,    83,   108,    88,   111,     0,    39,   105,    90,
      92,    70,    95,    73,    96,    74,    97,    75,    98,    76,
      99,    77,   100,    78,   101,    79,   102,    80,   103,    81,
     104,    82,    93,    71,    94,    72,     0,     0,    52,     0,
       0,     0,     0,     0,     0,   107,    87,    41,   109,    89,
      55,    57,    53,    46,    59,    60,    48,   110,     0,     0,
       0,     0,    56,    58,    54,    47
  };

  const short
  parser::yypgoto_[] =
  {
     -72,   -72,   158,   -72,    70,     9,   -72,   -20,   -72,   -27,
     -72,   145,   -64,   -71,   -23,    90,   114,   -72,   -58,     3,
     -72
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     5,     6,     7,     8,    26,    10,    11,    21,    49,
      50,    83,    84,    85,    27,    28,    42,    43,    86,   136,
      87
  };

  const short
  parser::yytable_[] =
  {
      93,    88,    40,    55,    53,    45,    41,    57,    22,     9,
      59,    16,    54,    17,     1,    96,     9,    97,    98,    99,
     100,   104,    23,    18,    12,    23,    23,    24,    63,    13,
      24,    24,   102,   124,   126,    56,   127,   128,    48,    90,
      48,    58,    41,   135,    64,    15,    19,     4,   133,   138,
      69,    67,   141,   143,   145,   147,   149,   151,   153,   155,
     157,   159,   161,   163,   165,   166,   103,   175,   108,    35,
      75,    76,    39,   177,    65,    48,    77,    78,   134,    20,
      44,    68,   137,    79,    80,    81,    82,    62,   123,     1,
       2,     3,    37,    29,    30,    33,   180,   176,   181,   183,
     184,   185,   186,   182,    38,    69,    91,    34,    70,    71,
      72,    66,    73,    94,   101,    74,   135,   192,   193,   194,
     195,   140,     4,    69,    46,    75,    76,     2,     3,   139,
      51,    77,    78,     2,     3,    92,    35,   168,    79,    80,
      81,    82,    95,    75,    76,   142,   188,    69,   189,    77,
      78,    60,    31,    32,    47,   190,    79,    80,    81,    82,
      52,   191,   144,    61,    69,    14,    36,    75,    76,     2,
       3,     2,     3,    77,    78,   105,    89,   187,     0,     0,
      79,    80,    81,    82,    75,    76,   146,     0,    69,     0,
      77,    78,     0,   108,     0,     0,     0,    79,    80,    81,
      82,    25,   -62,   148,     0,    69,   119,   120,    75,    76,
       0,     0,     0,   123,    77,    78,     0,     0,     0,     0,
       0,    79,    80,    81,    82,    75,    76,   150,     0,    69,
       0,    77,    78,     0,     0,     0,     0,     0,    79,    80,
      81,    82,     0,     0,   152,     0,    69,     0,     0,    75,
      76,     0,     0,     0,     0,    77,    78,     0,     0,     0,
       0,     0,    79,    80,    81,    82,    75,    76,   154,     0,
      69,     0,    77,    78,     0,     0,     0,     0,     0,    79,
      80,    81,    82,     0,     0,   156,     0,    69,     0,     0,
      75,    76,     0,     0,     0,     0,    77,    78,     0,     0,
       0,     0,     0,    79,    80,    81,    82,    75,    76,   158,
       0,    69,     0,    77,    78,     0,     0,     0,     0,     0,
      79,    80,    81,    82,     0,     0,   160,     0,    69,     0,
       0,    75,    76,     0,     0,     0,     0,    77,    78,     0,
       0,     0,     0,     0,    79,    80,    81,    82,    75,    76,
     162,     0,    69,     0,    77,    78,     0,     0,     0,     0,
       0,    79,    80,    81,    82,     0,     0,   164,     0,    69,
       0,     0,    75,    76,     0,     0,     0,     0,    77,    78,
     108,     0,     0,     0,     0,    79,    80,    81,    82,    75,
      76,   117,   118,   119,   120,    77,    78,     0,     0,     0,
     123,     0,    79,    80,    81,    82,    69,     2,     3,    70,
      71,    72,     0,    73,     0,     0,    74,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    75,    76,     0,     0,
       0,     0,    77,    78,     0,     0,     0,    35,     0,    79,
      80,    81,    82,    69,     0,     0,    70,    71,    72,     0,
      73,     0,     0,    74,     0,     0,     0,     0,     0,     0,
      69,     0,     0,    75,    76,     0,     0,     0,     0,    77,
      78,    69,     0,     0,    35,     0,    79,    80,    81,    82,
      75,    76,     0,     0,     0,     0,    77,    78,   125,     0,
       0,    75,    76,    79,    80,    81,    82,    77,    78,   178,
       0,   107,     0,     0,    79,    80,    81,    82,     0,     0,
     108,     0,     0,     0,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   106,     0,   107,
     123,   179,     0,     0,     0,     0,     0,     0,   108,   109,
       0,     0,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   129,     0,   107,   123,     0,
       0,     0,     0,     0,     0,     0,   108,   130,     0,     0,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   131,     0,   107,   123,     0,     0,     0,
       0,     0,     0,     0,   108,     0,     0,     0,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,     0,     0,   132,   123,   169,     0,   107,     0,     0,
       0,     0,     0,     0,     0,     0,   108,     0,     0,     0,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,     0,     0,   170,   123,   172,     0,   107,
       0,     0,     0,     0,     0,     0,     0,     0,   108,     0,
       0,     0,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   107,     0,   173,   123,     0,
       0,     0,     0,     0,   108,     0,     0,     0,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   107,     0,   167,   123,     0,     0,     0,     0,     0,
     108,     0,     0,     0,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   107,     0,   171,
     123,     0,     0,     0,     0,     0,   108,     0,     0,   174,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   107,     0,     0,   123,     0,     0,     0,
       0,     0,   108,     0,     0,     0,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   108,
       0,     0,   123,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   108,     0,     0,   123,
       0,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   108,     0,     0,     0,   123,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,     0,     0,     0,
       0,     0,   123
  };

  const short
  parser::yycheck_[] =
  {
      71,    59,    25,     1,    31,    28,    26,     1,    15,     0,
      16,     1,    35,     3,     3,    73,     7,    75,    76,    77,
      78,    85,    32,    13,    36,    32,    32,    37,    48,     0,
      37,    37,     1,    91,    92,    33,    94,    95,    29,    66,
      31,    35,    62,   101,     1,    13,    36,    36,     1,   107,
       3,     1,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,    35,     1,    12,    34,
      23,    24,    33,   137,    31,    66,    29,    30,    31,     9,
      35,    31,   105,    36,    37,    38,    39,    15,    32,     3,
       4,     5,    22,    30,    31,     1,   167,    31,   169,   170,
     171,   172,   173,     1,    37,     3,     1,    13,     6,     7,
       8,    15,    10,     1,    30,    13,   174,   188,   189,   190,
     191,     1,    36,     3,     1,    23,    24,     4,     5,    36,
       1,    29,    30,     4,     5,    30,    34,     7,    36,    37,
      38,    39,    30,    23,    24,     1,     7,     3,     7,    29,
      30,     1,    30,    31,    31,     7,    36,    37,    38,    39,
      31,     7,     1,    13,     3,     7,    21,    23,    24,     4,
       5,     4,     5,    29,    30,    85,    62,   174,    -1,    -1,
      36,    37,    38,    39,    23,    24,     1,    -1,     3,    -1,
      29,    30,    -1,    12,    -1,    -1,    -1,    36,    37,    38,
      39,    34,    35,     1,    -1,     3,    25,    26,    23,    24,
      -1,    -1,    -1,    32,    29,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    23,    24,     1,    -1,     3,
      -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    -1,     1,    -1,     3,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    39,    23,    24,     1,    -1,
       3,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,
      37,    38,    39,    -1,    -1,     1,    -1,     3,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    23,    24,     1,
      -1,     3,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    -1,    -1,     1,    -1,     3,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    29,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    23,    24,
       1,    -1,     3,    -1,    29,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    -1,    -1,     1,    -1,     3,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    29,    30,
      12,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    23,
      24,    23,    24,    25,    26,    29,    30,    -1,    -1,    -1,
      32,    -1,    36,    37,    38,    39,     3,     4,     5,     6,
       7,     8,    -1,    10,    -1,    -1,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,
      -1,    -1,    29,    30,    -1,    -1,    -1,    34,    -1,    36,
      37,    38,    39,     3,    -1,    -1,     6,     7,     8,    -1,
      10,    -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    29,
      30,     3,    -1,    -1,    34,    -1,    36,    37,    38,    39,
      23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    -1,
      -1,    23,    24,    36,    37,    38,    39,    29,    30,     1,
      -1,     3,    -1,    -1,    36,    37,    38,    39,    -1,    -1,
      12,    -1,    -1,    -1,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     1,    -1,     3,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,
      -1,    -1,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,     1,    -1,     3,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    -1,    -1,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     1,    -1,     3,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    31,    32,     1,    -1,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    31,    32,     1,    -1,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,     3,    -1,    31,    32,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,     3,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     3,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     3,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    12,
      -1,    -1,    32,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    12,    -1,    -1,    32,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    12,    -1,    -1,    -1,    32,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    32
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     5,    36,    44,    45,    46,    47,    48,
      49,    50,    36,     0,    45,    13,     1,     3,    13,    36,
      47,    51,    15,    32,    37,    34,    48,    57,    58,    30,
      31,    30,    31,     1,    13,    34,    54,    47,    37,    33,
      57,    50,    59,    60,    35,    57,     1,    31,    48,    52,
      53,     1,    31,    52,    57,     1,    33,     1,    35,    16,
       1,    13,    15,    50,     1,    31,    15,     1,    31,     3,
       6,     7,     8,    10,    13,    23,    24,    29,    30,    36,
      37,    38,    39,    54,    55,    56,    61,    63,    61,    59,
      52,     1,    30,    56,     1,    30,    61,    61,    61,    61,
      61,    30,     1,    35,    55,    58,     1,     3,    12,    13,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    32,    61,    31,    61,    61,    61,     1,
      13,     1,    31,     1,    31,    61,    62,    57,    61,    36,
       1,    61,     1,    61,     1,    61,     1,    61,     1,    61,
       1,    61,     1,    61,     1,    61,     1,    61,     1,    61,
       1,    61,     1,    61,     1,    61,    61,    31,     7,     1,
      31,    31,     1,    31,    15,     1,    31,    55,     1,    33,
      56,    56,     1,    56,    56,    56,    56,    62,     7,     7,
       7,     7,    56,    56,    56,    56
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    43,    44,    45,    45,    46,    46,    46,    46,    46,
      46,    47,    47,    48,    48,    49,    49,    49,    49,    50,
      50,    50,    50,    50,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    52,    53,    54,    54,    55,
      55,    55,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    57,    57,    58,    58,    59,    59,    60,    60,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      62,    62,    63,    63,    63,    63,    63
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     3,     2,     3,     3,     2,
       2,     1,     3,     1,     1,     5,     2,     5,     4,     1,
       4,     4,     3,     1,     4,     3,     4,     2,     3,     4,
       3,     4,     2,     3,     3,     1,     2,     4,     4,     0,
       2,     4,     1,     2,     1,     3,     5,     7,     5,     2,
       3,     3,     4,     5,     7,     5,     7,     5,     7,     5,
       5,     2,     0,     2,     3,     3,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     4,     3,     4,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     3,     4,
       3,     1,     1,     1,     1,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "INVALID", "TYPE",
  "STRUCT", "IF", "ELSE", "WHILE", "FOR", "RETURN", "INCLUDE", "DOT",
  "SEMI", "COLON", "COMMA", "ASSIGN", "LT", "LE", "GT", "GE", "NE", "EQ",
  "PLUS", "MINUS", "MUL", "DIV", "AND", "OR", "NOT", "LP", "RP", "LB",
  "RB", "LC", "RC", "ID", "INTEGER", "FLOAT", "CHAR",
  "SINGLE_LINE_COMMENT", "MULTI_LINE_COMMENT", "LOWER_ELSE", "$accept",
  "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args",
  "Var", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,    41,    41,    43,    44,    47,    48,    49,    50,    51,
      52,    55,    56,    60,    61,    64,    65,    66,    67,    71,
      72,    73,    74,    75,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    90,    91,    94,    98,    99,   103,
     104,   105,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   131,   132,   135,   136,   139,   140,   143,   144,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   184,   186,   190,   192,   194,
     197,   198,   201,   212,   223,   234,   245
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::symbol_kind_type
  parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
    };
    // Last valid token kind.
    const int code_max = 297;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // yy
#line 1889 "syntax.tab.cc"

#line 250 "syntax.y"


void yyerror(const std::string& s) {
    
    std::cerr << "Error: " << s << std::endl;
}

//int main() {
//    yyin = stdin;
//    do {
//        yyparse();
//    } while (!feof(yyin));
//    return 0;
//}
