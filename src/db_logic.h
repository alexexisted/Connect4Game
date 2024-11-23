//
// Created by Alexa G on 11/20/24.
//

#ifndef DB_LOGIC_H
#define DB_LOGIC_H

#include "game_state.h"

void initializeGameID(GameState *state);
void saveGame(GameState *state);
void listAllSavedGames();
void loadSavedGame(GameState *state);
int getNextUniqueID();
void showSavedGameBoard();
void listGamesByPlayer();
void startGameLoop(GameState *state);

#endif
