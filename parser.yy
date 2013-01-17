%token_prefix TOKEN_

%left INCLUDE INLUCDE_ONCE EVAL REQUIRE REQUIRE_ONCE.
%left COLUMN.
%left LOGICAL_OR.
%left LOGICAL_XOR.
%left LOGICAL_AND.
%right PRINT ECHO.
%right YIELD.
%left EQ PLUS_EQUAL MINUS_EQUAL MUL_EQUAL DIV_EQUAL CONCAT_EQUAL MOD_EQUAL AND_EQUAL OR_EQUAL XOR_EQUAL SL_EQUAL SR_EQUAL.
%left QUESTION COLON.
%left BOOLEAN_OR.
%left BOOLEAN_AND.
%left PIPE.
%left HAT.
%left AND.
%nonassoc IS_EQUAL IS_NOT_EQUAL IS_IDENTICAL IS_NOT_IDENTICAL.
%nonassoc IS_SMALLER IS_SMALLER_OR_EQUAL IS_GREATER IS_GREATER_EQUAL.
%left SL SR.
%left ADD SUB DOT.
%left MUL DIV MOD.
%right BANG.
%nonassoc INSTANCEOF.
%right TILD INC DEC INT_CAST DOUBLE_CAST STRING_CAST ARRAY_CAST OBJECT_CAST BOOL_CAST UNSET_CAST AT.
%right BRACKET_A DQ SQ ID VAR.
%nonassoc NEW CLONE.
%left ELSEIF.
%left ELSE.
%left ENDIF.
%right STATIC ABSTRACT FINAL PRIVATE PROTECTED PUBLIC.
%right COMMENT_IN COMMENT_OUT.
%token_type { YYSTYPE }

%extra_argument { ParserState *state }

%include {
#include <iostream>
#include "scanner.def.h"
}

%syntax_error {
    fprintf(stderr, "Syntax error\n");
}

%parse_failure {
    fprintf(stderr,"Giving up.  Parser is hopelessly lost...\n");
}

%start_symbol program

program ::= expr(A). {
    state->result = A.int_value;
}

expr(A) ::= primary_expression(B). {
    A.int_value = B.int_value;
}
expr(A) ::= expr(B) SUB primary_expression(C). {
    A.int_value = B.int_value - C.int_value;
}
expr(A) ::= expr(B) ADD primary_expression(C). {
    A.int_value = B.int_value + C.int_value;
}
expr(A) ::= expr(B) DIV primary_expression(C). {
    A.int_value = B.int_value / C.int_value;
}
expr(A) ::= expr(B) MUL primary_expression(C). {
    A.int_value = B.int_value * C.int_value;
}

primary_expression(A) ::= INT(B). {
    A.int_value = B.int_value;
}

