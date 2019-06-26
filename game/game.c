// GAME BACKGROUNDS
#include "../background/game/backgroundmap.c"
#include "../background/game/backgroundtiles.c"

// GAME SPRITES
#include "../sprites/player.c"
#include "../sprites/verticallaser.c"
#include "../sprites/horizontallaser.c"
#include "../sprites/lasergun.c"
#include "../sprites/bomblaser.c"
#include "../sprites/stun.c"
#include "../sprites/stunqueue.c"
#include "../sprites/explosion.c"

struct Laser {
    UBYTE repetitions[10];
}

UINT8 hLaser;
UINT8 hLaserReady = 1;
UINT8 hLaserPos, hCurrentClock;
 
struct Laser vLaser;
UINT8 vLaserReady = 1; 
UINT8 vLaserPos, vCurrentClock;

UINT8 bReady = 1;
UINT8 bPos, bCurrentClock;

UINT8 playerX, playerY;
font_t ibm;// Declare font variable

void countScore() {
    gotoxy(1, 16); // Position of the console on screen, uses tiles so x=1*8 and y=16*8
    printf("%u", score++); // Print score at desired position
}

void resetPlayerPosition(){
    UINT8 w;
    for (w = 0; w <= 5; w++) {
        if (w == selectedSkin) {
            set_sprite_tile(39, 11+w+w);
            if (selectedSkin < 2) {
                set_sprite_prop(39, 0);
            }
            if (selectedSkin >= 2){
                set_sprite_prop(39, selectedSkin + 1);
            }
        }
    }
        
    set_sprite_tile(37, 48);
    set_sprite_prop(37, 7);
    set_sprite_tile(38, 48);
    set_sprite_prop(38, get_sprite_prop(37) | S_FLIPX);
    
    move_sprite(37, 200, 200); //hide stun queue
    move_sprite(38, 200, 200); //hide reversed stun queue

    move_sprite(39, 84, 80); // reset player

    playerX = 84;
    playerY = 80;
    if (stunned == 0)  {
        stun = 0;
    }
}

void initGameLoop(){
    font_init(); // Initialize font library after state change to avoid overwriting bg tiles
    color(DKGREY, BLACK, SOLID); // Customize colors of font 
    ibm = font_load(font_ibm); // Load built in font_ibm
    font_set(ibm); // Set built in font_ibm, will be used on displaying the score, only 36 tiles
    set_bkg_palette(0, 1, bkg_game_palette);
    set_bkg_data(109, 6, BackgroundTiles); // Sets which background tileset to use, starts on 39, after the font load, counts three tiles
    set_bkg_tiles(0, 0, 20, 18, BackgroundMap); // Sets which background map to use and position on screen starting on x=0, y=0 (offscreen) and spanning 20x18 tiles of 8 pixels each
    set_sprite_data(0, 30, Player); // Sets the player sprite, starts on zero, counts seven
    set_sprite_data(30, 18, VerticalLaser); // Sets the vertical laser sprites
    set_sprite_data(94, 4, HorizontalLaser); // Sets the horizontal laser sprites
    set_sprite_data(100, 12, LaserGun); // Sets the laser gun sprites
    set_sprite_data(48, 8, StunQueue); // Sets the stun queue sprites
    set_sprite_data(58, 10, TheStun); // Sets the stun sprites
    set_sprite_prop(36, 6); // Setup stun animation colors
    set_sprite_data(68, 6, BombLaser); // Sets the bomb laser sprites
    set_sprite_data(76, 14, Explosion); // Sets the explosion sprites
    set_sprite_prop(17, 6);
    set_sprite_prop(18, get_sprite_prop(17) | S_FLIPX);
    SHOW_SPRITES; // Draw sprites
    resetPlayerPosition();
    DISPLAY_ON;
    stun = 0;
    stunned = 0;
    pDuty = 2;
}
 
void drawTheVLaser(struct Laser* laser, UINT8 x, UINT8 y) {
    UINT8 i; 
    for (i = 1; i < 10; i++ ){ 
        move_sprite(laser->repetitions[i], x, y + (16 * i));
    } 
}

void drawTheHLaser(UINT8 x, UINT8 y) {
    UINT8 i;
    if (y == 36 || y == 116) {
        move_sprite(19, 84, y);
    }
    else if (y == 76) {
        for(i = x; i < 3; i++){
            move_sprite(19 + i, 44 + (i*40), y);
        }
    }
}

