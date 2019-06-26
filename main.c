// GBDK LIBRARY
#include <gb/gb.h>
#include <gb/cgb.h>
#include <gb/font.h>
#include <gb/drawing.h>
#include <gb/console.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <rand.h>
#include <time.h>

// FUNCTIONS
#include "game/colors.c" // CGB color palettes
#include "game/helpers.c" // General functions that are used throughout states (sound, visual fx, etc)
#include "game/menu.c" // Menu state specific functions
#include "game/credits.c" // Credits state specific functions
#include "game/skins.c" // Skins state specific functions
#include "game/gameover.c" // Game over state specific functions
#include "game/game.c" // Game state functions and initialization of a lot of the variables

void main(){ // Main loop
    initColors();
    DISPLAY_ON;
    initGameMenu();
    while(1) {
        while(state == 0) { // 0: Credits
            switch(joypad()) { // Listens for user input
                case J_A:
                    waitpadup();  
                    DISPLAY_OFF;
                    initGameMenu();
                    state = 1;
                    break;
            }
            set_delay(2);
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
                        DISPLAY_OFF;
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
                        DISPLAY_OFF;
                        eraseMenuOptions();
                        initSkinsState();
                        state = 5;
                    }
                    break;
            }
            set_delay(2);
        }

        while(state == 2){ // 2: Game Loop
            countScore();
            processStun();
            startHazards();

            // Colorize skins
            if (selectedSkin < 2) {
                set_sprite_prop(39, 0);
            }
            if (selectedSkin >= 2){
                set_sprite_prop(39, selectedSkin + 1);
            }

            switch(joypad()) { // Listens for user input
                case J_LEFT:
                    if (stunned == 0) {
                        if (stun <= 65) { 
                            stun++;
                            animateStunQueue();
                            move_sprite(39, 44, 80); // Moves player sprite accordingly
                            move_sprite(37, 40, 76); // move stun queue
                            move_sprite(38, 48, 76); // move stun queue
                            playerX = 44;
                            playerY = 80;
                            if (selectedSkin == 0) {
                                set_sprite_tile(39, 3); // Sets the desired sprite tile to animate the eyes
                            }
                        }
                        else {
                            stunned = 1;
                            stun = 0;
                            resetPlayerPosition();
                        } 
                    }
                    break;
                case J_RIGHT: 
                    if (stunned == 0) {
                        if (stun <= 65) {
                            stun++; 
                            animateStunQueue();
                            move_sprite(39, 124, 80); 
                            move_sprite(37, 120, 76); // move stun queue
                            move_sprite(38, 128, 76); // move stun queue
                            playerX = 124;
                            playerY = 80;
                            if (selectedSkin == 0) {
                                set_sprite_tile(39, 9);
                            }
                        }
                        else {
                            stunned = 1;
                            stun = 0;
                            resetPlayerPosition();
                        }

                    }
                    break;
                case J_UP:
                    if (stunned == 0) {
                        if (stun <= 65) {
                            stun++;
                            animateStunQueue();
                            move_sprite(39, 84, 40); // move player sprite
                            move_sprite(37, 80, 36); // move stun queue
                            move_sprite(38, 88, 36); // move stun queue
                            playerX = 84;
                            playerY = 40;
                            if (selectedSkin == 0) {
                                set_sprite_tile(39, 9);
                            }
                        }
                        else {
                            stunned = 1;
                            stun = 0;
                            resetPlayerPosition();
                        }
                    }
                    break;
                case J_DOWN:
                    if (stunned == 0) {
                        if (stun <= 65) {
                            stun++;
                            animateStunQueue();
                            move_sprite(39, 84, 120);
                            move_sprite(37, 80, 116); // move stun queue
                            move_sprite(38, 88, 116); // move stun queue
                            playerX = 84;
                            playerY = 120;
                            if (selectedSkin == 0) {
                                set_sprite_tile(39, 5); 
                            }
                        }
                        else {
                            stunned = 1;
                            stun = 0;
                            resetPlayerPosition();
                        }
                    }
                    break;
                case J_START:
                    waitpadup();
                    state = 4;
                default: 
                    resetPlayerPosition(); // If no key, resets player to the center
            }
            isVLaserReadyToBlow();
            isHLaserReadyToBlow();
            isBombReadyToBlow();
            set_delay(2);
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
                    waitpadup();
                    clear_sprite_positions();
                    score = 0;
                    if (selected == 1) {
                        DISPLAY_OFF;
                        initGameLoop();
                        state = 2;
                    }
                    else if (selected == 0){
                        DISPLAY_OFF;
                        initGameMenu();
                        state = 1;
                    }
                    break;
            }
            set_delay(2);
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
                    if (selectedSkin < 3) {
                        selectedSkin++;
                        drawSelectedSkin();
                    }
                    break;
                case J_B: 
                    waitpadup();
                    selectedSkin = 0;
                    keyCount = 0;
                    DISPLAY_OFF;
                    initGameMenu();
                    state = 1;
                    break;
                case J_A:
                    waitpadup();
                    keyCount = 0;
                    DISPLAY_OFF;
                    initGameMenu();
                    state = 1;
                    break;
            }
            set_delay(2);
        }
    } 
}
