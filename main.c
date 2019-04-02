// GBDK LIBRARY
#include <gb/gb.h>
#include <gb/font.h>
#include <gb/drawing.h>
#include <gb/console.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <rand.h>
#include <time.h>

// FUNCTIONS
#include "game/helpers.c" // General functions that are used throughout states (sound, visual fx, etc)
#include "game/menu.c" // Menu state specific functions
#include "game/credits.c" // Credits state specific functions
#include "game/skins.c" // Skins state specific functions
#include "game/gameover.c" // Game over state specific functions
#include "game/game.c" // Game state functions and initialization of a lot of the variables

void main(){ // Main loop
    DISPLAY_ON;
    initGameMenu();
    while(1) {
        while(state == 0) { // 0: Credits
            switch(joypad()) { // Listens for user input
                case J_A:
                    waitpadup();  
                    initGameMenu();
                    state = 1;
                    break;
            }
            setDelay(2);
        }

        while(state == 1){ // 1: Main Menu  
            switch(joypad()) { // Listens for user input
                case J_UP:
                    drawPlay();
                    waitpadup();
                    processCheatCode(J_UP);
                    break;
                case J_DOWN:
                    drawCredits();
                    waitpadup();
                    processCheatCode(J_DOWN);
                    break;
                case J_LEFT: 
                    waitpadup();
                    processCheatCode(J_LEFT);
                    break;
                case J_RIGHT: 
                    waitpadup();
                    processCheatCode(J_RIGHT);
                    break;
                case J_B: 
                    waitpadup();
                    processCheatCode(J_B);
                    break;
                case J_A:
                    waitpadup();
                    processCheatCode(J_A);
                    if (keyCount < 10) {
                        fadeout();
                        eraseMenuOptions();
                        if (selected == 1) {
                            initGameLoop(); // Loads sprites and backgrounds to VRAM
                            state = 2;
                        }
                        else if (selected == 2){
                            initCredits();
                            state = 0;
                            selected = 1;
                        }
                    }
                    else {
                        fadeout();
                        eraseMenuOptions();
                        initSkinsState();
                        state = 5;
                    }
                    break;
            }
            setDelay(2);
        }

        while(state == 2){ // 2: Game Loop
            countScore();

            // Debug clock -- convert clock to int
            gotoxy(1, 1);
            printf("C:");
            printf("%d", clock() / CLOCKS_PER_SEC);

            startHazards();
            switch(joypad()) { // Listens for user input
                case J_LEFT:
                    move_sprite(39, 44, 80); // Moves player sprite accordingly
                    playerX = 44;
                    playerY = 80;
                    if (selectedSkin == 0) {
                        set_sprite_tile(39, 3); // Sets the desired sprite tile to animate the eyes
                    }
                    break;
                case J_RIGHT:
                    move_sprite(39, 124, 80); 
                    playerX = 124;
                    playerY = 80;
                    if (selectedSkin == 0) {
                        set_sprite_tile(39, 9);
                    }
                    break;
                case J_UP:
                    move_sprite(39, 84, 40); 
                    playerX = 84;
                    playerY = 40;
                    if (selectedSkin == 0) {
                        set_sprite_tile(39, 9);
                    }
                    break;
                case J_DOWN:
                    move_sprite(39, 84, 120);
                    playerX = 84;
                    playerY = 120;
                    if (selectedSkin == 0) {
                        set_sprite_tile(39, 5); 
                    }
                    break;
                case J_START:
                    waitpadup();
                    state = 4;
                default: 
                    resetPlayerPosition(); // If no key, resets player to the center
            }
            isVLaserReadyToBlow();
            setDelay(2);
        }

        while (state == 3) { // 3: Game Over
            switch(joypad()) { // Listens for user input
                case J_LEFT:
                    drawYes();
                    break;
                case J_RIGHT:
                    drawNo();
                    break;
                case J_A:
                    eraseOptions();
                    score = 0;
                    if (selected == 1) {
                        fadeout();
                        initGameLoop();
                        state = 2;
                    }
                    else if (selected == 0){
                        initGameMenu();
                        state = 1;
                    }
                    break;
            }
            setDelay(2);
        }

        while (state == 4) { // 4: Pause
            gotoxy(13, 16);
            printf("%s", "PAUSED");
            waitpad(J_START);
            waitpadup();
            gotoxy(13, 16);
            printf("%s", "      "); 
            state = 2; 
        }

        while (state == 5) {
            switch(joypad()) { // Listens for user input
                case J_LEFT: 
                    waitpadup();
                    if (selectedSkin > 0) {
                        selectedSkin--;
                        drawSelectedSkin();
                    }
                    break;
                case J_RIGHT: 
                    waitpadup();
                    if (selectedSkin < 5) {
                        selectedSkin++;
                        drawSelectedSkin();
                    }
                    break;
                case J_B: 
                    waitpadup();
                    selectedSkin = 0;
                    keyCount = 0;
                    initGameMenu();
                    state = 1;
                    break;
                case J_A:
                    waitpadup();
                    keyCount = 0;
                    initGameMenu();
                    state = 1;
                    break;
            }
            setDelay(2);
        }
    }
}
