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

    char *target = malloc(sizeof(char) * 10);           // Handles command line input
    strcpy(target, argv[2]);

    FILE *fp = fopen(argv[1], "rb");                    // Open the kv file
    if(fp == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(-1);
    }

    FILE *khs = openFile(argv[1], "khs");

    int capacity = get_capacity(khs);
    int hash = hashfn(target, capacity);
    int index;
    char key[STRLEN];
    char val[STRLEN];

    for(int i = 0 ; i < capacity; i++){                 // Search for value matching the key
        read_index(khs, hash, &index);
        read_key(fp, index, key);
        if(strcmp(key,target) == 0){
            read_val(fp, index, val);
            printf("%s\n", val);
            free(target);
            fclose(fp);
            fclose(khs);
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
    fclose(khs);
}