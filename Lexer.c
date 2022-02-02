//
// Created by breno on 2/1/22.
//

#include "Lexer.h"
#include "State.h"
#include "Token.h"

#define LEXEM_SIZE 1024

Lexer *Lexer_new(FILE *input) {
    Lexer *lexer = malloc(sizeof(Lexer));

    if (lexer) {
        lexer->input = input;
        lexer->line = 1;
        lexer->col = 1;
        lexer->bufferIndex = 0;
        lexer->currentState = Initial;

        for (int i = 0; i < BUFFER_SIZE; i++) {
            lexer->buffer[i] = 0;
        }

        fread(lexer->buffer, sizeof(char), BUFFER_SIZE, lexer->input);
    }

    return lexer;
}

void Lexer_delete(Lexer *lexer) {
    if (!lexer)
        return;

    fclose(lexer->input);
    free(lexer);
}

char Lexer_readNextChar(Lexer *lexer) {
    char currentChar = lexer->buffer[lexer->bufferIndex];
    lexer->bufferIndex++;

    if (currentChar == '\n') {
        lexer->line++;
        lexer->col = 1;
    } else {
        lexer->col++;
    }

    return currentChar;
}

Token *Lexer_getNextToken(Lexer *lexer) {
    char currentLexem[LEXEM_SIZE];
    int currentLexemIndex = 0;

    lexer->currentState = Initial;
    Lexer_readWhitespace(lexer);
    char next;
    while (!State_isFinalState(lexer->currentState)) {
        switch (lexer->currentState) {
            case Initial:
                if (Lexer_peek(lexer) != '/') {
                    // TODO: tratamento de erro
                }
                lexer->currentState = ReadFirstSlash;
                break;

            case ReadFirstSlash:
//                next = Lexer_peek(lexer);
                if (!Lexer_readSlash(lexer)) {
                    // TODO: tratamento de erro
                }

                lexer->currentState = ReadNextCommentChar;
                break;

            case ReadNextCommentChar:
                next = Lexer_peek(lexer);
                if (next == '/') {
                    Lexer_readSlash(lexer);
                    lexer->currentState = ReadSingleLine;
                } else if (next == '*') {
                    Lexer_readStar(lexer);
                    lexer->currentState = ReadUntilNextStar;
                } else {
                    // TODO: tratamento de erro
                }

                break;

            case ReadSingleLine:
                while (Lexer_peek(lexer) != '\n')
                    Lexer_readNextChar(lexer);

                Lexer_readLineBreak(lexer);
                lexer->currentState = AcceptSingleLineComment;

                break;

            case ReadUntilNextStar:
                while (Lexer_peek(lexer) != '*')
                    Lexer_readNextChar(lexer);

                lexer->currentState = ReadSecondStar;
                break;

            case ReadSecondStar:
                if (!Lexer_readStar(lexer)) {
                    // TODO: tratamento de erro
                }

                lexer->currentState = ReadSecondSlashMultiLine;
                break;

            case ReadSecondSlashMultiLine:
                if (!Lexer_readSlash(lexer)) {
                    // TODO: tratamento de erro
                }

                lexer->currentState = AcceptMultiLineComment;
                break;
        }
    }

    State currentState = lexer->currentState;
    switch (currentState) {
        case AcceptSingleLineComment:
            return Token_new(SingleLineComment);

        case AcceptMultiLineComment:
            return Token_new(MultiLineComment);
    }

    return NULL;
}

char Lexer_peek(Lexer *lexer) {
    return lexer->buffer[lexer->bufferIndex];
}

char Lexer_peekNext(Lexer *lexer) {
    return lexer->buffer[lexer->bufferIndex + 1];
}

int Lexer_readSlash(Lexer *lexer) {
    return Lexer_readNextChar(lexer) == '/';
}

int Lexer_readStar(Lexer *lexer) {
    return Lexer_readNextChar(lexer) == '*';
}

int Lexer_readLineBreak(Lexer *lexer) {
    return Lexer_readNextChar(lexer) == '\n';
}

int Lexer_isWhitespaceNext(Lexer *lexer) {
    char currentChar = lexer->buffer[lexer->bufferIndex];

    return currentChar == ' ' || currentChar == '\t' || currentChar == '\n';
}

void Lexer_readWhitespace(Lexer *lexer) {
    while (Lexer_isWhitespaceNext(lexer))
        Lexer_readNextChar(lexer);
}
