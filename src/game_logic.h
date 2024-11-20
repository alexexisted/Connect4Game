//
// Created by Alexa G on 11/20/24.
//

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define MAX_NAME_LENGTH 20
#define FIELD_WIDTH 7
#define FIELD_HEIGHT 6
#define WINNING_COUNT 4

// Function declarations
void initializeField();
void displayField();
bool checkWinAndHighlight(char piece);
bool checkAndHighlightDirection(int row, int col, int rowDir, int colDir, char piece);
void playerTurn(char *playerName, char usersMove);

#endif
