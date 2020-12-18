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

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s 'search term'\n", argv[0]);
        exit(-1);
    }

    char *target = malloc(sizeof(char) * STRLEN);               // Handle command line input
    strcpy(target, argv[1]);

    FILE *tpkv = fopen("title.principals.kv", "rb");            // Open required files
    if(tpkv == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(-1);
    }
    FILE *tpkhs = fopen("title.principals.khs", "rb");
    if(tpkhs == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(-1);
    }
    FILE *nkv = fopen("name.basics.kv", "rb");
    if(nkv == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(-1);
    }
    FILE *nkhs = fopen("name.basics.khs", "rb");
    if(nkhs == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(-1);
    }
    FILE *tkv = fopen("title.basics.kv", "rb");
    if(tkv == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(-1);
    }
    FILE *tvhs = fopen("title.basics.vhs", "rb");
    if(tvhs == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(-1);
    }

    int index;
    char key[STRLEN];
    char val[STRLEN];
    char key2[STRLEN];
    int found = 0;
    
    int capacity = get_capacity(tvhs);          // Get the key of the title
    int hash = hashfn(target, capacity);
    for(int i = 0; i < capacity; i++){
        read_index(tvhs, hash, &index);
        read_val(tkv, index, val);
        if(strcmp(val, target) == 0){
            read_key(tkv, index, key);
            found = 1;
            break;
        }
        hash += 1;
        if (hash == capacity){
            hash = 0;
        }
    }

    if(!found){                                 // Exit if no key is found for the title
        printf("NOT FOUND\n");
        free(target);
        fclose(tpkv);
        fclose(tpkhs);
        fclose(tkv);
        fclose(tvhs);
        fclose(nkv);
        fclose(nkhs);
        exit(-1);
    }
    found = 0;

    capacity = get_capacity(tpkhs);             // Get the index of the movie
    hash = hashfn(key, capacity);
    for(int i = 0; i < capacity; i++){
        read_index(tpkhs, hash, &index);
        read_key(tpkv, index, key2);
        if(strcmp(key, key2) == 0){
            found = 1;
            break;
        }
        hash += 1;
        if(hash == capacity){
            hash = 0;
        }
    }

    if(!found){                                 // Exit if no index is found for the movie
        printf("NOT FOUND\n");
        free(target);
        fclose(tpkv);
        fclose(tpkhs);
        fclose(tkv);
        fclose(tvhs);
        fclose(nkv);
        fclose(nkhs);
        exit(-1);
    }

    int tempIndex;
    capacity = get_capacity(nkhs);
    while(strcmp(key, key2) == 0){              // Print actor names
        read_val(tpkv, index, val);

        hash = hashfn(val, capacity);
        for(int i = 0; i < capacity; i++){
            read_index(nkhs, hash, &tempIndex);
            read_key(nkv, tempIndex, key2);
            if(strcmp(val, key2) == 0){
                read_val(nkv, tempIndex, val);
                break;
            }
            hash += 1;
            if(hash == capacity){
                hash = 0;
            }
        }

        printf("%s\n", val);
        index += 1;
        if(index == capacity){
            index = 0;
        }
        read_key(tpkv, index, key2);
    }

    free(target);
    fclose(tpkv);
    fclose(tpkhs);
    fclose(tkv);
    fclose(tvhs);
    fclose(nkv);
    fclose(nkhs);
}