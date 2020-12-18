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

// Find the key for Kevin Bacon in the names kv file
void findBaconKey(FILE *nkv, FILE *nvhs, char *baconKey){
    int capacity = get_capacity(nvhs);
    int hash = hashfn("Kevin Bacon", capacity);
    int index;
    for(int i = 0; i < capacity; i++){
        read_index(nvhs, hash, &index);
        read_val(nkv, index, baconKey);
        if(strcmp(baconKey, "Kevin Bacon") == 0){
            read_key(nkv, index, baconKey);
            break;
        }
        hash += 1;
        if(hash == capacity){
            hash = 0;
        }
    }
}

// Prints a movie name when called by the compareToBacon function
void printMovieName(FILE *tkhs, FILE *tkv, char *key, char *key2, char *val){
    int capacity = get_capacity(tkhs);
    int hash = hashfn(key, capacity);
    int index;
    for(int j = 0; j < capacity; j++){
        read_index(tkhs, hash, &index);
        read_key(tkv, index, key2);
        if(strcmp(key, key2) == 0){
            read_val(tkv, index, val);
        }
        hash += 1;
        if(hash == capacity){
            hash = 0;
        }
    }

    printf("%s\n", val);
}

// Determines if Kevin Bacon is in the same movie
// If Yes, print and return 1
// If No, return 0
int compareToBacon(FILE *tpkhs, FILE *tpkv, FILE *tkhs, FILE *tkv, FILE *nvhs, FILE *nkv, char key[STRLEN], char key2[STRLEN], char val[STRLEN]){
    char baconKey[STRLEN];
    findBaconKey(nkv, nvhs, baconKey);
    int capacity = get_capacity(tpkhs);
    int hash = hashfn(key, capacity);
    int index;
    for(int i = 0; i < capacity; i++){
        read_index(tpkhs, hash, &index);
        read_key(tpkv, index, key2);
        while(strcmp(key2, key) == 0){
            read_val(tpkv, index, val);
            if(strcmp(baconKey, val) == 0){
                printMovieName(tkhs, tkv, key, key2, val);
                return 1;
            }
            index += 1;
            read_key(tpkv, index, key2);
        }
        hash += 1;
        if(hash == capacity){
            hash = 0;
        }
    }
    return 0;
}

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
    FILE *tpvhs = fopen("title.principals.vhs", "rb");
    if(tpvhs == NULL){
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
    FILE *nvhs = fopen("name.basics.vhs", "rb");
    if(nvhs == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(-1);
    }
    FILE *tkv = fopen("title.basics.kv", "rb");
    if(tkv == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(-1);
    }
    FILE *tkhs = fopen("title.basics.khs", "rb");
    if(tkhs == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(-1);
    }

    int index;
    char key[STRLEN];
    char val[STRLEN];
    char key2[STRLEN];
 
    int capacity = get_capacity(nvhs);                  // Get key of actor
    int hash = hashfn(target, capacity);
    for(int i = 0; i < capacity; i++){
        read_index(nvhs, hash, &index);
        read_val(nkv, index, val);
        if(strcmp(val, target) == 0){
            read_key(nkv, index, key);
            break;
        }
        hash += 1;
        if(hash == capacity){
            hash = 0;
        }
    }

    capacity = get_capacity(tpvhs);                 // Find a movie the actor is in
    hash = hashfn(key, capacity);
    for(int i = 0; i < capacity; i++){
        read_index(tpvhs, hash, &index);
        read_val(tpkv, index, val);
        if(strcmp(val, key) == 0){
            read_key(tpkv , index, key);
            if(compareToBacon(tpkhs, tpkv, tkhs, tkv, nvhs, nkv, key, key2, val)){             // Check if Kevin Bacon is in the movie
                break;
            }
        }
        hash += 1;
        if(hash == capacity){
            hash = 0; 
        }
    }
    free(target);
    fclose(tpkv);
    fclose(tpkhs);
    fclose(tpvhs);
    fclose(tkv);
    fclose(tkhs);
    fclose(nkv);
    fclose(nvhs);
}