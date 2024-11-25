//
// Created by Alexa G on 11/20/24.
//

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "game_state.h"

// Function declarations
void initializeField(GameState *state);
void startGameLoop(GameState *state);
void displayField(GameState *state);
bool checkWinAndHighlight(char move, GameState *state);
bool checkAndHighlightDirection(int row, int col, int rowDir, int colDir, char move, GameState *state);
void playerTurn(char *playerName, char usersMove, GameState *state);

#endif
