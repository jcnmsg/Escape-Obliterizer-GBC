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
#include "background/backgroundmap.c"
#include "background/backgroundtiles.c"
#include "background/logo.c"
#include "Laser.c"

 // 0: false | 1: true

struct Laser hLaser;
int hLaserReady = 1;
int hLaserPos, hCurrentClock;

struct Laser vLaser;
int vLaserReady = 1; 
int vLaserPos, vCurrentClock;

int bReady = 1;
int bPos, bCurrentClock;

int score = 0;
int state = 1;

unsigned int generate_random_num(int upper) { 
    unsigned int num;
    num = (rand() % (upper + 1) );
    return num; 
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
    for(i = 1; i < 10; i++){
        vLaser.repetitions[i] = i;
        set_sprite_tile(i, 12);
    }
    drawTheVLaser(&vLaser, x, 0);
}

void isVLaserReadyToBlow() {
    UINT8 i, z;
    if ( (clock() / CLOCKS_PER_SEC) - vCurrentClock == 1 && vLaserReady == 0 ) {
        for (z = 2; z < 20; z+=2) {
            for(i = 1; i < 10; i++){
                vLaser.repetitions[i] = i;
                set_sprite_tile(i, 10+z);
            }
            drawTheVLaser(&vLaser, vLaserPos, 0);
            delay(30);
        }
        vLaserReady = 1;
    }
}

void callVLaser(){
    unsigned int pos = generate_random_num(3);
    if (pos == 0) {
        vLaserReady = 0;
        triggerVLaser(44);
        gotoxy(18,16);
        printf("%d", pos);
    }
    else if (pos == 1) {
        vLaserReady = 0;
        triggerVLaser(84);
        gotoxy(18,16);
        printf("%d", pos);
    }
    else if (pos == 2) {
        vLaserReady = 0;
        triggerVLaser(124);
        gotoxy(18,16);
        printf("%d", pos);
    }
    else if (pos == 3) {
        vLaserReady = 1;
        gotoxy(18,16);
        printf("%d", pos);
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
            printf("L");
        }
        else if (hazard == 2 && bReady == 1) {
           //callBomb();
           printf("B");
        }
    }
}

void resetPlayerPosition(){
    set_sprite_tile(0, 11);
    move_sprite(0, 84, 80); 
}

void initGameLoop(){
    set_bkg_data(39, 3, BackgroundTiles); // Sets which background tileset to use, starts on 39, after the font load, counts three tiles
    set_bkg_tiles(0, 0, 20, 18, BackgroundMap); // Sets which background map to use and position on screen starting on x=0, y=0 (offscreen) and spanning 20x18 tiles of 8 pixels each
    SPRITES_8x16; // Activate 8*16 sprite mode, defaults to 8x8
    set_sprite_data(0, 12, Player); // Sets the player sprite, starts on zero, counts seven
    set_sprite_data(12, 16, VerticalLaser); // Sets the vertical laser sprites 
    SHOW_SPRITES; // Draw sprites
}

void setDelay(int loops) {
    int i;
    for (i = 0; i < loops; i++){
        wait_vbl_done();
    }
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
            VBK_REG = 1; // Sets the Video Bank Register. When set to zero, it loads the tile data into the background. When set to one...
            set_bkg_tiles(0, 0, gbpic_cols, gbpic_rows, gbpic_att);
            VBK_REG = 0;
            set_bkg_tiles(0, 0, gbpic_cols, gbpic_rows, gbpic_map);
            SHOW_BKG; // Draw background
            DISPLAY_ON; // Turn on display
            waitpad(J_START); // Wait for Start Key
            waitpadup(); // Wait for release
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
                    move_sprite(0, 44, 80); // Moves player sprite accordingly
                    set_sprite_tile(0, 3); // Sets the desired sprite tile to animate the eyes
                    break;
                case J_RIGHT:
                    move_sprite(0, 124, 80); 
                    set_sprite_tile(0, 9);
                    break;
                case J_UP:
                    move_sprite(0, 84, 40); 
                    set_sprite_tile(0, 9);
                    break;
                case J_DOWN:
                    move_sprite(0, 84, 120);
                    set_sprite_tile(0, 5); 
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
