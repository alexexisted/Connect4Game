#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 20
#define FIELD_WIDTH 7
#define FIELD_HEIGHT 6
#define WINNING_COUNT 4
#define FILENAME "result.txt"

char globalPlayer1[MAX_NAME_LENGTH];
char globalPlayer2[MAX_NAME_LENGTH];
char gameField[FIELD_HEIGHT][FIELD_WIDTH];
int gameID = 1; // Unique ID for each saved game

void mainMenu();
void startGameLoop();
void promptForNewGame();


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

// Save the current game state to a file
void saveGame() {
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        printf("Error saving game.\n");
        return;
    }

    fprintf(file, "Game ID: %d, Player 1: %s, Player 2: %s\n", gameID, globalPlayer1, globalPlayer2);
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            fprintf(file, "%c", gameField[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    printf("Game saved with ID: %d\n", gameID);
    gameID++; // Increment game ID for the next game
    fclose(file);
}

// Load and display saved games from the file
void listSavedGames() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("No saved games available.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
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

void promptForNewGame() {
    int choice;
    printf("\nGame Over! Would you like to:\n");
    printf("1 - Start a new game\n");
    printf("2 - Return to main menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        startGameLoop();
    } else {
        mainMenu();
    }
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
                    promptForNewGame();
                    ; // End the game if there's a winner
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

// Main game loop to handle turns
void startGameLoop() {
    initializeField();
    displayField();

    while (true) {
        playerTurn(globalPlayer1, 'X'); // Player 1's turn
        displayField();

        playerTurn(globalPlayer2, 'O'); // Player 2's turn
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

// Main menu and additional options
void mainMenu() {
    int mainOption;
    while (true) {
        printf("1 - Play new game\n2 - Load already saved game\n3 - Exit the game\n");
        scanf("%1d", &mainOption);

        switch (mainOption) {
            case 1:
                getPlayerNames();
                startGameLoop();
                break;
            case 2:
                listSavedGames();
                break;
            case 3:
                printf("See you again!");
                return;
            default:
                printf("Enter a valid option (1, 2, or 3).\n");
        }
    }
}

int main(void) {
    mainMenu();
    return 0;
}
