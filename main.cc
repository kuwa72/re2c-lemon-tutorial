#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include <string>
#include "scanner.h"
#include "parser.c"

int main() {
    TTOKEN token;
    int tokenID;
    char line[2048];
    ParserState state;
    void *pParser;

#if 0
    ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

    while(1) {
        std::cin >> line;
        std::string ls(line);
        Scanner scanner(ls);
        // scanner.scan return 0 when get EOF.
        //
        pParser = ParseAlloc(malloc);
        while (tokenID = scanner.scan(&token)) {
            // printf("GET TOKEN: %d\n", tokenID);
            Parse(pParser, tokenID, token, &state);
        }
        Parse(pParser, 0, token, &state);
        ParseFree(pParser, free);

        printf("RESULT: %d\n", state.result);
        printf("RESULT: %s\n", state.str);
    }
    return 0;
}

