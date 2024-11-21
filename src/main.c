#include "db_logic.h"
#include "game_state.h"
#include "navigation_logic.h"
//TODO check input type to avoid inf. cycle

int main(void) {
    GameState state;
    initializeGameID();
    mainMenu(&state);
    return 0;
}