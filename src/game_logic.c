//
// Created by Alexa G on 11/20/24.
//
#include "game_logic.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Global variables specific to game logic
char gameField[FIELD_HEIGHT][FIELD_WIDTH];
char globalPlayer1[MAX_NAME_LENGTH];
char globalPlayer2[MAX_NAME_LENGTH];

// Initialize the field with empty spaces
void initializeField() {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            gameField[i][j] = ' ';
        }
    }
}

// Display the game board
void displayField() {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            printf("| %c ", gameField[i][j]);
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

// Check if a direction from (row, col) has WINNING_COUNT in a row and mark it if true
bool checkAndHighlightDirection(int row, int col, int rowDir, int colDir, char piece) {
    int count = 0;
    int winningPositions[WINNING_COUNT][2]; // Array to store winning positions

    // Traverse in the specified direction
    for (int i = 0; i < WINNING_COUNT; i++) {
        int newRow = row + i * rowDir;
        int newCol = col + i * colDir;

        // Check if we're within bounds and the piece matches
        if (newRow >= 0 && newRow < FIELD_HEIGHT && newCol >= 0 && newCol < FIELD_WIDTH && gameField[newRow][newCol] ==
            piece) {
            winningPositions[count][0] = newRow;
            winningPositions[count][1] = newCol;
            count++;
        } else {
            break;
        }
    }

    // If we have a winning combination, highlight the positions
    if (count == WINNING_COUNT) {
        for (int i = 0; i < WINNING_COUNT; i++) {
            gameField[winningPositions[i][0]][winningPositions[i][1]] = 'Y'; // Highlight with 'Y'
        }
        return true;
    }

    return false;
}

// Check if a player has won and highlight the winning combination if they have
bool checkWinAndHighlight(char piece) {
    for (int row = 0; row < FIELD_HEIGHT; row++) {
        for (int col = 0; col < FIELD_WIDTH; col++) {
            if (gameField[row][col] == piece) {
                if (checkAndHighlightDirection(row, col, 0, 1, piece) || // Horizontal
                    checkAndHighlightDirection(row, col, 1, 0, piece) || // Vertical
                    checkAndHighlightDirection(row, col, 1, 1, piece) || // Diagonal down-right
                    checkAndHighlightDirection(row, col, 1, -1, piece)) {
                    // Diagonal down-left
                    return true;
                }
            }
        }
    }
    return false;
}

// Handle the player's turn
void playerTurn(char *playerName, char usersMove) {
    int column;
    bool validMove = false;

    while (!validMove) {
        printf("%s, your turn. Enter a column (1-%d) or 0 to save: ", playerName, FIELD_WIDTH);
        scanf("%d", &column);

        if (column == 0) {
            saveGame();
            return; // Return to continue game after saving
        }

        if (column >= 1 && column <= FIELD_WIDTH) {
            validMove = placeUsersMove(column - 1, usersMove);
            if (validMove) {
                if (checkWinAndHighlight(usersMove)) {
                    displayField();
                    printf("%s wins!\n", playerName);
                    promptForNewGame();; // End the game if there's a winner
                }
                if (isBoardFull()) {
                    displayField();
                    printf("The board is full! It's a tie.\n");
                    promptForNewGame();
                }
            }
        } else {
            printf("Invalid column. Please choose a column between 1 and %d.\n", FIELD_WIDTH);
        }
    }
}
