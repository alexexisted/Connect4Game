#include "db_logic.h"
#include "game_state.h"
#include "navigation_logic.h"

int main(void) {
    GameState state;
    initializeGameID(&state);
    mainMenu(&state);
    return 0;
}