void drawTheBomb(UINT8 x, UINT8 y) {
    UINT8 i; 
    for(i = 0; i < 8; i++){
        if (i == 0) {
            move_sprite(9+i, x - 16, y - 20);
        }
        if (i == 1) {
            move_sprite(9+i, x - 8 , y - 20);
        }
        if (i == 2) {
            move_sprite(9+i, x + 16, y - 20);
        }
        if (i == 3) {
            move_sprite(9+i, x + 8 , y - 20);
        }
        if (i == 4) {
            move_sprite(9+i, x - 16, y + 12);
        }
        if (i == 5) {
            move_sprite(9+i, x - 8 , y + 12);
        }
        if (i == 6) {
            move_sprite(9+i, x + 16, y + 12);
        }
        if (i == 7) {
            move_sprite(9+i, x + 8 , y + 12);
        }
    }
}

void triggerVLaser(UINT8 x) { // Trigger Vertical Laser, only requires x coordinate, y = 0
    UINT8 i;
    vLaserPos = x;
    vCurrentClock = (clock() / CLOCKS_PER_SEC);
    for(i = 0; i < 9; i++){
        vLaser.repetitions[i] = i;
        set_sprite_tile(i, 30);
        set_sprite_prop(i, 1);
    }
    drawTheVLaser(&vLaser, x, 0);
}

void triggerHLaser(UINT8 y) { // Trigger Horiziontal Laser, only requires y coordinate, x = 0
    UINT8 i;
    hLaserPos = y;
    hCurrentClock = (clock() / CLOCKS_PER_SEC);
    if (y == 36 || y == 116) {
        set_sprite_tile(19, 94);
        set_sprite_prop(19, 1);
        if (y == 36) {
           // set_bkg_tiles(0,3,20,1, LaserBgMapSingleBase);
        }
        if (y == 116) {
           // set_bkg_tiles(0,13,20,1, LaserBgMapSingleBase);
        }
    }
    else if (y == 76) {
        for(i = 0; i < 3; i++){
            set_sprite_tile(19 + i, 94);
            set_sprite_prop(19 + i, 1);
            //set_bkg_tiles(0,8,20,1, LaserBgMapDualBase);
        }
    }
    
    drawTheHLaser(0, y);
}


void triggerBomb(UINT8 x) {
    UINT8 i;
    bPos = x;
    bCurrentClock = (clock() / CLOCKS_PER_SEC);
    for(i = 0; i < 8; i++){
        if (i < 2) {
            set_sprite_tile(9+i, 68+i+i);
        }
        if (i >= 2 && i < 4) {
            set_sprite_tile(9+i, 68+i+i-2-2);
        }
        if (i >= 4 && i < 6) {
            set_sprite_tile(9+i, 68+i+i-4-4);
        }
        if (i >= 6 && i < 8) {
            set_sprite_tile(9+i, 68+i+i-6-6);
        }
        set_sprite_prop(9+i, 1);
        if (i >= 2 && i < 4) {
            set_sprite_prop(9+i, get_sprite_prop(9+i) | S_FLIPX);
        }
        if (i >=4 && i < 6) {
            set_sprite_prop(9+i, get_sprite_prop(9+i) | S_FLIPY);
        }
        if (i>=6){
            set_sprite_prop(9+i, get_sprite_prop(9+i) | S_FLIPX | S_FLIPY);
        }
    }
    drawTheBomb(x, 80);
}

void isVLaserReadyToBlow() {
    UINT8 i, z;
    if ( (clock() / CLOCKS_PER_SEC) - vCurrentClock >= 1 && vLaserReady == 0 && state !=3 ) {
        playSoundFX(0);
        for (z = 2; z < 20; z+=2) {
            for(i = 0; i < 9; i++){
                vLaser.repetitions[i] = i;
                set_sprite_tile(i, 28+z);
            }
            drawTheVLaser(&vLaser, vLaserPos, 0);
            set_delay(2);
        }
        if (playerX == vLaserPos) {
            for (i = 0; i <= 5; i++) {
                set_sprite_tile(39, 23+i);
                set_delay(3);
            }
            DISPLAY_OFF;
            playerX = 0;
            initGameOver();
            state = 3;
        }
        vLaserReady = 1;
    }
    else if (state == 3) {
        vLaserReady = 1;
    }
}



void isHLaserReadyToBlow() {
    UINT8 i;
    if ( (clock() / CLOCKS_PER_SEC) - hCurrentClock >= 1 && hLaserReady == 0 && state !=3 ) {
        playSoundFX(3);
        for (i = 0; i < 3; i++) {
            set_sprite_tile(19+i, 120, 120);
        }
        // animate hazard
        for (i = 0; i < 14; i++) {
            set_delay(2);
        }
        if (playerY == hLaserPos + 4) {
            for (i = 0; i <= 5; i++) {
                set_sprite_tile(39, 23+i);
                set_delay(3);
            }
            DISPLAY_OFF;
            playerY = 0;
            initGameOver();
            state = 3;
        }
        hLaserReady = 1;
    }
    else if (state == 3) {
        hLaserReady = 1;
    }
}

