//
// Created by Alexa G on 11/20/24.
//

#ifndef UTILS_LOGIC_H
#define UTILS_LOGIC_H
#include "game_state.h"

void clearInputBuffer();
bool isBoardFull(GameState *state);
bool placeUsersMove(int column, char usersMove, GameState *state);
void getPlayerNames(GameState *state);

#endif //UTILS_LOGIC_H
