#include <stdio.h>
#include <stdlib.h>


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
            break;
        case 2:
            printf("TODO saved games menu");
            break;
        case 3:
            printf("See you again!");
            return EXIT_SUCCESS;
            break;
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
