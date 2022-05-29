/*
** EPITECH PROJECT, 2022
** Bootstrap
** File description:
** write_some_txt
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <my.h>
    //#define BLOCK_SIZE 3000

void writeFile(const char *filename, char *txt)
{
    int len = my_strlen(txt);
    char *buffer = malloc(sizeof(char) * len);
    int returnCode = 0;
    FILE *stream = fopen(filename, "w");
    
    if (stream == NULL) {
        fprintf(stderr, "Cannot open file for writing\n");
        exit( -1 );
    }
    sprintf(buffer, "%s", txt);
    size_t size = my_strlen(txt);
    if (1 != fwrite(buffer, size, 1, stream))
        fprintf(stderr, "Cannot write block in file\n" );
    returnCode = fclose(stream);
    if (returnCode == EOF) {
        fprintf(stderr, "Cannot close file\n" );
        exit(-1);
    }
}

char *command_time()
{
    time_t rawtime = time(NULL);
    struct tm *time_info = localtime(&rawtime);
    char *clock = malloc(sizeof(char) * 7);
    int hour = time_info->tm_hour;
    int min = time_info->tm_min;
    if (hour < 10)
        sprintf(clock, "0%d:", hour);
    else
        sprintf(clock, "%d:", hour);
    if (min < 10)
        sprintf(clock + my_strlen(clock), "0%d\t", min);
    else
        sprintf(clock + my_strlen(clock), "%d\t", min);
    return clock;
}
