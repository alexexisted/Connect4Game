//
// Created by Alexa G on 11/20/24.
//

#include "utils_logic.h"

#include <stdio.h>

#include "game_logic.h"

// Check if the board is full
bool isBoardFull() {
    for (int col = 0; col < FIELD_WIDTH; col++) {
        if (gameField[0][col] == ' ') {
            return false;
        }
    }
    return true;
}

// Place the user's move in the specified column
bool placeUsersMove(int column, char usersMove) {
    for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
        if (gameField[i][column] == ' ') {
            gameField[i][column] = usersMove;
            return true;
        }
    }
    printf("Column %d is full! Choose another column.\n", column + 1);
    return false;
}

// Input and validation for player names
void getPlayerNames() {
    printf("Enter the name of Player 1 (X): ");
    scanf("%19s", globalPlayer1);

    printf("Enter the name of Player 2 (O): ");
    scanf("%19s", globalPlayer2);
}