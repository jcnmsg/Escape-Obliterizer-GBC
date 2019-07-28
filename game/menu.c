#include "../background/logo/logo.c"
#include "../sprites/words/MenuOptions.c"

UINT8 selected = 1; 
UINT8 key_count = 0;
const unsigned char *cheat_code[10] = {J_UP, J_UP, J_DOWN, J_DOWN, J_LEFT, J_RIGHT, J_LEFT, J_RIGHT, J_B, J_A};

void process_cheat_code(unsigned char key) {
    if (key_count < 10) {
        if (key == cheat_code[key_count]) {
            key_count++;
        }
        else {
            key_count = 0;
        }
    }
}

void draw_play() {
    UINT8 i;
    selected = 1;
    set_sprite_tile(5, 199);
    for (i = 0; i < 5; i++ ){
        set_sprite_tile(i, i + i);
        move_sprite(i, 133 + i*8, 113);
        set_sprite_prop(i, 2);
    }
}

void draw_credits() {
    UINT8 i;
    selected = 2;
    for (i = 0; i < 6; i++ ){
        set_sprite_tile(i, i + i + 10);
        move_sprite(i, 120 + i*8, 123);
        set_sprite_prop(i, 2);
    }
}

void erase_menu_options() {
    UINT8 i;
    for (i = 0; i < 12; i++ ){
        set_sprite_tile(i, i + i);
        move_sprite(i, 166 + i + 8, 144);
    }
}

void remove_skin_state(){
    UINT8 w, z;
    for (z = 0; z <= 39 ; z++) { 
        move_sprite(z, 180, 180);    
    }
    for (w = 0; w <= 39; w++) {
        set_sprite_prop(w, 0x00);
    }
}

void init_game_menu() {
    remove_skin_state();
    set_bkg_palette(0, 1, &bkg_palettes[0]); // set bg palettes
	set_bkg_data(0x01, 77, gbpic_dat); 
	VBK_REG = 0;
	set_bkg_tiles(0, 0, 20, 18, gbpic_map);
	move_bkg (0, 0);
	SHOW_BKG;
    SPRITES_8x16; // Activate 8*16 sprite mode, defaults to 8x8
    set_sprite_data(0, 22, MenuOptions);
    draw_play();
    SHOW_SPRITES; // Draw sprites
    DISPLAY_ON;
}