#include <string.h>
#include "screen.h"

screen screen_init(){
    screen scrn;

    // Setup Screen
    strcpy(scrn.width, "600px");
    strcpy(scrn.height, "400px");
    strcpy(scrn.x, "10px");
    strcpy(scrn.y, "5px");
    strcpy(scrn.port, "1234");
    scrn.id = 0;

    return scrn;
}