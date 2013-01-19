#ifndef CALC_SCANNER_DEF_H_
#define CALC_SCANNER_DEF_H_

typedef union {
    int int_value;
    char *str;
} TTOKEN;

struct ParserState {
    int result;
    char *str;
    ParserState() :result(0) {
    }
};

#endif // CALC_SCANNER_DEF_H_
