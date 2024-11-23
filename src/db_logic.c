//
// Created by Alexa G on 11/20/24.
//

#include "db_logic.h"

#include <stdio.h>
#include <string.h>

#include "game_logic.h"
#include "game_state.h"
#define FILENAME "result.txt"

int getNextUniqueID() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) return 1; // If file doesn't exist, start from ID 1

    int maxID = 0, currentID;
    char line[256]; // Buffer to hold each line of the file

    while (fgets(line, sizeof(line), file)) {
        // Check if the line contains "Game ID" and extract the ID
        if (sscanf(line, "Game ID: %d,", &currentID) == 1) {
            if (currentID > maxID) {
                maxID = currentID;
            }
        }
    }

    fclose(file);
    return maxID + 1;
}

void loadSavedGame(GameState *state) {
    printf("Enter game ID: ");
    int id;
    scanf("%d", &id);

    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("No saved games found.\n");
        return;
    }

    char line[100];
    bool gameFound = false;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Game ID:")) {
            int currentID;
            sscanf(line, "Game ID: %d, Player 1: %s, Player 2: %s", &currentID, state->globalPlayer1, state->globalPlayer2);
            if (currentID == id) {
                gameFound = true;

                // Read the board and populate gameField
                for (int i = 0; i < FIELD_HEIGHT; i++) {
                    if (fgets(line, sizeof(line), file)) {
                        for (int j = 0; j < FIELD_WIDTH; j++) {
                            state->gameField[i][j] = line[j];  // Copy characters into gameField
                        }
                    }
                }

                printf("Game loaded successfully!\n");
                printf("Player 1: %s, Player 2: %s\n", state->globalPlayer1, state->globalPlayer2);
                displayField(state);  // Show the loaded game board

                state->isResumingSavedGame = true;  // Set the flag to prevent reinitialization
                startGameLoop(state);  // Start the game from the loaded state
                break;
            }
        }
    }

    if (!gameFound) {
        printf("Game with ID %d not found.\n", id);
    }

    fclose(file);
}

// Save the current game state to a file
void saveGame(GameState *state) {
    state->gameID = getNextUniqueID(); // Get the next unique ID

    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        printf("Error saving game.\n");
        return;
    }

    fprintf(file, "Game ID: %d, Player 1: %s, Player 2: %s\n", state->gameID, state->globalPlayer1, state->globalPlayer2);
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            fprintf(file, "%c", state->gameField[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    printf("Game saved with ID: %d\n", state->gameID);
    fclose(file);
}

void listAllSavedGames() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("No saved games found.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Game ID:")) {
            int freeCells = 0;
            int currentID;
            char player1[MAX_NAME_LENGTH], player2[MAX_NAME_LENGTH];

            // Parse the current line for ID and player names
            sscanf(line, "Game ID: %d, Player 1: %s, Player 2: %s", &currentID, player1, player2);

            // Count free cells in the following lines (the board)
            for (int i = 0; i < FIELD_HEIGHT; i++) {
                if (fgets(line, sizeof(line), file)) {
                    for (int j = 0; j < FIELD_WIDTH; j++) {
                        if (line[j] == ' ') {
                            freeCells++;
                        }
                    }
                }
            }

            // Print the game details
            printf("ID: %d, Player 1: %s, Player 2: %s, Free cells: %d\n", currentID, player1, player2, freeCells);
        }
    }

    fclose(file);
}

void initializeGameID(GameState *state) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        state->gameID = 1;  // No saved file, start from ID 1
        return;
    }

    int maxID = 0, currentID;
    char line[100];

    // Read all lines to find the maximum ID
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Game ID:")) {
            sscanf(line, "Game ID: %d,", &currentID);
            if (currentID > maxID) {
                maxID = currentID;
            }
        }
    }

    fclose(file);
    state->gameID = maxID + 1;  // Set gameID to the next available ID
}

void showSavedGameBoard() {
    printf("Enter game ID: ");
    int id;
    scanf("%d", &id);

    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("No saved games found.\n");
        return;
    }

    char line[100];
    bool gameFound = false;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Game ID:")) {
            int currentID;
            sscanf(line, "Game ID: %d,", &currentID);
            if (currentID == id) {
                gameFound = true;
                printf("%s", line); // Print game metadata
                for (int i = 0; i < FIELD_HEIGHT; i++) {
                    if (fgets(line, sizeof(line), file)) {
                        printf("%s", line); // Print the board row
                    }
                }
                break;
            }
        }
    }

    if (!gameFound) {
        printf("Game with ID %d not found.\n", id);
    }

    fclose(file);
}

void listGamesByPlayer() {
    printf("Enter player name: ");
    char playerName[MAX_NAME_LENGTH];
    scanf("%s", playerName);

    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("No saved games found.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, playerName)) {
            printf("%s", line); // Print matching games
        }
    }

    fclose(file);
}