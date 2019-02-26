#include <gb/gb.h>
#include <stdio.h> 
#include "sprites/player.c"
#include "background/backgroundmap.c"
#include "background/backgroundtiles.c"

void resetPlayerPosition(){
    set_sprite_tile(0, 6);
    move_sprite(0, 84, 80); 
}

void main(){
    set_bkg_data(0, 3, BackgroundTiles); // Sets which background tileset to use, starts on zero, counts three
    set_bkg_tiles(0, 0, 20, 18, BackgroundMap); // Sets which background map to use and position on screen starting on x=0, y=0 (offscreen) and spanning 20x18 tiles of 8 pixels each
    set_sprite_data(0, 7, Player); // Sets the player sprite, starts on zero, counts seven
    set_sprite_tile(0, 6); // Sets the tileset used by the player sprite
    move_sprite(0, 84, 80); // Moves sprite to desired position
    SHOW_BKG; // Draw background
    SHOW_SPRITES; // Draw sprites
 
    while(1){ 
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
    }
}

