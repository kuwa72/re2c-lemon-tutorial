%token_prefix TOKEN_

%left ADD SUB.
%left DIV MOD.
%left STR. 

%token_type { TTOKEN } //this is token

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

program ::= STR(A). {
    state->str = A.str;
}

expr(A) ::= expr(B) SUB expr(C). {
    A.int_value = B.int_value - C.int_value;
}
expr(A) ::= expr(B) ADD expr(C). {
    A.int_value = B.int_value + C.int_value;
}
expr(A) ::= expr(B) DIV expr(C). {
    A.int_value = B.int_value / C.int_value;
}
expr(A) ::= expr(B) MUL expr(C). {
    A.int_value = B.int_value * C.int_value;
}

expr(A) ::= INT(B). {
    A.int_value = B.int_value;
}

