// GBDK LIBRARY
#include <gb/gb.h>
#include <gb/font.h>
#include <gb/drawing.h>
#include <gb/console.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <rand.h>
#include <time.h>

// EXTERNAL FUNCTIONS
#include "helpers.c" // General functions that are used throughout states (sound, visual fx, etc)
#include "menu.c" // Menu state specific functions
#include "gameover.c" // Game over state specific functions
#include "credits.c" // Credits state specific functions
#include "skins.c" // Skins state specific functions

// GAME BACKGROUNDS
#include "background/game/backgroundmap.c"
#include "background/game/backgroundtiles.c"

// GAME SPRITES
#include "sprites/player.c"
#include "sprites/verticallaser.c"

// GENERAL STATE AND GAMEPLAY VARIABLES
struct Laser {
    UBYTE repetitions[10];
}

struct Laser hLaser;
UINT8 hLaserReady = 1;
UINT8 hLaserPos, hCurrentClock;
 
struct Laser vLaser;
UINT8 vLaserReady = 1; 
UINT8 vLaserPos, vCurrentClock;

UINT8 bReady = 1;
UINT8 bPos, bCurrentClock;

UINT8 playerX, playerY;

int score = 0; 
UINT8 state = 1;

void countScore() {
    gotoxy(1, 16); // Position of the console on screen, uses tiles so x=1*8 and y=16*8
    printf("%u", score++); // Print score at desired position
}

void resetPlayerPosition(){
    UINT8 w;
    for (w = 0; w <= 5; w++) {
        if (w == selectedSkin) {
            set_sprite_tile(39, 11+w+w);
        }
    }
    move_sprite(39, 84, 80); 
    playerX = 84;
    playerY = 80;
}

void initGameLoop(){
    font_t ibm; // Declare font variable
    font_init(); // Initialize font library after state change to avoid overwriting bg tiles
    color(DKGREY, BLACK, SOLID); // Customize colors of font 
    ibm = font_load(font_ibm); // Load built in font_ibm
    font_set(ibm); // Set built in font_ibm, will be used on displaying the score, only 36 tiles
    set_bkg_data(109, 3, BackgroundTiles); // Sets which background tileset to use, starts on 39, after the font load, counts three tiles
    set_bkg_tiles(0, 0, 20, 18, BackgroundMap); // Sets which background map to use and position on screen starting on x=0, y=0 (offscreen) and spanning 20x18 tiles of 8 pixels each
    set_sprite_data(0, 30, Player); // Sets the player sprite, starts on zero, counts seven
    set_sprite_data(30, 18, VerticalLaser); // Sets the vertical laser sprites 
    SHOW_SPRITES; // Draw sprites
    resetPlayerPosition();
    fadein();
}
 
void drawTheVLaser(struct Laser* laser, UINT8 x, UINT8 y) {
    UINT8 i; 
    for (i = 1; i < 10; i++ ){ 
        move_sprite(laser->repetitions[i], x, y + (16 * i));
    } 
}

void triggerVLaser(UINT8 x) { // Trigger Vertical Laser, only requires x coordinate, y = 0
    UINT8 i;
    vLaserPos = x;
    vCurrentClock = (clock() / CLOCKS_PER_SEC);
    for(i = 0; i < 9; i++){
        vLaser.repetitions[i] = i;
        set_sprite_tile(i, 30);
    }
    drawTheVLaser(&vLaser, x, 0);
}

void isVLaserReadyToBlow() {
    UINT8 i, z;
    if ( (clock() / CLOCKS_PER_SEC) - vCurrentClock >= 1 && vLaserReady == 0 ) {
        playSoundFX(0);
        for (z = 2; z < 20; z+=2) {
            for(i = 0; i < 9; i++){
                vLaser.repetitions[i] = i;
                set_sprite_tile(i, 28+z);
            }
            drawTheVLaser(&vLaser, vLaserPos, 0);
            setDelay(2);
        }
        if (playerX == vLaserPos) {
            for (i = 0; i <= 5; i++) {
                set_sprite_tile(39, 23+i);
                setDelay(3);
            }
            fadeout();
            initGameOver();
            state = 3;
        }
        vLaserReady = 1;
    }
}

void callVLaser(){
    unsigned UINT8 pos = generate_random_num(3);
    if (pos == 0) {
        vLaserReady = 0;
        triggerVLaser(44);
    }
    else if (pos == 1) {
        vLaserReady = 0;
        triggerVLaser(84);
    }
    else if (pos == 2) {
        vLaserReady = 0;
        triggerVLaser(124);
    }
    else if (pos == 3) {
        vLaserReady = 1;
    }
}

void startHazards() {
    unsigned UINT8 hazard;
    if ( (clock() / CLOCKS_PER_SEC) % 2 == 0) { // change for timer 
        hazard = generate_random_num(2);
        if (hazard == 0 && vLaserReady == 1) {
            callVLaser();
        }
        else if (hazard == 1 && hLaserReady == 1) {
            //callHLaser();
            printf("");
        }
        else if (hazard == 2 && bReady == 1) {
           //callBomb();
           printf("");
        }
    }
}

void main(){
    DISPLAY_ON;
    initGameMenu();
    while(1) {
        while(state == 0) { // 0: Credits
            switch(joypad()) { // Listens for user input
                case J_A:
                    waitpadup();  
                    initGameMenu();
                    state = 1;
            }
            setDelay(1);
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
            setDelay(1);
        }

        while(state == 2){ // 2: Game Loop
            countScore();
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
            setDelay(1);
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
            setDelay(1);
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
            setDelay(1);
        }
    }
}
