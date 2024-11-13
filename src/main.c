#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20

char globalPlayer1[20];
char globalPlayer2[20];

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
            printf("Nice names\n");
            printf("%s\n%s", globalPlayer1, globalPlayer2);
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
