// GBDK
#include <gb/gb.h>
#include <gb/font.h>
#include <gb/drawing.h>
#include <gb/console.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <rand.h>
#include <time.h>

// SPRITES
#include "sprites/player.c"
#include "sprites/verticallaser.c"

// WORDS
#include "sprites/words/Yes.c"
#include "sprites/words/No.c"
#include "sprites/words/Play.c"
#include "sprites/words/Credits.c"

// BACKGROUNDS
#include "background/game/backgroundmap.c"
#include "background/game/backgroundtiles.c"
#include "background/logo/logo.c"
#include "background/gameover/gameover.c"

// STRUCTS
#include "Laser.c"

/* 
    Cheat sheet:
    0xE4 : 11100100 - Regular palette
    0xF9 : 11111001 - Darker
    0xFE : 11111110 - Even Darker
    0xFF : 11111111 - Even Darker
    Code: Up-Up-Down-Down-Left-Right-Left-Right-B-A
*/

// Play state variables
struct Laser hLaser;
int hLaserReady = 1;
int hLaserPos, hCurrentClock;

struct Laser vLaser;
int vLaserReady = 1; 
int vLaserPos, vCurrentClock;

int bReady = 1;
int bPos, bCurrentClock;

int playerX, playerY;

// Global game variables
int score = 0; 
int state = 1;

// Menu variables
int selected = 1; 
int keyCount = 0;
unsigned char *cheatCode[10] = {J_UP, J_UP, J_DOWN, J_DOWN, J_LEFT, J_RIGHT, J_LEFT, J_RIGHT, J_B, J_A};

unsigned int generate_random_num(int upper) { // Generates random with upper as maximum
    unsigned int num;
    num = (rand() % (upper + 1) );
    return num; 
}

void processCheatCode(char key) {
    if (keyCount < 10) {
        if (key == cheatCode[keyCount]) {
            keyCount++;
        }
        else {
            keyCount = 0;
        }
    }
}

void playSoundFX(UINT8 fx) {
    if (fx == 0) { // Laser blowing sound 
        NR52_REG = 0x80; // Turn on sound registers, setting it to 0x00 turns them off
        NR51_REG = 0x11; // Select channel to use: 0x11 - 1, 0x22 - 2, 0x33 - 3, 0x88 - 4, 0xFF - All
        NR50_REG = 0x77; // Volume, min: 0x00, max: 0x77
        
        NR10_REG = 0x1C; // Channel 1, Register 0 => Binary: 00001100
        NR11_REG = 0xC6; // Channel 1, Register 1 => Binary: 11000110 
        NR12_REG = 0x73; // Channel 1, Register 2 => Binary: 01110011
        NR13_REG = 0x00; // Channel 1, Register 3 => Binary: 00000000
        NR14_REG = 0xC3; // Channel 1, Register 4 => Binary: 11000011
    }
}

void setDelay(int loops) {
    int i;
    for (i = 0; i < loops; i++){
        wait_vbl_done();
    }
}

void fadeout() {
    UINT8 i;
    for (i=0; i<4; i++) {
        if (i == 0) {
            BGP_REG = 0xE4; // Background palette
            OBP0_REG = 0xE4; // Sprite palette
        }
        if (i == 1) {
            BGP_REG = 0x90;
            OBP0_REG = 0x90;
        }
        if (i == 2) {
            BGP_REG = 0x80;
            OBP0_REG = 0x80;
        }
        if (i == 3) {
            BGP_REG = 0x00;
            OBP0_REG = 0x00;
        }
        setDelay(3);
    }
}

void fadein() {
    UINT8 i;
    for (i=0; i<4; i++) {
        if (i == 0) {
            OBP0_REG = 0x00; // Sprite palette
            BGP_REG = 0x00; // Background palette
        }
        if (i == 1) {
            OBP0_REG = 0x80;
            BGP_REG = 0x80;
        }
        if (i == 2) {
            OBP0_REG = 0x90;
            BGP_REG = 0x90;
        }
        if (i == 3) {
            OBP0_REG = 0xE4; 
            BGP_REG = 0xE4;
        }
        setDelay(3);
    }
}

void drawYes() {
    UINT8 i, z;
    selected = 1;
    for (z = 0; z < 5; z++ ){
        set_sprite_tile(z + 6, z + z + 12);
        move_sprite(z + 6, 166 + z + 8, 144);
    }
    for (i = 0; i < 6; i++ ){
        set_sprite_tile(i, i + i);
        move_sprite(i, 44 + i*8, 120);
    }
}

void drawNo() {
    UINT8 i, z;
    selected = 0;
    for (z = 0; z < 6; z++ ){
        set_sprite_tile(z, z + z);
        move_sprite(z, 166 + z + 8, 144);
    }
    for (i = 0; i < 5; i++ ){
        set_sprite_tile(i + 6, i + i + 12);
        move_sprite(i + 6, 97 + i*8, 120);
    }
}

void eraseOptions() {
    UINT8 i, z;
    for (z = 0; z < 6; z++ ){
        move_sprite(z, 166 + z + 8, 144);
    }
    for (i = 0; i < 5; i++ ){
        move_sprite(i + 6, 166 + i + 8, 144);
    }
}

