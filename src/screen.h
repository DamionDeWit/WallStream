#ifndef SCREEN_H
#define SCREEN_H

#define MAXBUF 1024

typedef struct screen
{
    char width[MAXBUF];
    char height[MAXBUF];
    char x[MAXBUF];
    char y[MAXBUF];   
    char port[MAXBUF];
    int id;
} screen;

screen screen_init();

#endif