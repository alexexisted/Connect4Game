//
// Created by Alexa G on 11/20/24.
//

#ifndef GAME_STATE_H
#define GAME_STATE_H

#define MAX_NAME_LENGTH 20
#define FIELD_WIDTH 7
#define FIELD_HEIGHT 6
#define WINNING_COUNT 4

typedef struct {
    char gameField[FIELD_HEIGHT][FIELD_WIDTH];
    char globalPlayer1[MAX_NAME_LENGTH];
    char globalPlayer2[MAX_NAME_LENGTH];
    bool isResumingSavedGame;

} GameState;

#endif
