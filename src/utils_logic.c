//
// Created by Alexa G on 11/20/24.
//

#include "utils_logic.h"

#include <stdio.h>
#include <string.h>

#include "game_state.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Check if the board is full
bool isBoardFull(GameState *state) {
    for (int col = 0; col < FIELD_WIDTH; col++) {
        if (state->gameField[0][col] == ' ') {
            return false;
        }
    }
    return true;
}

// Place the user's move in the specified column
bool placeUsersMove(int column, char usersMove, GameState *state) {
    for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
        if (state->gameField[i][column] == ' ') {
            state->gameField[i][column] = usersMove;
            return true;
        }
    }
    printf("Column %d is full! Choose another column.\n", column + 1);
    return false;
}

// Input and validation for player names
void getPlayerNames(GameState *state) {
    clearInputBuffer(); // Clear any leftover input

    printf("Enter the name of Player 1 (X): ");
    fgets(state->globalPlayer1, MAX_NAME_LENGTH, stdin);
    state->globalPlayer1[strcspn(state->globalPlayer1, "\n")] = '\0'; // Remove newline

    printf("Enter the name of Player 2 (O): ");
    fgets(state->globalPlayer2, MAX_NAME_LENGTH, stdin);
    state->globalPlayer2[strcspn(state->globalPlayer2, "\n")] = '\0'; // Remove newline
}
