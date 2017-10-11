#include "wall_stream.h"


typedef struct screen
{
    char id[MAXBUF];
    char width[MAXBUF];
    char height[MAXBUF];
    char x_pos[MAXBUF];
    char y_pos[MAXBUF];   
    char port[MAXBUF];
} screen;

int main(){
    
    create_config_default();

    return 0;
}