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


bool checkDirection(int row, int col, int rowDir, int colDir, char piece) {
    int count = 0;

    for (int i = 0; i < WINNING_COUNT; i++) {
        int newRow = row + i * rowDir;
        int newCol = col + i * colDir;

        // Ensure we’re within bounds and that the cell contains the player's piece
        if (newRow >= 0 && newRow < FIELD_HEIGHT &&
            newCol >= 0 && newCol < FIELD_WIDTH &&
            gameField[newRow][newCol] == piece) {
            count++;
            } else {
                break;
            }
    }

    return count == WINNING_COUNT;
}

bool checkWin(char piece) {
    // Iterate over each cell on the board
    for (int row = 0; row < FIELD_HEIGHT; row++) {
        for (int col = 0; col < FIELD_WIDTH; col++) {
            // Check for a win only if the cell has the player's piece
            if (gameField[row][col] == piece) {
                // Check all directions: horizontal, vertical, diagonal (2 ways)
                if (checkDirection(row, col, 0, 1, piece) ||    // Horizontal
                    checkDirection(row, col, 1, 0, piece) ||    // Vertical
                    checkDirection(row, col, 1, 1, piece) ||    // Diagonal down-right
                    checkDirection(row, col, 1, -1, piece)) {   // Diagonal down-left
                    return true;  // Win found
                    }
            }
        }
    }

    return false;  // No win found
}

bool placeUsersMove(int column, char usersMove) {
    for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
        if (gameField[i][column] == ' ') { //check if cell is empty
            gameField[i][column] = usersMove; //rewrite the array with user's sign
            return true;
        }
    }
    printf("Column %d is full! Choose another column.\n", column + 1);
    return false;
}

void playerTurn(char *playerName, const char users_move) {
    int column;
    bool validMove = false;

    while (!validMove) {
        printf("%s, your turn. Enter a column (1-%d): ", playerName, FIELD_WIDTH);
        scanf("%d", &column);
        // if (checkWin("X") || checkWin("0")) {
        //     printf("You won!");
        //     validMove = false;
        // }

        if (column >= 1 && column <= FIELD_WIDTH) {
            validMove = placeUsersMove(column - 1, users_move);
        } else { //TODO if 0 then save
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
                playerTurn(globalPlayer1, 'X');
                displayField();

                playerTurn(globalPlayer2, 'O');
                displayField();
            }
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
