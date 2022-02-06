//
// Created by breno on 2/1/22.
//

#ifndef COMP_LEX_1_LEXER_H
#define COMP_LEX_1_LEXER_H

#include <stdio.h>
#include <stdlib.h>

#include "State.h"
#include "Token.h"

#define BUFFER_SIZE 1024

typedef struct {
    FILE *input;
    int line;
    int col;
    int bufferIndex;
    State currentState;
    char buffer[BUFFER_SIZE];
} Lexer;

Lexer *Lexer_new(FILE *input);
void Lexer_delete(Lexer *lexer);
char Lexer_readNextChar(Lexer *lexer);
Token *Lexer_getNextToken(Lexer *lexer);

char Lexer_peek(Lexer *lexer);
char Lexer_peekNext(Lexer *lexer);
// Tenta ler um caractere '/', retorna 1 em caso de sucesso, 0 em caso de falha
int Lexer_readSlash(Lexer *lexer);
int Lexer_readStar(Lexer *lexer);
int Lexer_readLineBreak(Lexer *lexer);
int Lexer_isWhitespaceNext(Lexer *lexer);
void Lexer_readWhitespace(Lexer *lexer);

void Lexer_raiseError(Lexer *lexer, char *error);

#endif //COMP_LEX_1_LEXER_H
