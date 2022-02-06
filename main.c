#include <stdio.h>

#include "Lexer.h"

int main() {
    printf("Hello, World!\n");

    FILE *input = fopen("input.txt", "r");
    Lexer *lexer = Lexer_new(input);

    Token *token;

    do {
        token = Lexer_getNextToken(lexer);
        printf("Token: %s\n", Token_toString(token));
    } while (token->tokenType != EofToken);

//    for (int i = 0; i < 6; i++) {
//        token = Lexer_getNextToken(lexer);
//        printf("Token: %s\n", Token_toString(token));
//        Token_delete(token);
//    }

    Lexer_delete(lexer);

    return 0;
}
