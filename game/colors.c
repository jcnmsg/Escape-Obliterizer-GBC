//SPRITES
#define RGB_LIGHTGREEN       RGB(16, 31, 27) 
#define RGB_DDARKGREEN       RGB(4, 18, 10)
#define RGB_LASERRED         RGB(31, 0, 0)
#define RGB_LASERVIOLET      RGB(25, 9, 29)
#define RGB_LASERDARKVIOLET  RGB(16, 7, 31)

//BG
#define RGB_VIOLET           RGB(7, 1, 6)
#define RGB_LIGHTVIOLET      RGB(11, 3, 10)
#define RGB_BGYELLOW         RGB(30, 30, 1)

const UWORD sprite_palettes[] = {
	0, RGB_LIGHTGREEN, RGB_DDARKGREEN, 0, // player sprite - regular skin
	0, RGB_LASERRED, RGB_LASERVIOLET, RGB_LASERDARKVIOLET // laser sprite
};

const UWORD bkg_palettes[] = {
    RGB_DDARKGREEN, RGB_LIGHTGREEN, RGB_LIGHTVIOLET, RGB_VIOLET, // bg menu palette and game
    RGB_VIOLET, RGB_VIOLET, RGB_VIOLET, RGB_VIOLET // bg menu palette and game
};

void initColors() {
    set_sprite_palette(0, 2, sprite_palettes); // Set sprite palettes to memory
    //set_bkg_palette(0, 2, bkg_palettes); // Set bg palettes to memory
}