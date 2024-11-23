#include "db_logic.h"
#include "game_state.h"
#include "navigation_logic.h"
//TODO check input type to avoid inf. loop

int main(void) {
    GameState state;
    initializeGameID(&state);
    mainMenu(&state);
    return 0;
}