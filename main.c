// GBDK LIBRARY
#include <gb/gb.h>
#include <gb/cgb.h>
#include <gb/font.h>
#include <gb/drawing.h>
#include <gb/console.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <rand.h>
#include <time.h>

// FUNCTIONS
#include "game/colors.c" // CGB color palettes
#include "game/helpers.c" // General functions that are used throughout states (sound, visual fx, etc)
#include "game/menu.c" // Menu state specific functions
#include "game/credits.c" // Credits state specific functions
#include "game/skins.c" // Skins state specific functions
#include "game/gameover.c" // Game over state specific functions
#include "game/game.c" // Game state functions and initialization of a lot of the variables

extern UBYTE _cpu;

void main(){ // Main loop
    if (_cpu != 0x01 && _cpu != 0xFF) { // If running on MGB or prior models
        set_sprite_palette(0, 8, sprite_palettes);
        DISPLAY_ON;
        init_game_menu();
        while(1) {
            while(state == 0) { // 0: Credits
                switch(joypad()) { // Listens for user input
                    case J_A:
                        waitpadup();  
                        DISPLAY_OFF;
                        init_game_menu();
                        state = 1;
                        break;
                }
                wait_vbl_done();
            }

            while(state == 1){ // 1: Main Menu  
                switch(joypad()) { // Listens for user input
                    case J_UP:
                        draw_play();
                        waitpadup();
                        process_cheat_code(J_UP);
                        break;
                    case J_DOWN:
                        draw_credits();
                        waitpadup();
                        process_cheat_code(J_DOWN);
                        break;
                    case J_LEFT: 
                        waitpadup();
                        process_cheat_code(J_LEFT);
                        break;
                    case J_RIGHT: 
                        waitpadup();
                        process_cheat_code(J_RIGHT);
                        break;
                    case J_B: 
                        waitpadup();
                        process_cheat_code(J_B);
                        break;
                    case J_A:
                        waitpadup();
                        process_cheat_code(J_A);
                        if (key_count < 10) {
                            DISPLAY_OFF;
                            erase_menu_options();
                            if (selected == 1) {
                                init_game_loop(); // Loads sprites and backgrounds to VRAM
                                state = 2;
                            }
                            if (selected == 2){
                                init_credits();
                                state = 0;
                                selected = 1;
                            }
                        }
                        else {
                            DISPLAY_OFF;
                            erase_menu_options();
                            init_skin_state();
                            state = 5;
                        }
                        break;
                }
                wait_vbl_done();
            }

            while(state == 2){ // 2: Game Loop
                count_score();
                process_stun();
                start_hazards();

                // Colorize skins
                if (selected_skin < 2) {
                    set_sprite_prop(39, 0);
                }
                if (selected_skin >= 2){
                    set_sprite_prop(39, selected_skin + 1);
                }

                switch(joypad()) { // Listens for user input
                    case J_LEFT:
                        if (stunned == 0) {
                            if (stun <= 65) { 
                                stun++;
                                animate_stun_queue();
                                move_sprite(39, 44, 80); // Moves player sprite accordingly
                                move_sprite(37, 40, 76); // move stun queue
                                move_sprite(38, 48, 76); // move stun queue
                                player_x = 44;
                                player_y = 80;
                                if (selected_skin == 0) {
                                    set_sprite_tile(39, 3); // Sets the desired sprite tile to animate the eyes
                                }
                            }
                            else {
                                stunned = 1;
                                stun = 0;
                                reset_player_position();
                            } 
                        }
                        break;
                    case J_RIGHT: 
                        if (stunned == 0) {
                            if (stun <= 65) {
                                stun++; 
                                animate_stun_queue();
                                move_sprite(39, 124, 80); 
                                move_sprite(37, 120, 76); // move stun queue
                                move_sprite(38, 128, 76); // move stun queue
                                player_x = 124;
                                player_y = 80;
                                if (selected_skin == 0) {
                                    set_sprite_tile(39, 9);
                                }
                            }
                            else {
                                stunned = 1;
                                stun = 0;
                                reset_player_position();
                            }

                        }
                        break;
                    case J_UP:
                        if (stunned == 0) {
                            if (stun <= 65) {
                                stun++;
                                animate_stun_queue();
                                move_sprite(39, 84, 40); // move player sprite
                                move_sprite(37, 80, 36); // move stun queue
                                move_sprite(38, 88, 36); // move stun queue
                                player_x = 84;
                                player_y = 40;
                                if (selected_skin == 0) {
                                    set_sprite_tile(39, 9);
                                }
                            }
                            else {
                                stunned = 1;
                                stun = 0;
                                reset_player_position();
                            }
                        }
                        break;
                    case J_DOWN:
                        if (stunned == 0) {
                            if (stun <= 65) {
                                stun++;
                                animate_stun_queue();
                                move_sprite(39, 84, 120);
                                move_sprite(37, 80, 116); // move stun queue
                                move_sprite(38, 88, 116); // move stun queue
                                player_x = 84;
                                player_y = 120;
                                if (selected_skin == 0) {
                                    set_sprite_tile(39, 5); 
                                }
                            }
                            else {
                                stunned = 1;
                                stun = 0;
                                reset_player_position();
                            }
                        }
                        break;
                    case J_START:
                        waitpadup();
                        state = 4;
                    default: 
                        reset_player_position(); // If no key, resets player to the center
                }
                is_vlaser_ready_to_blow();
                is_hlaser_ready_to_blow();
                is_bomb_ready_to_blow();
                set_delay(2);
            }

            while (state == 3) { // 3: Game Over
                switch(joypad()) { // Listens for user input
                    case J_LEFT:
                        draw_yes();
                        break;
                    case J_RIGHT:
                        draw_no(); 
                        break;
                    case J_A:
                        waitpadup();
                        clear_sprite_positions();
                        score = 0;
                        if (selected == 1) {
                            DISPLAY_OFF;
                            init_game_loop();
                            state = 2;
                        }
                        if (selected == 0){
                            DISPLAY_OFF;
                            init_game_menu();
                            state = 1;
                        }
                        break;
                }
                wait_vbl_done();
            }

            while (state == 4) { // 4: Pause
                gotoxy(13, 16);
                printf("%s", "PAUSED");
                waitpad(J_START);
                waitpadup();
                gotoxy(13, 16);
                printf("%s", "      "); 
                state = 2; 
            }

            while (state == 5) {
                switch(joypad()) { // Listens for user input
                    case J_LEFT: 
                        waitpadup();
                        if (selected_skin > 0) {
                            selected_skin--;
                            draw_selected_skin();
                        }
                        break;
                    case J_RIGHT: 
                        waitpadup();
                        if (selected_skin < 3) {
                            selected_skin++;
                            draw_selected_skin();
                        }
                        break;
                    case J_B: 
                        waitpadup();
                        selected_skin = 0;
                        key_count = 0;
                        DISPLAY_OFF;
                        init_game_menu();
                        state = 1;
                        break;
                    case J_A:
                        waitpadup();
                        key_count = 0;
                        DISPLAY_OFF;
                        init_game_menu();
                        state = 1;
                        break;
                }
                set_delay(2);
            }
        } 
    }
}
