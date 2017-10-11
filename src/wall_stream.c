#include <stdio.h>
#include <string.h>
#include "wall_stream.h"
#include "screen.h"

int main(){

    //  Create screen
    screen my_screen = screen_init();
    
    // Setup Screen
    // strcpy(my_screen.width, "600px");
    // strcpy(my_screen.height, "400px");
    // strcpy(my_screen.x, "10px");
    // strcpy(my_screen.y, "5px");
    // strcpy(my_screen.port, "1234");
    // my_screen.id = 0;

    //  Dump Screen info
    printf("my_screen.width: %s\n", my_screen.width);
    printf("my_screen.heigth: %s\n", my_screen.height);
    printf("my_screen.x: %s\n", my_screen.x);
    printf("my_screen.y: %s\n", my_screen.y);
    printf("my_screen.port: %s\n", my_screen.port);
    printf("my_screen.id: %d\n", my_screen.id);
    return 0;
}