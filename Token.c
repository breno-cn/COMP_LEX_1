//
// Created by breno on 2/1/22.
//

#include <stdlib.h>

#include "Token.h"

Token *Token_new(TokenType tokenType) {
    Token *token = malloc(sizeof(Token));

    if (token) {
        token->tokenType = tokenType;
    }

    return token;
}

void Token_delete(Token *token) {
    if (!token)
        return;

    free(token);
}

char *Token_toString(Token *token) {
    switch (token->tokenType) {
        case SingleLineComment:
            return "SINGLE_LINE_COMMENT";

        case MultiLineComment:
            return "MULTI_LINE_COMMENT";
    }
}
