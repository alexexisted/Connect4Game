//
// Created by Alexa G on 11/20/24.
//

#include "navigation_logic.h"

#include <stdio.h>

#include "db_logic.h"
#include "utils_logic.h"

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
