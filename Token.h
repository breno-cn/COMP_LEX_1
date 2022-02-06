//
// Created by breno on 2/1/22.
//

#ifndef COMP_LEX_1_TOKEN_H
#define COMP_LEX_1_TOKEN_H

typedef enum {
    SingleLineComment, MultiLineComment, EofToken
} TokenType;

typedef struct {
    TokenType tokenType;
} Token;

Token *Token_new(TokenType tokenType);
void Token_delete(Token *token);
char *Token_toString(Token *token);

#endif //COMP_LEX_1_TOKEN_H
