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

void writeFile(const char *filename, char *txt) //TODO writeFile
{
    int len = my_strlen(txt);
    char *buffer = malloc(sizeof(char) * len);
    int return_code = 0;
    FILE *stream = fopen(filename, "w");

    if (stream == NULL) {
        fprintf(stderr, "Cannot open file for writing\n");
        exit( -1 );
    }
    sprintf(buffer, "%s", txt);
    size_t size = my_strlen(txt);
    if (fwrite(buffer, size, 1, stream) != 1)
        fprintf(stderr, "Cannot write block in file\n" );
    return_code = fclose(stream);
    if (return_code == EOF) {
        fprintf(stderr, "Cannot close file\n" );
        exit(-1);
    }
}

char *command_time() //TODO void
{
    time_t rawtime = time(NULL);
    struct tm *time_info = localtime(&rawtime);
    char *clock = malloc(sizeof(char) * 7);
    int hour = time_info->tm_hour;
    int min = time_info->tm_min;
    sprintf(clock, "%02d:", hour);
    sprintf(clock + my_strlen(clock), "%02d\t", min);
    return clock;
}
