#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20

char globalPlayer1[20];
char globalPlayer2[20];

bool isNameValid(char name) {
    const size_t nameLen = strlen(name);
    switch (nameLen) {
        case 0:
            return false;
            break;

        default:
            return true;
            break;
    }
}

void getPlayer2() {
    printf("Enter the name of the Player2\n");
    scanf("%s", &globalPlayer2);
    if (isNameValid(globalPlayer2) == true) {
        printf("Nice name");
    } else {
        printf("Incorrect name, try again");
        getPlayer2();
    }
}

void getPlayer1() {
    printf("Enter the name of the Player1\n");
    scanf("%s", &globalPlayer1);
    if (isNameValid(globalPlayer1) == true) {
        getPlayer2();
    } else {
        printf("Incorrect name, try again");
        getPlayer1();
    }
}

int mainMenu() {
    printf("1 - Play new game\n2 - Load saved game\n3 - Exit the game\n");
    int mainOption;
    scanf("%d", &mainOption);

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