void isBombReadyToBlow() {
    UINT8 i;
    if ( (clock() / CLOCKS_PER_SEC) - bCurrentClock >= 1 && bReady == 0 && state != 3) {
        playSoundFX(2);
        set_sprite_tile(17, 76);
        set_sprite_tile(18, 76);
        move_sprite(17, bPos-4, 76); // reset player
        move_sprite(18, bPos+4, 76); // reset player
        for(i = 9; i < 17; i++ ) {
            move_sprite(i, 200, 200);
        }
        for(i = 0; i < 18; i+=2){
            set_sprite_tile(17, 76+i);
            set_sprite_tile(18, 76+i);
            set_delay(2);
        }
        if (playerX == bPos) {
            for (i = 0; i <= 5; i++) {
                set_sprite_tile(39, 23+i);
                set_delay(3);
            }
            DISPLAY_OFF;
            playerX = 0;
            initGameOver();
            state = 3;
        }
        bReady = 1;
    }
    else if (state == 3) {
        bReady = 1;
    }
}

void callVLaser(){
    unsigned UINT8 pos = generate_random_num(3);
    if (pos == 0) {
        vLaserReady = 0;
        triggerVLaser(44);
    }
    else if (pos == 1) {
        vLaserReady = 0;
        triggerVLaser(84);
    }
    else if (pos == 2) {
        vLaserReady = 0;
        triggerVLaser(124);
    }
    else if (pos == 3) {
        vLaserReady = 1;
    }
}

void callBomb() {
    unsigned UINT8 pos = generate_random_num(2);
    if (pos == 0) {
        bReady = 0;
        triggerBomb(44);
    }
    else if (pos == 1) {
        bReady = 0;
        triggerBomb(124);
    }
    else if (pos == 2) {
        bReady = 1;
    }
}

void callHLaser() {
    unsigned UINT8 pos = generate_random_num(3);
    if (pos == 0) {
        hLaserReady = 0;
        triggerHLaser(36);
    }
    else if (pos == 1) {
        hLaserReady = 0;
        triggerHLaser(76);
    }
    else if (pos == 2) {
        hLaserReady = 0;
        triggerHLaser(116);
    }
    else if (pos == 3) {
        hLaserReady = 1;
    }
}

void startHazards() {
    unsigned UINT8 hazard;
    if ( ((clock() / CLOCKS_PER_SEC)) % 2 == 0) { // change for timer 
        hazard = generate_random_num(2);
        if (hazard == 0 && vLaserReady == 1) {
            callVLaser();
        }
        else if (hazard == 1 && hLaserReady == 1) {
            callHLaser();
        }
        else if (hazard == 2 && bReady == 1) {
            callBomb();
        }
    }
}

void playStunAnimation() {
    move_sprite(36, 85, 78);
    if ((stun > 0 && stun <= 5) || (stun > 25 && stun <= 30) || (stun > 50 && stun <= 55) ) {
        set_sprite_tile(36, 58);
    }
    if ((stun > 5 && stun <= 10) || (stun > 30 && stun <= 35) || (stun > 55 && stun <= 60)) {
        set_sprite_tile(36, 60);
    }
    if ((stun > 10 && stun <= 15) || (stun > 35 && stun <= 40) || (stun > 60 && stun <= 65)) {
        set_sprite_tile(36, 62);
    }
    if ((stun > 15 && stun <= 20) || (stun > 40 && stun <= 45) || (stun > 65 && stun <= 70)) {
        set_sprite_tile(36, 64);
    }
    if ((stun >= 20 && stun <= 25) || (stun > 45 && stun <= 50) || (stun > 70 && stun <= 75)) {
        set_sprite_tile(36, 66);
    }
    if (stun == 1 || stun == 12 || stun == 40 || stun == 52) {
        playSoundFX(1);
    }
}

void processStun() {
    if (stunned == 1) {
        playStunAnimation();
        if(stun <= 75){ 
            stun++;
        }
        else {
            stunned = 0;
            stun = 0;
            move_sprite(36, 200, 200); // hide stun sprite on stun finish
        }
    } 
}

void animateStunQueue(){
    if (stun > 0 && stun < 20) {
        set_sprite_tile(37, 50);
        set_sprite_tile(38, 50);
    }
    if (stun >=20 && stun < 40) {
        set_sprite_tile(37, 52);
        set_sprite_tile(38, 52);
    } 
    if (stun >=40 && stun < 60) {
        set_sprite_tile(37, 54);
        set_sprite_tile(38, 54);
    } 
    if (stun >= 60 && stun < 80) {
        set_sprite_tile(37, 119);
        set_sprite_tile(38, 119);
    }
    score+=3;
}