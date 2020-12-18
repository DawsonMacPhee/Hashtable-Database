#ifndef __stdio_h_
#include <stdio.h>
#endif

#ifndef __string_h_
#include <string.h>
#endif

#ifndef __stdlib_h_
#include <stdlib.h>
#endif

#ifndef __util_h_
#include "util.h"
#endif

#ifndef __hashfn_h_
#include "hashfn.h"
#endif

// Opens the khs and vhs files
FILE* openFile(char *originalName, char *newExt){
    char *newName = malloc(sizeof(char) * (strlen(originalName) + strlen(newExt)));
    strcpy(newName, originalName);
    newName[strlen(newName) - (strlen(newExt) - 1)] = '\0';

    strcat(newName, newExt);
    FILE *newFile = fopen(newName, "rb");
    if(newFile == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(-1);
    }

    free(newName);
    return newFile;
}

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Usage: %s filename.kv 'search term'\n", argv[0]);
        exit(-1);
    }

    char *target = malloc(sizeof(char) * STRLEN);           // Handles command line input
    strcpy(target, argv[2]);

    FILE *fp = fopen(argv[1], "rb");                        // Opens kv file
    if(fp == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(-1);
    }

    FILE *vhs = openFile(argv[1], "vhs");

    int capacity = get_capacity(vhs);
    int hash = hashfn(target, capacity);
    int index;
    char key[STRLEN];
    char val[STRLEN];

    for(int i = 0 ; i < capacity; i++){                     // searches for key matching value
        read_index(vhs, hash, &index);  
        read_val(fp, index, val);
        if(strcmp(val,target) == 0){
            read_key(fp, index, key);
            printf("%s\n", key);
            free(target);
            fclose(fp);
            fclose(vhs);
            exit(0);
        }
        hash += 1;
        if(hash == capacity){
            hash = 0;
        }
    }
    printf("NOT FOUND\n");
    free(target);
    fclose(fp);
    fclose(vhs);
}