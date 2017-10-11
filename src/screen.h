#ifndef SCREEN_H
#define SCREEN_H

#ifndef MAXBUF
#define MAXBUF 1024
#endif

typedef struct screen
{
    char width[MAXBUF];
    char height[MAXBUF];
    char x[MAXBUF];
    char y[MAXBUF];   
    char port[MAXBUF];
    char id[MAXBUF];
} screen;

screen screen_init();
void screen_dump();

#endif