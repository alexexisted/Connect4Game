//
// Created by Alexa G on 11/20/24.
//

#include "navigation_logic.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db_logic.h"
#include "game_state.h"
#include "utils_logic.h"


//main menu
void mainMenu(GameState *state) {
    while (true) {
        //movements to avoid endless loop if user enter string
        char tempOption[10];
        printf("1 - Play new game\n2 - Load already saved game\n3 - Exit the game\n");

        //read user's input as a string
        scanf("%9s", tempOption);

        //check if it is a single digit number
        if (strlen(tempOption) == 1 && isdigit(tempOption[0])) {
            //convert input to integer
            const int mainOption = atoi(tempOption);

            switch (mainOption) {
                case 1:
                    getPlayerNames(state);
                    startGameLoop(state);
                    break;
                case 2:
                    listGamesClicked(state);
                    break;
                case 3:
                    printf("See you again!\n");
                    return;
                default:
                    printf("Enter a valid option (1, 2, or 3).\n");
            }
        } else {
            //input is invalid like not a digit or longer than 1 character
            printf("Invalid input. Please enter a number (1, 2, or 3).\n");
        }
    }
}


void promptForNewGame(GameState *state) {
    char tempOption[1];
    printf("\nGame Over! Would you like to:\n");
    printf("1 - Start a new game\n");
    printf("2 - Return to main menu\n");
    printf("Enter your choice: ");
    scanf("%1s", &tempOption);

    if (strlen(tempOption) == 1 && isdigit(tempOption[0])) {
       int choice = atoi(tempOption);

        if (choice == 1) {
            startGameLoop(state);
        } else {
            mainMenu(state);
        }
    } else {
        printf("Enter correct value");
    }
}

void listGamesClicked(GameState *state) {
    printf("1 - List all saved games\n");
    printf("2 - List all saved games for a particular player\n");
    printf("3 - Show the board of one of the saved games\n");
    printf("4 - Load the game\n");
    printf("5 - Return to main menu\n");

    char tempOption[1];
    scanf("%1s", &tempOption);

    if (strlen(tempOption) == 1 && isdigit(tempOption[0])) {
        int option = atoi(tempOption);

        switch (option) {
            case 1:
                listAllSavedGames();
            listGamesClicked(state);
            break;
            case 2:
                listGamesByPlayer();
            listGamesClicked(state);
            break;
            case 3:
                showSavedGameBoard();
            listGamesClicked(state);
            break;
            case 4:
                loadSavedGame(state);
            break;
            case 5:
                mainMenu(state);
            break;
            default:
                printf("Enter valid value 1-5");
            listGamesClicked(state);
            break;
        }
    } else {
        printf("Enter correct value");
    }
}
