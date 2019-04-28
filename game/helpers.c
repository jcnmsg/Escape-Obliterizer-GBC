// GLOBAL VARIABLES NEEDED ACROSS STATES
extern int highscore;
int score = 0; 
int stun = 0;
int stunned = 0;
UINT8 state = 1;

// GAMEPLAY
unsigned UINT8 generate_random_num(UINT8 upper) { // Generates random with upper as maximum
    unsigned UINT8 num;
    num = (rand() % (upper + 1) );
    return num;
}

void setDelay(UINT8 loops) {
    UINT8 i;
    for (i = 0; i < loops; i++){
        wait_vbl_done();
    }
}

// SOUND
void playSoundFX(UINT8 fx) {
    if (fx == 0) { // Laser blowing sound 
        NR52_REG = 0x80; // Turn on sound registers, setting it to 0x00 turns them off
        NR51_REG = 0x11; // Select channel to use: 0x11 - 1, 0x22 - 2, 0x33 - 3, 0x88 - 4, 0xFF - All
        NR50_REG = 0x77; // Volume, min: 0x00, max: 0x77
        
        NR10_REG = 0x1C; // Channel 1, Register 0 => Binary: 00001100
        NR11_REG = 0xC6; // Channel 1, Register 1 => Binary: 11000110 
        NR12_REG = 0x73; // Channel 1, Register 2 => Binary: 01110011
        NR13_REG = 0x00; // Channel 1, Register 3 => Binary: 00000000
        NR14_REG = 0xC3; // Channel 1, Register 4 => Binary: 11000011
    }
}

// VISUAL FX
void fadeout() {
    DISPLAY_OFF;
    //UINT8 i;
    /* NOT IN USE ANYMORE, DOESN'T WORK ON GBC, ONLY DMG AND POCKET
    for (i=0; i<4; i++) {
        if (i == 0) {
            BGP_REG = 0xE4; // Background palette
            OBP0_REG = 0xE4; // Sprite palette
        }
        if (i == 1) {
            BGP_REG = 0x90;
            OBP0_REG = 0x90;
        }
        if (i == 2) {
            BGP_REG = 0x80;
            OBP0_REG = 0x80;
        }
        if (i == 3) {
            BGP_REG = 0x00;
            OBP0_REG = 0x00;
        }
        setDelay(2);
    }*/
}

void fadein() {
    DISPLAY_ON;
    //UINT8 i;
    /* NOT IN USE ANYMORE, DOESN'T WORK ON GBC, ONLY DMG AND POCKET
    for (i=0; i<4; i++) {
        if (i == 0) {
            OBP0_REG = 0x00; // Sprite palette
            BGP_REG = 0x00; // Background palette
        }
        if (i == 1) {
            OBP0_REG = 0x80;
            BGP_REG = 0x80;
        }
        if (i == 2) {
            OBP0_REG = 0x90;
            BGP_REG = 0x90;
        }
        if (i == 3) {
            OBP0_REG = 0xE4; 
            BGP_REG = 0xE4;
        }
        setDelay(2);
    }*/
}

void clearSpritePositions() {
    UINT8 i;
    for (i = 0; i < 30; i++ ){
        move_sprite(i, 200, 200);
    }
}