cmake_minimum_required(VERSION 3.29)
project(Connect4Game C)

set(CMAKE_C_STANDARD 23)

add_executable(Connect4Game src/main.c
        src/game_logic.h
        src/game_logic.c
        src/db_logic.h
        src/db_logic.c
        src/navigation_logic.c
        src/navigation_logic.h
        src/utils_logic.c
        src/utils_logic.h)
