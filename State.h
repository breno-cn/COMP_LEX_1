//
// Created by breno on 2/1/22.
//

#ifndef COMP_LEX_1_STATE_H
#define COMP_LEX_1_STATE_H

typedef enum {
    Initial, ReadFirstSlash, ReadNextCommentChar, ReadSingleLine, ReadUntilNextStar,
    ReadSecondStar, ReadSecondSlashMultiLine, AcceptSingleLineComment, AcceptMultiLineComment
} State;

int State_isFinalState(State state);

#endif //COMP_LEX_1_STATE_H
