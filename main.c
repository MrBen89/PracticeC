#include <gb/gb.h>
#include <stdio.h>
#include "slime.c"
#include "background.c"
#include "backgroundsheet.c"
#include "windowmap.c"
#include <gbdk/font.h>


void main(){
    UINT8 currentSpriteIndex = 0;
    font_t min_font;

    //Register order matters
    NR52_REG = 0x80; //turns on sound
    NR50_REG = 0x77; // sets volume to max for left and right channel
    NR51_REG = 0xFF; // turns on all 4 channels left and right

    font_init();
    min_font = font_load(font_min); //36 tiles
    font_set(min_font);

    set_bkg_data(37, 7, BackgroundTile); //load after font data
    set_bkg_tiles(0, 0, 40, 18, BackgroundSheet);

    set_win_tiles(0, 0, 5, 1, WindowMap);
    move_win(7,120);

    set_sprite_data(0, 2, Slime);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;
    SHOW_BKG;
    SHOW_WIN;
    DISPLAY_ON;

    while(1){
        scroll_bkg(1,0);
        switch(joypad()){
                case J_LEFT:
                    scroll_sprite(0, -10, 0);
                    NR10_REG = 0x16;
                    NR11_REG = 0x40;
                    NR12_REG = 0x73;
                    NR13_REG = 0x00;
                    NR14_REG = 0xc3;
                    break;
                case J_RIGHT:
                    scroll_sprite(0, 10, 0);
                    NR10_REG = 0x16;
                    NR11_REG = 0x40;
                    NR12_REG = 0x73;
                    NR13_REG = 0x00;
                    NR14_REG = 0xc3;
                    break;
                case J_UP:
                    scroll_sprite(0, 0, -10);
                    NR10_REG = 0x16;
                    NR11_REG = 0x40;
                    NR12_REG = 0x73;
                    NR13_REG = 0x00;
                    NR14_REG = 0xc3;
                    break;
                case J_DOWN:
                    scroll_sprite(0, 0, 10);
                    NR10_REG = 0x16;
                    NR11_REG = 0x40;
                    NR12_REG = 0x73;
                    NR13_REG = 0x00;
                    NR14_REG = 0xc3;
                    break;
        }

        if(currentSpriteIndex == 0){
            currentSpriteIndex = 1;
        }
        else {
            currentSpriteIndex = 0;
        }
        set_sprite_tile(0, currentSpriteIndex);
        delay(500);

    }
}
