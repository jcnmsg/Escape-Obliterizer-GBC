// GLOBAL VARIABLES NEEDED ACROSS STATES
extern int highscore;
int score = 0; 
int stun = 0;
int stunned = 0;
UINT8 state = 1;
UINT8 pDuty = 2;


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
        NR10_REG = 4 | (1 << 3) | (2 << 4); 
        NR11_REG = 1 | (3 << 6); 
        NR12_REG = 1 | (0 << 3) | (15 << 4); 
        NR13_REG = 0xFF & 1020; 
        NR14_REG = 0xC3; 
    }

    if (fx == 1) { // Stun sound fx 1 (Frequency: 1936)
        NR52_REG = 0x80; // Turn on sound registers, setting it to 0x00 turns them off
        NR51_REG = 0x22; // Select channel to use: 0x11 - 1, 0x22 - 2, 0x33 - 3, 0x88 - 4, 0xFF - All
        NR50_REG = 0x77; // Volume, min: 0x00, max: 0x77
        if (pDuty == 3) {
            NR21_REG = 0xC0; 
            pDuty = 2;
        }
        else if (pDuty == 2) {
            NR21_REG = 0x80; 
            pDuty = 3;
        }
        NR22_REG = 0x74; 
        NR23_REG = 0x90;
        NR24_REG = 0xC7;
    }

    if (fx == 2) {
        NR52_REG = 0x80; // Turn on sound registers, setting it to 0x00 turns them off
        NR51_REG = 0x88; // Select channel to use: 0x11 - 1, 0x22 - 2, 0x33 - 3, 0x88 - 4, 0xFF - All
        NR50_REG = 0x77; // Volume, min: 0x00, max: 0x77
        NR41_REG = 1;
        NR42_REG = 1 | (0 << 3) | (15 << 4);
        NR43_REG =  1 | (2 << 3) | (2 << 4);
        NR44_REG = (1 << 6) | (1 << 7);
    }
}

// VISUAL FX
void fadeout() {
    DISPLAY_OFF;
}

void fadein() {
    DISPLAY_ON;
}


void clearSpritePositions() {
    UINT8 i;
    for (i = 0; i < 30; i++ ){
        move_sprite(i, 200, 200);
    }
}