void drawPlay() {
    UINT8 i, z;
    selected = 1;
    for (z = 0; z < 8; z++ ){
        set_sprite_tile(z + 12, z + z + 12);
        move_sprite(z + 12, 166 + z + 8, 144);
    }
    for (i = 0; i < 5; i++ ){
        set_sprite_tile(i, i + i);
        move_sprite(i, 72 + i*8, 112);
    }
}

void drawCredits() {
    UINT8 i, z;
    selected = 2;
    for (z = 0; z < 5; z++ ){
        set_sprite_tile(z, z + z);
        move_sprite(z, 166 + z + 8, 144);
    }
    for (i = 0; i < 8; i++ ){
        set_sprite_tile(i + 12, i + i + 12);
        move_sprite(i + 12, 57 + i*8, 127);
    }
}

void eraseMenuOptions() {
    UINT8 i, z;
    for (z = 0; z < 5; z++ ){
        set_sprite_tile(z, z + z);
        move_sprite(z, 166 + z + 8, 144);
    }
    for (i = 0; i < 8; i++ ){
        set_sprite_tile(i + 12, i + i + 12);
        move_sprite(i + 12, 166 + i + 8, 144);
    }
}

void initGameOver(){
    HIDE_SPRITES;
    set_bkg_palette(0, 1, gameoverbg_pal);
    set_bkg_data(0x01, gameoverbg_tiles, gameoverbg_dat);
    set_bkg_tiles(0, 0, gameoverbg_cols, gameoverbg_rows, gameoverbg_att);
    set_bkg_tiles(0, 0, gameoverbg_cols, gameoverbg_rows, gameoverbg_map);
    move_bkg (0, 0);
    SHOW_BKG;
    set_sprite_data(0, 12, Yes); // Sets the yes sprite, starts on zero, counts twelve tiles
    set_sprite_data(12, 10, No); // Sets the no sprite, starts on 12, counts ten tiles
    drawYes();
    set_sprite_tile(39, 50); // empty player sprite
    SHOW_SPRITES;
    fadein();
}

void resetPlayerPosition(){
    set_sprite_tile(39, 11);
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
    set_sprite_data(0, 12, Player); // Sets the player sprite, starts on zero, counts seven
    set_sprite_data(12, 16, VerticalLaser); // Sets the vertical laser sprites 
    SHOW_SPRITES; // Draw sprites
    resetPlayerPosition();
    fadein();
}

void initGameMenu() {
    fadeout();
    HIDE_SPRITES;
    set_bkg_palette(0, 1, gbpic_pal);
	set_bkg_data(0x01, gbpic_tiles, gbpic_dat);
	VBK_REG = 1;
	set_bkg_tiles(0, 0, gbpic_cols, gbpic_rows, gbpic_att);
	VBK_REG = 0;
	set_bkg_tiles(0, 0, gbpic_cols, gbpic_rows, gbpic_map);
	move_bkg (0, 0);
	SHOW_BKG;
    SPRITES_8x16; // Activate 8*16 sprite mode, defaults to 8x8
    set_sprite_data(0, 12, Play);
    set_sprite_data(12, 16, Credits);
    drawPlay();
    SHOW_SPRITES;
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
        set_sprite_tile(i, 12);
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
                set_sprite_tile(i, 10+z);
            }
            drawTheVLaser(&vLaser, vLaserPos, 0);
            setDelay(2);
        }
        if (playerX == vLaserPos) {
            fadeout();
            initGameOver();
            state = 3;
        }
        vLaserReady = 1;
    }
}

void callVLaser(){
    unsigned int pos = generate_random_num(3);
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
    unsigned int hazard;
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

void countScore() {
    gotoxy(1, 16); // Position of the console on screen, uses tiles so x=1*8 and y=16*8
    printf("%u", score++); // Print score at desired position
}

void main(){
    DISPLAY_ON;
    initGameMenu();
    while(1) {
        while(state == 0) { // 0: Credits
            
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
                            state = 0;
                            selected = 1;
                        }
                    }
                    else {
                        gotoxy(1, 16);
                        printf("%s", "cheat code unlocked");
                    }
                    break;
            }
        }

        while(state == 2){ // 2: Game Loop
            countScore();
            startHazards();
            switch(joypad()) { // Listens for user input
                case J_LEFT:
                    move_sprite(39, 44, 80); // Moves player sprite accordingly
                    playerX = 44;
                    playerY = 80;
                    set_sprite_tile(39, 3); // Sets the desired sprite tile to animate the eyes
                    break;
                case J_RIGHT:
                    move_sprite(39, 124, 80); 
                    playerX = 124;
                    playerY = 80;
                    set_sprite_tile(39, 9);
                    break;
                case J_UP:
                    move_sprite(39, 84, 40); 
                    playerX = 84;
                    playerY = 40;
                    set_sprite_tile(39, 9);
                    break;
                case J_DOWN:
                    move_sprite(39, 84, 120);
                    playerX = 84;
                    playerY = 120;
                    set_sprite_tile(39, 5); 
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
    }
}
