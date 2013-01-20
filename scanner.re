#ifndef CALC_SCANNER_H_
#define CALC_SCANNER_H_

#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include "scanner.def.h"
#include "parser.h"

class Scanner {
private:
    char line[4096];
    char *l_pos;
    // buffer memory
    char* m_buffer;
    // current position
    char* m_cursor;
    char* m_limit;
    char* m_token;
    char* m_marker;
    char* m_top;
    char* m_end;
    int m_buffer_size;
    int m_lineno;
 
public:

    void increment_line_number() {
        m_lineno++;
    }

    Scanner( std::string s, int init_size=1024 )
        : m_buffer(0)
        , m_cursor(0)
        , m_limit(0)
        , m_token(0)
        , m_marker(0)
        , m_buffer_size(init_size)
        , m_lineno(1)
        , m_top(0)
        , m_end(0)
    {
        m_buffer = new char[m_buffer_size];
        m_cursor = m_limit = m_token = m_marker = m_buffer;
        strcpy(m_buffer, s.c_str());
        strcpy(line, s.c_str());
        l_pos = line;
    }
 
    ~Scanner() {
        delete [] m_buffer;
    }
 
    bool fill(int n) {
        if (!m_end){
            int cnt = m_token-m_buffer;
            if (cnt) {
                memmove(m_buffer, m_token, m_limit - m_token);
                m_token = m_buffer;
                m_marker -= cnt;
                m_cursor -= cnt;
                m_limit  -= cnt;
            }
            if((m_top - m_limit) < m_buffer_size){
                char *buf = (char*) malloc(((m_limit - m_buffer) + m_buffer_size)*sizeof(char));
                memmove(buf, m_token, m_limit - m_token);
                m_token = buf;
                m_marker = &buf[m_marker - m_buffer];
                m_cursor = &buf[m_cursor - m_buffer];
                m_limit = &buf[m_limit - m_buffer];
                m_top = &m_limit[m_buffer_size];
                free(m_buffer);
                m_buffer = buf;
            }

            
            cnt = strlen(l_pos)+1;
            memmove(m_limit, l_pos, cnt);
            l_pos += cnt;
            if(cnt != m_buffer_size){
                m_end = &m_limit[cnt];
                *(m_end)++ = '\n';
            }
            m_limit += cnt;

            return true;
        }
	return false;
    }
 
    std::string text() {
        return std::string( m_token, m_token+length() );
    }
    int length() {
        return (m_cursor-m_token);
    }
    int lineno() {
        return m_lineno;
    }
 
    int scan(TTOKEN* tok) {
std:
        m_token = m_cursor;
 
    /*!re2c
        re2c:define:YYCTYPE = "char";
        re2c:define:YYCURSOR = m_cursor;
        re2c:define:YYMARKER = m_marker;
        re2c:define:YYLIMIT = m_limit;
        re2c:define:YYFILL:naked = 1;
        re2c:define:YYFILL@len = #;
        re2c:define:YYFILL = "if (!fill(#)) { return 0; }";
        re2c:indent:top = 2;
        re2c:indent:string="    ";

        O = [0-7];
        D = [0-9];
        L = [a-zA-Z_];
        H = [a-fA-F0-9];
        E = [Ee] [+-]? D+;
        FS = [fFlL];
        IS = [uUlL]*;
        INTEGER                = [1-9][0-9]*;
        WS                     = [ \r\n\t\f];
        ANY_CHARACTER     = [\000-\377];
	S_ESC	= [\\] (['\\]);
        ESC     = [\\] ([efnrtv$"\\] | "x" H+ | O+);


        (['] (S_ESC|ANY_CHARACTER\[\n\\"])*? [']) {
	    tok->str = (char*)this->text().c_str();
            return TOKEN_STR;
        }
        (["] (ESC|ANY_CHARACTER\[\n\\"])*? ["]) {
	    tok->str = (char*)this->text().c_str();
            return TOKEN_STR;
        }
	INTEGER {
            tok->int_value = atoi(this->text().c_str());
            return TOKEN_INT;
        }
        "+" { return TOKEN_ADD; }
        "-" { return TOKEN_SUB; }
        "*" { return TOKEN_MUL; }
        "/" { return TOKEN_DIV; }
        WS {
            goto std;
        }
        ANY_CHARACTER {
            printf("unexpected character: '%c(%d)'\n", *m_token, *m_token);
            goto std;
        }

    */

    }
};

#endif // CALC_SCANNER_H_
