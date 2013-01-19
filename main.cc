#include <sstream>
#include <cassert>
#include <cstdlib>
#include "scanner.h"
#include "parser.c"

int main() {
    TTOKEN token;
    Scanner scanner(&std::cin);
    void *pParser = ParseAlloc(malloc);
    int tokenID;

#if 0
    ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

    ParserState state;
    // scanner.scan return 0 when get EOF.
    while (tokenID = scanner.scan(token)) {
        // printf("GET TOKEN: %d\n", tokenID);
        Parse(pParser, tokenID, token, &state);
    }
    Parse(pParser, 0, token, &state);
    ParseFree(pParser, free);

    printf("RESULT: %d\n", state.result);
    printf("RESULT: %s\n", state.str);
    return 0;
}

