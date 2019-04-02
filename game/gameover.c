// BACKGROUND
#include "../background/gameover/gameover.c"

// SPRITES
#include "../sprites/words/GameOverOptions.c"

const unsigned int *numbers[10] = {9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31};
const unsigned int *pos[6] = {0, 84, 90, 95, 101, 106};
UINT16 *digits[10] = {11, 11, 11, 11, 11, 11, 11, 11, 11, 11};

void drawYes() {
    UINT8 i;
    selected = 1;
    for (i = 0; i < 2; i++ ){
        set_sprite_tile(i, i + i);
        move_sprite(i, 75 + i*8, 115);
    }
}

void drawNo() {
    UINT8 i;
    selected = 0;
    for (i = 0; i < 2; i++ ){
        set_sprite_tile(i, i + i + 4);
        move_sprite(i, 92 + i*8, 115);
    }
}

void eraseOptions() {
    UINT8 i, z; 
    for (z = 0; z < 6; z++ ){
        move_sprite(z, 166 + z + 8, 144);
    }
    for (i = 0; i < 5; i++ ){
        move_sprite(i + 6, 166 + i + 8, 144);
    }
}

void drawScore(int count) {
    int i;
    for (i = 0; i < count; i++ ) {
        if (digits[i] != 11 ) {
            if ((int)digits[i] == 0) {
                set_sprite_tile(i + 2, 27);
            }
            else {
                set_sprite_tile(i + 2, numbers[(int)digits[i]-1]);
            }
            move_sprite(i + 2, (int)pos[count]-(11*i), 57);
        }
    }
}

void drawHighScore() {
    /*
        Retrieve score from volatile ram
        if (score > highscore) {
            draw score as highscore
            save current score to volatile ram
        }
        else {
            draw highscore from volatile ram
        }
    */
}

int reverseDigits(int num) {
    int rev_num = 0;
    while(num > 0){
        rev_num = rev_num*10 + num%10;
        num = num/10;
    }
    return rev_num;
}


void processScore() {
    UINT16 digit;
    int i, count, current_score;
    current_score = 698;
    
    count = 0;
    while (current_score != 0) {
        digit = current_score % 10;
        current_score /= 10;
        digits[count] = digit;
        count++;
    }

    count = 0;
    for (i = 9; i > 0; i-- ) {
        if (digits[i] != 11 ) {
            count++;
        }
    }

    drawScore(count);
    drawHighScore();
}

void initGameOver(){
    HIDE_SPRITES;
    set_bkg_palette(0, 1, gameoverbg_pal);
    set_bkg_data(0x01, gameoverbg_tiles, gameoverbg_dat);
    VBK_REG = 1;
    set_bkg_tiles(0, 0, gameoverbg_cols, gameoverbg_rows, gameoverbg_att);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, gameoverbg_cols, gameoverbg_rows, gameoverbg_map);
    move_bkg (0, 0);
    SHOW_BKG;
    processScore();
    set_sprite_data(0, 28, GameOverOptions); // Sets the yes sprite, starts on zero, counts twelve tiles
    drawYes();
    set_sprite_tile(39, 119); // empty player sprite
    SHOW_SPRITES;
    fadein();
}
