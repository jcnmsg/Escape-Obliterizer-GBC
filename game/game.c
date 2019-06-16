// GAME BACKGROUNDS
#include "../background/game/backgroundmap.c"
#include "../background/game/backgroundtiles.c"

// GAME SPRITES
#include "../sprites/player.c"
#include "../sprites/verticallaser.c"
#include "../sprites/stun.c"
#include "../sprites/stunqueue.c"

struct Laser {
    UBYTE repetitions[10];
}

struct Laser hLaser;
UINT8 hLaserReady = 1;
UINT8 hLaserPos, hCurrentClock;
 
struct Laser vLaser;
UINT8 vLaserReady = 1; 
UINT8 vLaserPos, vCurrentClock;

UINT8 bReady = 1;
UINT8 bPos, bCurrentClock;

UINT8 playerX, playerY;

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
    font_t ibm; // Declare font variable
    font_init(); // Initialize font library after state change to avoid overwriting bg tiles
    color(DKGREY, BLACK, SOLID); // Customize colors of font 
    ibm = font_load(font_ibm); // Load built in font_ibm
    font_set(ibm); // Set built in font_ibm, will be used on displaying the score, only 36 tiles
    set_bkg_data(109, 3, BackgroundTiles); // Sets which background tileset to use, starts on 39, after the font load, counts three tiles
    set_bkg_tiles(0, 0, 20, 18, BackgroundMap); // Sets which background map to use and position on screen starting on x=0, y=0 (offscreen) and spanning 20x18 tiles of 8 pixels each
    set_sprite_data(0, 30, Player); // Sets the player sprite, starts on zero, counts seven
    set_sprite_data(30, 18, VerticalLaser); // Sets the vertical laser sprites
    set_sprite_data(48, 8, StunQueue); // Sets the stun queue sprites
    set_sprite_data(58, 10, TheStun); // Sets the stun sprites
    set_sprite_prop(36, 6); // Setup stun animation colors

    SHOW_SPRITES; // Draw sprites
    resetPlayerPosition();
    fadein();
    stun = 0;
    stunned = 0;
}
 
void drawTheVLaser(struct Laser* laser, UINT8 x, UINT8 y) {
    UINT8 i; 
    for (i = 1; i < 10; i++ ){ 
        move_sprite(laser->repetitions[i], x, y + (16 * i));
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

void isVLaserReadyToBlow() {
    UINT8 i, z;
    if ( (clock() / CLOCKS_PER_SEC) - vCurrentClock >= 1 && vLaserReady == 0 ) {
        playSoundFX(0);
        for (z = 2; z < 20; z+=2) {
            for(i = 0; i < 9; i++){
                vLaser.repetitions[i] = i;
                set_sprite_tile(i, 28+z);
            }
            drawTheVLaser(&vLaser, vLaserPos, 0);
            setDelay(2);
        }
        if (playerX == vLaserPos) {
            for (i = 0; i <= 5; i++) {
                set_sprite_tile(39, 23+i);
                setDelay(3);
            }
            fadeout();
            initGameOver();
            state = 3;
        }
        vLaserReady = 1;
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

void startHazards() {
    unsigned UINT8 hazard;
    if ( (int)((clock() / CLOCKS_PER_SEC)) % 2 == 0) { // change for timer 
        hazard = generate_random_num(2);
        if (hazard == 0 && vLaserReady == 1) {
            callVLaser();
        }
        else if (hazard == 1 && hLaserReady == 1) {
            //callHLaser();
            printf("");
        }
        else if (hazard == 2 && bReady == 1) {
            printf("");
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