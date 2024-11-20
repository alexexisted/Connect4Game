#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db_logic.h"
#include "game_logic.h"
#include "navigation_logic.h"

// #define MAX_NAME_LENGTH 20
// #define FIELD_WIDTH 7
// #define FIELD_HEIGHT 6
// #define WINNING_COUNT 4
// #define FILENAME "result.txt"
//
// char globalPlayer1[MAX_NAME_LENGTH];
// char globalPlayer2[MAX_NAME_LENGTH];
// char gameField[FIELD_HEIGHT][FIELD_WIDTH];
// int gameID; // Unique ID for each saved game
// bool isResumingSavedGame = false;  // Indicates whether a saved game is being resumed

//TODO check input type to avoid inf. cycle

int main(void) {
    initializeGameID();
    mainMenu();
    return 0;
}
