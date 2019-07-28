#include "../background/gameover/gameover.c"
#include "../sprites/words/GameOverOptions.c"

const unsigned int *numbers[10] = {9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31};
const unsigned int *pos[6] = {0, 84, 90, 95, 101, 106};
UINT16 *digits[10] = {11, 11, 11, 11, 11, 11, 11, 11, 11, 11};

void clear_digits() {
    UINT8 i;
    for (i = 0; i < 10; i++ ) {
        digits[i] = 11;
    }
}

void draw_yes() {
    UINT8 i;
    selected = 1;
    for (i = 0; i < 2; i++ ){
        set_sprite_tile(i, i + i);
        move_sprite(i, 75 + i*8, 115);
        set_sprite_prop(i, 2);
    }
}

void draw_no() {
    UINT8 i;
    selected = 0;
    for (i = 0; i < 2; i++ ){
        set_sprite_tile(i, i + i + 4);
        move_sprite(i, 92 + i*8, 115);
        set_sprite_prop(i, 2);
    }
}

void draw_score(int count) {
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
            set_sprite_prop(i + 2, 2);
        }
    }
}

void draw_highscore() {
    UINT16 digit;
    int i, count, current_highscore;
    current_highscore = highscore;
    clear_digits(); 

    count = 0;
    while (current_highscore != 0) {
        digit = current_highscore % 10;
        current_highscore /= 10;
        digits[count] = digit;
        count++;
    }

    count = 0;
    for (i = 9; i > 0; i-- ) {
        if (digits[i] != 11 ) {
            count++;
        }
    }

    for (i = 0; i < count; i++ ) {
        if (digits[i] != 11 ) {
            if ((int)digits[i] == 0) {
                set_sprite_tile(i + 2 + 20, 27);
            }
            else {
                set_sprite_tile(i + 2 + 20, numbers[(int)digits[i]-1]);
            }
            move_sprite(i + 2 + 20, (int)pos[count]-(11*i), 86);
            set_sprite_prop(i + 2 + 20, 2); 
        }
    }
}

void process_highscore() {
    ENABLE_RAM_MBC1; // Open nvram

    if ((score - 1) > highscore) { // If current score larger than highscore
        highscore = score - 1; // Save current score to nvram
    } 
    draw_highscore();

    DISABLE_RAM_MBC1; // Close nvram
}

void process_score() {
    UINT16 digit;
    int i, count, current_score;
    current_score = score - 1;
    clear_digits(); 

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

    draw_score(count);
    process_highscore();
}

void init_game_over(){
    HIDE_SPRITES;
    set_bkg_palette(0, 1, bkg_gameover_palette); // set bg palettes
    set_bkg_data(0x01, 60, gameoverbg_dat);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, 20, 18, gameoverbg_map);
    move_bkg (0, 0);
    SHOW_BKG;
    clear_sprite_positions();
    set_sprite_tile(36, 119); // empty stun anim sprite
    set_sprite_tile(37, 119); // empty stun queue
    set_sprite_tile(38, 119); // empty stun queue
    set_sprite_tile(39, 119); // empty player sprite
    process_score();
    set_sprite_data(0, 28, GameOverOptions); // Sets the yes sprite, starts on zero, counts twelve tiles
    draw_yes();
    SHOW_SPRITES;
    DISPLAY_ON;
}
