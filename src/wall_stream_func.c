#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wall_stream.h"

void create_config_default(){
    //  Create a default config file
    //  for a set-up for a 3x2 wall
    #define NUMBER_OF_SCREENS 6
    FILE *pFile;
    int i;
    char line[MAXBUF];

    //  Create and open Config.conf
    pFile = fopen("Config.conf", "w");
    fputs("# Default Config file for Wall Stream\n", pFile);
    fputs("# Setup for a basic 3x2 wall\n", pFile);
    fputs("####################\n", pFile);

    for(i = 0; i < NUMBER_OF_SCREENS; i++){
        
        //  Screen Id
        sprintf(line, "ID=%d\n", i);
        fputs(line, pFile);
        
        //  Screen Width
        sprintf(line, "WIDTH=%s\n", "iw/3");
        fputs(line, pFile);
        
        //  Screen Height
        sprintf(line, "HEIGHT=%s\n", "ih/3");
        fputs(line, pFile);
        
        //  Screen X Position
        sprintf(line, "X=iw/3*%d\n", i%3);
        fputs(line, pFile);
        
        //  Screen Y Position
        sprintf(line, "Y=ih/2*%d\n", i/3);
        fputs(line, pFile);

        //  Screen Port
        sprintf(line, "PORT=123%d\n", i+1);
        fputs(line, pFile);

        fputs("####################\n", pFile);
    }

    #undef NUMBER_OF_SCREENS
}

void open_config(){
    FILE *pFile;
    //  First try to open Config.conf
    pFile = fopen("Config.conf", "r");
    
    if(pFile == NULL){  //  Couldn't find Config.conf
        //  Try Config.txt
        pFile = fopen("Config.txt", "r");
        
        if(pFile == NULL){  // Still couldn't find a Config file
        //  create config file
        create_config_default();
        }
    }
}

void run_ffmpeg(){
    char command[65535];
    char input_file[255] = "sample.divx";
    int screen_count = 1;
    int i;

    // Start Ffmpeg 
    strcpy(command, "ffmpeg -re ");

    // Get input file
    strcat(command, "-i ");
    strcat(command, input_file);
    strcat(command, " ");   // Adds space

    // Here comes a for-loop where each screen is configured
    for(i = 0; i < screen_count; i++){
        // init variables
        char command_screen[255];

        // Do stuff to make string, read a conf file or something
        strcpy(command_screen, "-filter:v 'crop=iw/3:ih/2:iw/3*0:ih/2*0' -preset ultrafast -vcodec libx264 -tune zerolatency -bufsize 30000k  -f mpegts udp://192.168.58.221:1231");
        
        // Add space at end of string
        strcat(command_screen, " ");
        
        // Add string to command
        strcat(command, command_screen);
    }

    // print/execute the command
    // printf("%s\n", command);
    system(command);

    return ;
}