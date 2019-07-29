#include "../sprites/skins/big_skins.c"
#include "../sprites/skins/names/classic.c"
#include "../sprites/skins/names/delloween.c"
#include "../sprites/skins/names/gameboy.c"
#include "../sprites/skins/names/zipper.c"
#include "../sprites/skins/arrows.c"
#include "../background/skins/skins.c"

UINT8 selected_skin = 0;
const unsigned char *skinNames[4] = {GameBoySkinName, ClassicSkinName, DelloweenSkinName, ZipperSkinName};
const unsigned int *skinSize[4] = {10, 8, 12, 8};
const unsigned int *skinSpacing[4] = {68, 73, 65, 75};

void drawBigSprite() { // draw big skin with flipx
    UINT8 i;
    for (i = 0; i < 4; i++) {
        set_sprite_tile(i, i+i+(selected_skin*8));
        set_sprite_tile(i+4, i+i+(selected_skin*8));
        // Set according palettes
        if (selected_skin < 2) {
            set_sprite_prop(i, 0);
            set_sprite_prop(i+4, 0);
            set_sprite_prop(i+4, get_sprite_prop(i+4) | S_FLIPX);
        }
        if (selected_skin >= 2){
            set_sprite_prop(i, selected_skin + 1);
            set_sprite_prop(i+4, selected_skin + 1);
            set_sprite_prop(i+4, get_sprite_prop(i+4) | S_FLIPX);
        }
    }
    move_sprite(0, 76, 76); 
    move_sprite(1, 84, 76);    
    move_sprite(2, 76+(8*(2-2)), 92);
    move_sprite(3, 76+(8*(3-2)), 92);
    move_sprite(4, 76+(8*(4-2)), 76); 
    move_sprite(5, 76+(8*(5-4)), 76);
    move_sprite(6, 76+(8*(6-4)), 92);
    move_sprite(7, 76+(8*(7-6)), 92);
}

void drawSkinName() {
    UINT8 i, z;
    for (z = 0; z < ((UINT8) skinSize[selected_skin]) ; z++) {
        set_sprite_tile(8+z, 52+z+z); 
        move_sprite(8+z, ((UINT8) skinSpacing[selected_skin])+(z*8), 110);
        set_sprite_prop(8+z, 2);
    }
    for (i = ((UINT8) skinSize[selected_skin] - (UINT8) skinSize[selected_skin] / 2); i < 18; i++ ) {
        move_sprite(8+i, 180, 180);
        set_sprite_prop(8+i, 2);
    }
    set_sprite_data(52, skinSize[selected_skin], skinNames[selected_skin]);
}

void draw_selected_skin() {
    UINT8 i;
    for (i = 0; i <= 4; i++) {
        if (selected_skin == i) {
            drawBigSprite();
            drawSkinName();
        }
    }
    // Lightup the arrows
    if (selected_skin <= 0) {
        move_sprite(38, 190, 190);
    }
    if (selected_skin > 0) {
        move_sprite(38, 65, 84);
    }
    if (selected_skin < 3) {
        move_sprite(39, 103, 84);
    }
    if (selected_skin >= 3) {
        move_sprite(39, 190, 190);
    }
}

void init_skin_state() {
    set_bkg_palette(0, 1, bkg_palettes);
	set_bkg_data(0x01, 13, skins_dat);
	VBK_REG = 0;
	set_bkg_tiles(0, 2, 20, 13, skins_map);
	move_bkg (0, 0);
	SHOW_BKG;
    set_sprite_data(0, 54, BigSkins);
    set_sprite_data(80, 4, Arrows);
    set_sprite_tile(38, 80);
    set_sprite_prop(38, 2);
    set_sprite_tile(39, 82);
    set_sprite_prop(39, 2);
    draw_selected_skin();  
    DISPLAY_ON; 
}