#include <stdio.h>

#include "Lexer.h"

int main() {
    printf("Hello, World!\n");

    FILE *input = fopen("input.txt", "r");
    Lexer *lexer = Lexer_new(input);

    Token *token;

    while (1) {
        token = Lexer_getNextToken(lexer);
        printf("Token: %s\n", Token_toString(token));

        if (token->tokenType == EofToken)
            break;
    }

    Lexer_delete(lexer);

    return 0;
}
