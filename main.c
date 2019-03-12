#include <gb/gb.h>
#include <gb/font.h>
#include <gb/drawing.h>
#include <gb/console.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <rand.h>
#include <time.h>
#include "sprites/player.c"
#include "sprites/verticallaser.c"
#include "background/game/backgroundmap.c"
#include "background/game/backgroundtiles.c"
#include "background/logo/logo.c"
#include "background/gameover/gameover.c"
#include "background/gameover/gameovermap.c"
#include "Laser.c"
//#include "BombLaser.c"

/* 
    Cheat sheet:
    0xE4 : 11100100 - Regular palette
    0xF9 : 11111001 - Darker
    0xFE : 11111110 - Even Darker
    0xFF : 11111111 - Even Darker
*/

struct Laser hLaser;
int hLaserReady = 1;
int hLaserPos, hCurrentClock;

struct Laser vLaser;
int vLaserReady = 1; 
int vLaserPos, vCurrentClock;

int bReady = 1;
int bPos, bCurrentClock;

int playerX, playerY;

int score = 0;
int state = 1;

unsigned int generate_random_num(int upper) { // Generates random with upper as maximum
    unsigned int num;
    num = (rand() % (upper + 1) );
    return num; 
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

void resetPlayerPosition(){
    set_sprite_tile(39, 11);
    move_sprite(39, 84, 80); 
    playerX = 84;
    playerY = 80;
}

void initGameLoop(){
    set_bkg_data(109, 3, BackgroundTiles); // Sets which background tileset to use, starts on 39, after the font load, counts three tiles
    set_bkg_tiles(0, 0, 20, 18, BackgroundMap); // Sets which background map to use and position on screen starting on x=0, y=0 (offscreen) and spanning 20x18 tiles of 8 pixels each
    SPRITES_8x16; // Activate 8*16 sprite mode, defaults to 8x8
    set_sprite_data(0, 12, Player); // Sets the player sprite, starts on zero, counts seven
    set_sprite_data(12, 16, VerticalLaser); // Sets the vertical laser sprites 
    SHOW_SPRITES; // Draw sprites
    resetPlayerPosition();
    fadein();
}

void countScore() {
    gotoxy(1, 16); // Position of the console on screen, uses tiles so x=1*8 and y=16*8
    printf("%u", score++); // Print score at desired position
}

void main(){
    while(1) {
        while(state == 0){ // 0: Splash Screen
 
        }

        while(state == 1){ // 1: Main Menu 
            font_t ibm; // Declare font variable
            set_bkg_palette(0, 1, gbpic_pal);
            set_bkg_data(0x01, gbpic_tiles, gbpic_dat);
            set_bkg_tiles(0, 0, gbpic_cols, gbpic_rows, gbpic_att);
            set_bkg_tiles(0, 0, gbpic_cols, gbpic_rows, gbpic_map);
            SHOW_BKG; // Draw background
            DISPLAY_ON; // Turn on display
            fadein();
            waitpad(J_START); // Wait for Start Key
            waitpadup(); // Wait for release
            fadeout();
            font_init(); // Initialize font library after state change to avoid overwriting bg tiles
            color(DKGREY, BLACK, SOLID); // Customize colors of font 
            ibm = font_load(font_ibm); // Load built in font_ibm
            font_set(ibm); // Set built in font_ibm, will be used on displaying the score, only 36 tiles
            initGameLoop(); // Loads sprites and backgrounds to VRAM
            state = 2;
        }

        while(state == 2){ // 2: Game Loop
            countScore();
            startHazards();

            // Debug clock
            gotoxy(1, 1);
            printf("C:");
            printf("%d", clock() / CLOCKS_PER_SEC);

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
            HIDE_SPRITES;
            set_bkg_data(0, 1, GameOverTiles); // Sets which background tileset to use, starts on 39, after the font load, counts three tiles
            set_bkg_tiles(0, 0, 20, 18, GameOverMap); // Sets which background map to use and position on screen starting on x=0, y=0 (offscreen) and spanning 20x18 tiles of 8 pixels each
            gotoxy(1,1);
            printf("FINAL SCORE: ");
            printf("%d", --score);
            gotoxy(1, 14);
            printf("WHEN YOU DIE, YOU");
            gotoxy(1, 16);
            printf("DIE. THAT'S IT.");
            fadein();
            waitpad(J_START);
            waitpadup();
            fadeout();
            score = 0;
            state = 1;
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
