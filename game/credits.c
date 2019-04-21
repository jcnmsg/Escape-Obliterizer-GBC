// BACKGROUND
#include "../background/credits/credits.c"

void initCredits() {
	set_bkg_palette(0, 1, bkg_credits_palette); // set bg palettes
	set_bkg_data(0x01, credits_tiles, credits_dat);
	VBK_REG = 1;
	set_bkg_tiles(0, 0, credits_cols, credits_rows, credits_att);
	VBK_REG = 0;
	set_bkg_tiles(0, 0, credits_cols, credits_rows, credits_map);
	move_bkg (0, 0);
	SHOW_BKG;
    fadein();
}