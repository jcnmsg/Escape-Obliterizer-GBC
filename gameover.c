// BACKGROUND
#include "background/gameover/gameover.c"

// SPRITES
#include "sprites/words/GameOverOptions.c"

const unsigned int *numbers[10] = {4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26};

void drawYes() {
    UINT8 i;
    selected = 1;
    for (i = 0; i < 2; i++ ){
        set_sprite_tile(i, i + i);
        move_sprite(i, 75 + i*8, 115);
    }
}

void drawNo() {
    UINT8 i;
    selected = 0;
    for (i = 0; i < 2; i++ ){
        set_sprite_tile(i, i + i + 4);
        move_sprite(i, 92 + i*8, 115);
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

void initGameOver(){
    HIDE_SPRITES;
    set_bkg_palette(0, 1, gameoverbg_pal);
    set_bkg_data(0x01, gameoverbg_tiles, gameoverbg_dat);
    VBK_REG = 1;
    set_bkg_tiles(0, 0, gameoverbg_cols, gameoverbg_rows, gameoverbg_att);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, gameoverbg_cols, gameoverbg_rows, gameoverbg_map);
    move_bkg (0, 0);
    SHOW_BKG;
    set_sprite_data(0, 8, GameOverOptions); // Sets the yes sprite, starts on zero, counts twelve tiles
    drawYes();
    set_sprite_tile(39, 119); // empty player sprite
    SHOW_SPRITES;
    fadein();
}
