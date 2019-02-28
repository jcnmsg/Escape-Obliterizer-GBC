#include <gb/gb.h>
#include <stdio.h> 
#include <gb/font.h>
#include <gb/drawing.h>
#include "sprites/player.c"
#include "background/backgroundmap.c"
#include "background/backgroundtiles.c"
#include "background/logo.c"

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

void main(){
    int score = 0;
    int state = 0;
     
    while(state == 0){ // 0: Main Menu 
        set_bkg_palette(0, 1, gbpic_pal);
        set_bkg_data(0x01, gbpic_tiles, gbpic_dat);
        VBK_REG = 1; // Sets the Video Bank Register. When set to zero, it loads the tile data into the background. When set to one, it loads the palette data into the background. You're supposed to set the palette data before you set the tile data. 
        set_bkg_tiles(0, 0, gbpic_cols, gbpic_rows, gbpic_att);
        VBK_REG = 0; // Sets the Video Bank Register. When set to zero, it loads the tile data into the background. When set to one, it loads the palette data into the background. You're supposed to set the palette data before you set the tile data. 
        set_bkg_tiles(0, 0, gbpic_cols, gbpic_rows, gbpic_map);
        SHOW_BKG; // Draw background
        DISPLAY_ON; // Turn on display
        waitpad(J_START); // Wait for Start Key
        waitpadup(); // Wait for release
        initGameLoop();
        state = 1;
    }

    while(state == 1){ // 1: Game Loop
        switch(joypad()) { // Listens for user input
            case J_LEFT:
                move_sprite(0, 44, 80); // Moves player sprite accordingly
                set_sprite_tile(0, 3); // Sets the desired sprite tile to animate the eyes
                waitpadup(); // Waits for the user to release the pressed key
                resetPlayerPosition(); // Resets the player position back to the center
                break;
            case J_RIGHT:
                move_sprite(0, 124, 80); 
                set_sprite_tile(0, 4);
                waitpadup();
                resetPlayerPosition();
                break;
            case J_UP:
                move_sprite(0, 84, 40); 
                set_sprite_tile(0, 4);
                waitpadup();
                resetPlayerPosition();
                break;
            case J_DOWN:
                move_sprite(0, 84, 120);
                set_sprite_tile(0, 2); 
                waitpadup();
                resetPlayerPosition();
                break;
        }
        setDelay(2);
    }
}

