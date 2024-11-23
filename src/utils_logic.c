//
// Created by Alexa G on 11/20/24.
//

#include "utils_logic.h"

#include <stdio.h>
#include <string.h>

#include "game_state.h"

//clear buffer if user entered new lines etc
void clearInputBuffer() {
    int c;
    //while c is not a new line and not an end of the file
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
void getPlayerNames(GameState *state) {
    //clear buffer to let username be in two words
    clearInputBuffer();

    printf("Enter the name of Player 1 (X): ");
    //read a full line from user
    fgets(state->globalPlayer1, MAX_NAME_LENGTH, stdin);
    //remove new line
    state->globalPlayer1[strcspn(state->globalPlayer1, "\n")] = '\0';

    //same for another one
    printf("Enter the name of Player 2 (O): ");
    fgets(state->globalPlayer2, MAX_NAME_LENGTH, stdin);
    state->globalPlayer2[strcspn(state->globalPlayer2, "\n")] = '\0';
}

//place user's move on a board
bool placeUsersMove(const int column, const char usersMove, GameState *state) {
    //run through field and check if column is available
    for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
        if (state->gameField[i][column] == ' ') { //if yes then put x or o there
            state->gameField[i][column] = usersMove;
            return true;
        }
    } //if not then let user know about it
    printf("Column %d is full! Choose another column.\n", column + 1);
    return false;
}