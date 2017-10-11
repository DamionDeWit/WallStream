#include <stdio.h>
#include <string.h>
#include "screen.h"


screen screen_init(char w[], char h[], char x[], char y[], char p[], char id[]){
    screen scrn;

    // Initialize Screen
    strcpy(scrn.width, w);
    strcpy(scrn.height, h);
    strcpy(scrn.x, x);
    strcpy(scrn.y, y);
    strcpy(scrn.port, p);
    strcpy(scrn.id, id);

    return scrn;
}

//  Dump Screen info
void screen_dump(screen scrn){
    printf("my_screen.width: %s\n", scrn.width);
    printf("my_screen.heigth: %s\n", scrn.height);
    printf("my_screen.x: %s\n", scrn.x);
    printf("my_screen.y: %s\n", scrn.y);
    printf("my_screen.port: %s\n", scrn.port);
    printf("my_screen.id: %s\n", scrn.id);
}