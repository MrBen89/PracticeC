#include <gb/gb.h>
#include <stdio.h>
#include "slime.c"
#include "background.c"
#include "backgroundsheet.c"
#include "windowmap.c"
#include <gbdk/font.h>

INT8 playerlocation[2]; //2 8 bit integers for x and y of player
UINT8 currentSpeed;
INT8 gravity = -2;
UINT8 floorYPosition = 100;
BYTE jumping;

void soundJump(){
    NR10_REG = 0x16;
    NR11_REG = 0x40;
    NR12_REG = 0x73;
    NR13_REG = 0x00;
    NR14_REG = 0xc3;
}

INT8 wouldHitSurface(UINT8 projectedYPosition){
    if(projectedYPosition >= floorYPosition){
        return floorYPosition;
    }
    return -1;
}

void jump(UINT8 spriteID, UINT8 spriteLocation[2]){
    INT8 possibleYSurface;

    if (jumping == 0) {
        jumping=1;
        currentSpeed = 10;
    }

    currentSpeed = currentSpeed + gravity;

    spriteLocation[1] = spriteLocation[1] - currentSpeed;

    possibleYSurface = wouldHitSurface(playerlocation[1]);

    if (possibleYSurface > -1){
        jumping = 0;
        move_sprite(spriteID, spriteLocation[0], possibleYSurface);
    }
    else {
        move_sprite(spriteID, spriteLocation[0], spriteLocation[1]);
    }

}

void waitFor(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }
}

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

    playerlocation[0] = 10;
    playerlocation[1] = floorYPosition;
    jumping = 0;

    move_sprite(0, playerlocation[0], playerlocation[1]);
    SHOW_SPRITES;
    SHOW_BKG;
    SHOW_WIN;
    DISPLAY_ON;

    while(1){
        scroll_bkg(1,0);
        if(currentSpriteIndex == 0){
            currentSpriteIndex = 1;
        }
        else {
            currentSpriteIndex = 0;
        }
        set_sprite_tile(0, currentSpriteIndex);
        if((joypad() & J_A) || jumping ==1){
            jump(0,playerlocation);
        }
        if (joypad() & J_LEFT){
            playerlocation[0] = playerlocation[0] - 2;
            move_sprite(0, playerlocation[0], playerlocation[1]);
        }
        if (joypad() & J_RIGHT){
            playerlocation[0] = playerlocation[0] + 2;
            move_sprite(0, playerlocation[0], playerlocation[1]);
        }
        waitFor(5);


    }

}
