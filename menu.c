// BACKGROUND
#include "background/logo/logo.c"

// SPRITES
#include "sprites/words/MenuOptions.c"

// VARIABLES
UINT8 selected = 1; 
UINT8 keyCount = 0;
const unsigned char *cheatCode[10] = {J_UP, J_UP, J_DOWN, J_DOWN, J_LEFT, J_RIGHT, J_LEFT, J_RIGHT, J_B, J_A};

void processCheatCode(unsigned char key) {
    if (keyCount < 10) {
        if (key == cheatCode[keyCount]) {
            keyCount++;
        }
        else {
            keyCount = 0;
        }
    }
}

void drawPlay() {
    UINT8 i;
    selected = 1;
    set_sprite_tile(5, 199);
    for (i = 0; i < 5; i++ ){
        set_sprite_tile(i, i + i);
        move_sprite(i, 133 + i*8, 113);
    }
}

void drawCredits() {
    UINT8 i;
    selected = 2;
    for (i = 0; i < 6; i++ ){
        set_sprite_tile(i, i + i + 10);
        move_sprite(i, 120 + i*8, 123);
    }
}

void eraseMenuOptions() {
    UINT8 i;
    for (i = 0; i < 12; i++ ){
        set_sprite_tile(i, i + i);
        move_sprite(i, 166 + i + 8, 144);
    }
}

void remSkinsState(){
    UINT8 w, z;
    for (z = 0; z <= 39 ; z++) { 
        move_sprite(z, 180, 180);    
    }
    for (w = 0; w <= 39; w++) {
        set_sprite_prop(w, 0x00);
    }
}

void initGameMenu() {
    fadeout();
    remSkinsState();
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
    set_sprite_data(0, 22, MenuOptions);
    drawPlay();
    SHOW_SPRITES;
    fadein(); 
}