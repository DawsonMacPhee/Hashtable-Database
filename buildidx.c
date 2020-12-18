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

// Creates the khs and vhs files
FILE* createFile(char *originalName, char *newExt){
    char *newName = malloc(sizeof(char) * (strlen(originalName) + strlen(newExt)));
    strcpy(newName, originalName);
    newName[strlen(newName) - (strlen(newExt) - 1)] = '\0';

    strcat(newName, newExt);
    FILE *newFile = fopen(newName, "wb+");
    if(newFile == NULL){
        fprintf(stderr, "Couldn't create a new file\n");
        exit(-1);
    }

    free(newName);
    return newFile;
}

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Usage: %s filename.kv capacity\n", argv[0]);
        exit(-1);
    }

    int capacity = atoi(argv[2]);

    FILE *fp = fopen(argv[1], "rb");
    if(fp == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(-1);
    }

    FILE *khs = createFile(argv[1], "khs");
    write_empty(khs, capacity);
    FILE *vhs = createFile(argv[1], "vhs");
    write_empty(vhs, capacity);

    fseek(fp, 0, SEEK_END );
    int kvSize = ftell(fp)/(STRLEN * 2);
    fseek(fp, 0, SEEK_SET);

    char key[STRLEN];
    char value[STRLEN];
    int index = 10;
    for(int i = 0; i < kvSize; i++){
        read_keyval(fp, key, value);
        int hashKeyIndex = hashfn(key, capacity);                           // Hash the key
        int hashValueIndex = hashfn(value, capacity);                       // Hash the value

        #ifdef DEBUG
        printf("%s, %s\n", key, value);
        #endif

        while(read_index(khs, hashKeyIndex, &index) && index != -1){        // Add key to khs file
            hashKeyIndex += 1;
            if(hashKeyIndex == capacity){
                hashKeyIndex = 0;
            }
        }
        write_index(khs, i, hashKeyIndex);

        while(read_index(vhs, hashValueIndex, &index) && index != -1){      // Add value to vhs file
            hashValueIndex += 1;
            if(hashValueIndex == capacity){
                hashValueIndex = 0;
            }
        }
        write_index(vhs, i, hashValueIndex);
    }

    fclose(fp);
    fclose(khs);
    fclose(vhs);
}