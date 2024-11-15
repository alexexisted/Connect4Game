#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define FIELD_WIDTH 7
#define FIELD_HEIGHT 6

char globalPlayer1[20];
char globalPlayer2[20];
char gameField[FIELD_HEIGHT][FIELD_WIDTH];


bool placePiece(int column, char piece) {
    // Place piece in the lowest available cell in the specified column
    for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
        if (gameField[i][column] == ' ') {
            gameField[i][column] = piece;
            return true; // Placement successful
        }
    }
    printf("Column %d is full! Choose another column.\n", column + 1);
    return false; // Placement failed
}

void playerTurn(char *playerName, char piece) {
    int column;
    bool validMove = false;

    while (!validMove) {
        printf("%s, your turn. Enter a column (1-%d): ", playerName, FIELD_WIDTH);
        scanf("%d", &column);

        // Adjust for 0-based indexing and validate input
        if (column >= 1 && column <= FIELD_WIDTH) {
            validMove = placePiece(column - 1, piece);
        } else {
            printf("Invalid column. Please choose a column between 1 and %d.\n", FIELD_WIDTH);
        }
    }
}

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

bool isNameValid(const char *name) {
    const size_t nameLen = strlen(name);
    return nameLen > 0 && name[0] != '\n';
}

void getPlayer2() {
    printf("Enter the name of the Player2\n");
    scanf("%19s", globalPlayer2);
    bool isValid = isNameValid(globalPlayer2);
    switch (isValid) {
        case true:
            initializeField();
            displayField();
            while (true) { //TODO need to create method to check if win to avoid endless loop
                playerTurn(globalPlayer1, 'X'); // Player 1's turn
                displayField();

                playerTurn(globalPlayer2, 'O'); // Player 2's turn
                displayField();
            }
            break;
        default:
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
            printf("TODO Starting new game...\n");
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
