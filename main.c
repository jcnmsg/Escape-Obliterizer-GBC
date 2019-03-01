#include <gb/gb.h>
#include <stdio.h> 
#include <gb/font.h>
#include <gb/drawing.h>
#include <gb/console.h>
#include "sprites/player.c"
#include "background/backgroundmap.c"
#include "background/backgroundtiles.c"
#include "background/logo.c"

int score = 0;
int state = 1;

void resetPlayerPosition(){
    set_sprite_tile(0, 6);
    move_sprite(0, 84, 80); 
}

void initGameLoop(){
    set_bkg_data(39, 3, BackgroundTiles); // Sets which background tileset to use, starts on 39, after the font load, counts three tiles
    set_bkg_tiles(0, 0, 20, 18, BackgroundMap); // Sets which background map to use and position on screen starting on x=0, y=0 (offscreen) and spanning 20x18 tiles of 8 pixels each
    set_sprite_data(0, 7, Player); // Sets the player sprite, starts on zero, counts seven
    set_sprite_tile(0, 6); // Sets the tileset used by the player sprite
    move_sprite(0, 84, 80); // Moves sprite to desired position
    SHOW_SPRITES; // Draw sprites
}

void setDelay(UINT8 loops) {
    UINT8 i;
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
            VBK_REG = 1; // Sets the Video Bank Register. When set to zero, it loads the tile data into the background. When set to one, it loads the palette data into the background. You're supposed to set the palette data before you set the tile data. 
            set_bkg_tiles(0, 0, gbpic_cols, gbpic_rows, gbpic_att);
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
            switch(joypad()) { // Listens for user input
                case J_LEFT:
                    move_sprite(0, 44, 80); // Moves player sprite accordingly
                    set_sprite_tile(0, 3); // Sets the desired sprite tile to animate the eyes
                    break;
                case J_RIGHT:
                    move_sprite(0, 124, 80); 
                    set_sprite_tile(0, 4);
                    break;
                case J_UP:
                    move_sprite(0, 84, 40); 
                    set_sprite_tile(0, 4);
                    break;
                case J_DOWN:
                    move_sprite(0, 84, 120);
                    set_sprite_tile(0, 2); 
                    break;
                case J_SELECT:
                    waitpadup();
                    state = 4;
                default: 
                    resetPlayerPosition(); // If no key, resets player to the center
            }
            setDelay(2);
        }

        while (state == 3) { // 3: Game Over

        }

        while (state == 4) { // 4: Pause
            gotoxy(13, 16);
            printf("%s", "PAUSED");
            waitpad(J_SELECT);
            waitpadup();
            gotoxy(13, 16);
            printf("%s", "      "); 
            state = 2; 
        }

    }
}
