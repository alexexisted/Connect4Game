#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define FIELD_WIDTH 7
#define FIELD_HEIGHT 6
#define WINNING_COUNT 4

char globalPlayer1[20];
char globalPlayer2[20];
char gameField[FIELD_HEIGHT][FIELD_WIDTH];
int gameID = 1;

void initializeField() {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            gameField[i][j] = ' ';
        }
    }
}

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

void playerTurn(char *playerName, char usersMove) {
    int column;
    bool validMove = false;

    while (!validMove) {
        printf("%s, your turn. Enter a column (1-%d) or 0 to save: ", playerName, FIELD_WIDTH);
        scanf("%d", &column);
        if (column >= 1 && column <= FIELD_WIDTH) {

        } else {
            printf("Invalid column. Please choose a column between 1 and %d.\n", FIELD_WIDTH);
        }
    }
}

bool isNameValid(const char *name) {
    const size_t nameLen = strlen(name);
    return nameLen > 0 && name[0] != '\n';
}

void startGameLoop() {
    initializeField();
    displayField();

    while (true) {
        // Main game loop
        playerTurn(globalPlayer1, 'X'); // Player 1's turn
        displayField();

        playerTurn(globalPlayer2, 'O'); // Player 2's turn
        displayField();
    }
}

void getPlayer2() {
    printf("Enter the name of the Player2\n");
    scanf("%19s", globalPlayer2);
    bool isValid = isNameValid(globalPlayer2);
    if (isValid) {
        startGameLoop();
    } else {
        printf("Incorrect name, try again\n");
        getPlayer2();
    }
}

void getPlayer1() {
    printf("Enter the name of the Player1\n");
    scanf("%19s", globalPlayer1);
    bool isValid = isNameValid(globalPlayer1);
    switch (isValid) {
        case true:
            getPlayer2();
            break;

        default:
            printf("Incorrect name, try again\n");
            getPlayer1();
    }
}

int mainMenu() {
    printf("1 - Play new game\n2 - Load saved game\n3 - Exit the game\n");
    int mainOption;
    scanf("%1d", &mainOption);

    switch (mainOption) {
        case 0:
            printf("Enter valid value 1-3\n");
            mainMenu();
            break;
        case 1:
            getPlayer1();
            break;
        case 2:
            printf("TODO saved games menu");
            break;
        case 3:
            printf("See you again!");
            return EXIT_SUCCESS;
        default:
            printf("Some error occurred");
            break;
    }

    return 0;
}

int main(void) {
    mainMenu();
    return 0;
}
