#include <stdio.h>
#include <string.h>
#include "wall_stream.h"
#include "screen.h"

int main(){
    //  Variables to store data for screen
    FILE *pFile;
    int ids;
    char w[MAXBUF], h[MAXBUF], x[MAXBUF], y[MAXBUF], p[MAXBUF], id[MAXBUF];
    
    create_config_default();
    //  Open Config.conf
    pFile = fopen("Config.conf", "r");

    //  Count the Id's in .conf

    //  Create screen
    screen my_screen = screen_init(w, h, x, y, p, id);

    //  Dump Screen info
    screen_dump(my_screen);
    
    return 0;
}