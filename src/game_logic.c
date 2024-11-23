//
// Created by Alexa G on 11/20/24.
//
#include "game_logic.h"
#include <stdio.h>

#include "db_logic.h"
#include "game_state.h"
#include "navigation_logic.h"
#include "utils_logic.h"

//init the field with empty spaces
void initializeField(GameState *state) {
    //matrix 6X7
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            state->gameField[i][j] = ' ';
        }
    }
}

//display the game board
void displayField(GameState *state) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            printf("| %c ", state->gameField[i][j]);
        }
        printf("|\n");
    }
    for (int j = 0; j < FIELD_WIDTH; j++) {
        printf("----");
    }
    printf("-\n");
    for (int j = 0; j < FIELD_WIDTH; j++) {
        printf("  %d ", j + 1);
    }
    printf("\n");
}

//check if some player has won and highlight the winning combination if they have
bool checkWinAndHighlight(const char move, GameState *state) {
    //iterate through entire field
    for (int row = 0; row < FIELD_HEIGHT; row++) {
        for (int col = 0; col < FIELD_WIDTH; col++) {
            if (state->gameField[row][col] == move) { //If the cell matches the player's symbol
                                                    //we're starting to check winning combination from this cell
                if (checkAndHighlightDirection(row, col, 0, 1, move, state) || //horizontal
                    checkAndHighlightDirection(row, col, 1, 0, move, state) || //vertical
                    checkAndHighlightDirection(row, col, 1, 1, move, state) || //diagonal down-right
                    checkAndHighlightDirection(row, col, 1, -1, move, state))  //diagonal down-left
                {
                    return true;
                }
            }
        }
    }
    return false;
}

//check if a direction from has WINNING_COUNT in a row and mark it if true
bool checkAndHighlightDirection(int row, int col, int rowDir, int colDir, char move, GameState *state) {
    //counter
    int count = 0;
    //array to store winning positions
    int winningPositions[WINNING_COUNT][2];

    //go in the specified direction
    for (int i = 0; i < WINNING_COUNT; i++) {
        //calculate the next cell coordinates using the direction vector(rowDir, colDir)
        int newRow = row + i * rowDir;
        int newCol = col + i * colDir;

        //check if the new cell is within bounds and matches the player's symbol
        if (newRow >= 0 && newRow < FIELD_HEIGHT && newCol >= 0 && newCol < FIELD_WIDTH &&
            state->gameField[newRow][newCol] == move) {
            winningPositions[count][0] = newRow;
            winningPositions[count][1] = newCol;
            count++;
            //if it does, record its coordinates in winningPositions and increment count
        } else {
            break;
        }
    }

    //if we have a winning combination, highlight the positions
    if (count == WINNING_COUNT) {
        for (int i = 0; i < WINNING_COUNT; i++) {
            state->gameField[winningPositions[i][0]][winningPositions[i][1]] = 'Y';
        }
        return true;
    }

    return false;
}

//handle the player's turn
void playerTurn(char *playerName, const char usersMove, GameState *state) {
    int column;
    bool validMove = false;

    while (!validMove) {
        printf("%s, your turn. Enter a column (1-%d) or 0 to save: ", playerName, FIELD_WIDTH);
        scanf("%d", &column);

        //if user decide to save the game
        if (column == 0) {
            saveGame(state);
            //return to continue game after saving
            return;
        }
        //if valid move
        if (column >= 1 && column <= FIELD_WIDTH) {
            validMove = placeUsersMove(column - 1, usersMove, state);
            if (validMove) {
                //if placeUsersMove returns true we check if there are any winning combination
                if (checkWinAndHighlight(usersMove, state)) {
                    displayField(state);
                    printf("%s wins!\n", playerName);
                    promptForNewGame(state);; // End the game if there's a winner
                }
                if (isBoardFull(state)) {
                    displayField(state);
                    printf("The board is full! It's a tie.\n");
                    promptForNewGame(state);
                }
            }
        } else {
            printf("Invalid column. Please choose a column between 1 and %d.\n", FIELD_WIDTH);
        }
    }
}

//main game loop
void startGameLoop(GameState *state) {
    //initialize only for new games, not for resumed from db
    if (!state->isResumingSavedGame) {
        initializeField(state);
    }
    //reset flag after the use
    state->isResumingSavedGame = false;

    //display the field
    displayField(state);

    while (true) {
        //game process
        playerTurn(state->globalPlayer1, 'X', state);
        displayField(state);

        playerTurn(state->globalPlayer2, 'O', state);
        displayField(state);
    }
}
