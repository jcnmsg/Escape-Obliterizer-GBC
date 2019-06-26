#include "../background/credits/credits.c"

void initCredits() {
	set_bkg_palette(0, 1, bkg_credits_palette); 
	set_bkg_data(0x01, 191, credits_dat);
	VBK_REG = 0;
	set_bkg_tiles(0, 0, 20, 18, credits_map);
	move_bkg (0, 0);
	SHOW_BKG;
    DISPLAY_ON;
}