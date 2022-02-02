//
// Created by breno on 2/1/22.
//

#include "State.h"

int State_isFinalState(State state) {
    return state == AcceptSingleLineComment || state == AcceptMultiLineComment;
}
