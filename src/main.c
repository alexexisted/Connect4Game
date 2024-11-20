#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define FIELD_WIDTH 7
#define FIELD_HEIGHT 6
#define WINNING_COUNT 4
#define FILENAME "result.txt"

char globalPlayer1[MAX_NAME_LENGTH];
char globalPlayer2[MAX_NAME_LENGTH];
char gameField[FIELD_HEIGHT][FIELD_WIDTH];
int gameID; // Unique ID for each saved game
bool isResumingSavedGame = false;  // Indicates whether a saved game is being resumed


void mainMenu();

void startGameLoop();

void promptForNewGame();

void displayField();

//TODO check input type to avoid inf. cycle
//TODO fix saving

void loadSavedGame() {
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
            sscanf(line, "Game ID: %d, Player 1: %s, Player 2: %s", &currentID, globalPlayer1, globalPlayer2);
            if (currentID == id) {
                gameFound = true;

                // Read the board and populate gameField
                for (int i = 0; i < FIELD_HEIGHT; i++) {
                    if (fgets(line, sizeof(line), file)) {
                        for (int j = 0; j < FIELD_WIDTH; j++) {
                            gameField[i][j] = line[j];  // Copy characters into gameField
                        }
                    }
                }

                printf("Game loaded successfully!\n");
                printf("Player 1: %s, Player 2: %s\n", globalPlayer1, globalPlayer2);
                displayField();  // Show the loaded game board

                isResumingSavedGame = true;  // Set the flag to prevent reinitialization
                startGameLoop();  // Start the game from the loaded state
                break;
            }
        }
    }

    if (!gameFound) {
        printf("Game with ID %d not found.\n", id);
    }

    fclose(file);
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

void listGamesClicked() {
    printf("1 - List all saved games\n");
    printf("2 - List all saved games for a particular player\n");
    printf("3 - Show the board of one of the saved games\n");
    printf("4 - Load the game\n");
    printf("5 - Return to main menu\n");

    int option;
    scanf("%d", &option);

    switch (option) {
        case 1:
            listAllSavedGames();
            listGamesClicked();
            break;
        case 2:
            listGamesByPlayer();
            listGamesClicked();
            break;
        case 3:
            showSavedGameBoard();
            listGamesClicked();
            break;
        case 4:
            loadSavedGame();
            break;
        case 5:
            mainMenu();
            break;
        default:
            printf("Enter valid value 1-5");
            listGamesClicked();
            break;
    }
}

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
    gameID = getNextUniqueID(); // Get the next unique ID

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
                listGamesClicked();
                break;
            case 3:
                printf("See you again!");
                return;
            default:
                printf("Enter a valid option (1, 2, or 3).\n");
        }
    }
}

void initializeGameID() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        gameID = 1;  // No saved file, start from ID 1
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
    gameID = maxID + 1;  // Set gameID to the next available ID
}

int main(void) {
    initializeGameID();
    mainMenu();
    return 0;
}
