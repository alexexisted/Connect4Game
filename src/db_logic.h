//
// Created by Alexa G on 11/20/24.
//

#ifndef DB_LOGIC_H
#define DB_LOGIC_H

#define MAX_NAME_LENGTH 20
#define FIELD_WIDTH 7
#define FIELD_HEIGHT 6
#define WINNING_COUNT 4

void initializeGameID();
void saveGame();
void listAllSavedGames();
void loadSavedGame();
void showSavedGameBoard();
void listGamesByPlayer();

#endif //DB_LOGIC_H
