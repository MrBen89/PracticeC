#include <gb/gb.h>
#include <stdio.h>
#include "slime.c"
#include "background.c"
#include "backgroundsheet.c"

void main(){
    UINT8 currentSpriteIndex = 0;

    set_bkg_data(0, 7, BackgroundTile);
    set_bkg_tiles(0, 0, 40, 18, BackgroundSheet);

    set_sprite_data(0, 2, Slime);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    while(1){
        scroll_bkg(1,0);
        switch(joypad()){
                case J_LEFT:
                    scroll_sprite(0, -10, 0);
                    break;
                case J_RIGHT:
                    scroll_sprite(0, 10, 0);
                    break;
                case J_UP:
                    scroll_sprite(0, 0, -10);
                    break;
                case J_DOWN:
                    scroll_sprite(0, 0, 10);
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
