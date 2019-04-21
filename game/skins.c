// SPRITES 
#include "../sprites/skins/big_skins.c"
#include "../sprites/skins/names/classic.c"
#include "../sprites/skins/names/delloween.c"
#include "../sprites/skins/names/gameboy.c"
#include "../sprites/skins/names/steve.c"
#include "../sprites/skins/names/zipper.c"
#include "../sprites/skins/arrows.c"

// BACKGROUNDS
#include "../background/skins/skins.c"

UINT8 selectedSkin = 0;
const unsigned char *skinNames[6] = {GameBoySkinName, ClassicSkinName, DelloweenSkinName, ZipperSkinName, SteveSkinName};
const unsigned int *skinSize[6] = {10, 8, 12, 8, 6};
const unsigned int *skinSpacing[6] = {68, 73, 65, 75, 77};

void drawBigSprite() { // draw big skin with flipx
    UINT8 i;
    for (i = 0; i < 4; i++) {
        set_sprite_tile(i, i+i+(selectedSkin*8));
        set_sprite_tile(i+4, i+i+(selectedSkin*8));
        // Set according palettes
        if (selectedSkin < 2) {
            set_sprite_prop(i, 0);
            set_sprite_prop(i+4, 0);
            set_sprite_prop(i+4, get_sprite_prop(i+4) | S_FLIPX);
        }
        if (selectedSkin >= 2){
            set_sprite_prop(i, selectedSkin + 1);
            set_sprite_prop(i+4, selectedSkin + 1);
            set_sprite_prop(i+4, get_sprite_prop(i+4) | S_FLIPX);
        }
    }
    for (i = 0; i <= 8; i++) {
        if (i < 2) {
            move_sprite(i, 76+(8*i), 76);    
        }
        if ( i == 2 || i == 3 ) {
            move_sprite(i, 76+(8*(i-2)), 92);
        }
        if ( i == 4 ) {
            move_sprite(i, 76+(8*(i-2)), 76); 
        }
        if ( i == 5 ) {
            move_sprite(i, 76+(8*(i-4)), 76);
        }
        if ( i == 6 ) {
            move_sprite(i, 76+(8*(i-4)), 92);
        }
        if ( i == 7 ) {
            move_sprite(i, 76+(8*(i-6)), 92);
        }
    }
}

void drawSkinName() {
    UINT8 i, z;
    set_sprite_data(52, skinSize[selectedSkin], skinNames[selectedSkin]);
    for (z = 0; z < ((UINT8) skinSize[selectedSkin]) ; z++) {
        set_sprite_tile(8+z, 52+z+z); 
        move_sprite(8+z, ((UINT8) skinSpacing[selectedSkin])+(z*8), 110);
        set_sprite_prop(8+z, 2);
    }
    for (i = ((UINT8) skinSize[selectedSkin] - (UINT8) skinSize[selectedSkin] / 2); i < 18; i++ ) {
        move_sprite(8+i, 180, 180);
        set_sprite_prop(8+i, 2);
    }
}

void drawSelectedSkin() {
    UINT8 i;
    for (i = 0; i <= 4; i++) {
        if (selectedSkin == i) {
            drawBigSprite();
            drawSkinName();
        }
    }
    // Lightup the arrows
    if (selectedSkin <= 0) {
        move_sprite(38, 190, 190);
    }
    if (selectedSkin > 0) {
        move_sprite(38, 65, 84);
    }
    if (selectedSkin < 4) {
        move_sprite(39, 103, 84);
    }
    if (selectedSkin >= 4) {
        move_sprite(39, 190, 190);
    }
}

void initSkinsState() {
    HIDE_SPRITES;
    set_bkg_palette(0, 1, bkg_palettes); // set bg palettes
	set_bkg_data(0x01, skins_tiles, skins_dat);
	VBK_REG = 1;
	set_bkg_tiles(0, 0, skins_cols, skins_rows, skins_att);
	VBK_REG = 0;
	set_bkg_tiles(0, 0, skins_cols, skins_rows, skins_map);
	move_bkg (0, 0);
	SHOW_BKG;
    set_sprite_data(0, 54, BigSkins);
    set_sprite_data(80, 4, Arrows);
    set_sprite_tile(38, 80);
    set_sprite_prop(38, 2);
    set_sprite_tile(39, 82);
    set_sprite_prop(39, 2);
    drawSelectedSkin();  
    SHOW_SPRITES;
    fadein(); 
}