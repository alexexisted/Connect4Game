//
// Created by Alexa G on 11/20/24.
//

#include "utils_logic.h"

int getNextUniqueID() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) return 1; // If file doesn't exist, start from ID 1

    int maxID = 0, currentID;
    while (fscanf(file, "Game ID: %d,", &currentID) == 1) {
        if (currentID > maxID) {
            maxID = currentID;
        }
        // Skip the rest of the line
        char buffer[100];
        fgets(buffer, sizeof(buffer), file);
    }

    fclose(file);
    return maxID + 1;
}

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

// Main game loop to handle turns
void startGameLoop() {
    if (!isResumingSavedGame) {  // Initialize only for new games
        initializeField();
    }
    isResumingSavedGame = false;  // Reset flag after the first use

    displayField();

    while (true) {
        playerTurn(globalPlayer1, 'X');  // Player 1's turn
        displayField();

        playerTurn(globalPlayer2, 'O');  // Player 2's turn
        displayField();
    }
}

// Input and validation for player names
void getPlayerNames() {
    printf("Enter the name of Player 1 (X): ");
    scanf("%19s", globalPlayer1);

    printf("Enter the name of Player 2 (O): ");
    scanf("%19s", globalPlayer2);
}