#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;
int enlarge_called=0;

struct Pair {
     char * key;
     void * value;
};

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    unsigned long pos = hash(key, map->capacity);
    unsigned long aux = pos;
    struct Pair *n = createPair(key, value);
    while ( (map->buckets[pos] != NULL) && (!is_equal(map->buckets[pos]->key, key)) ) {
        pos++;
        if (pos == map->capacity) {
            pos = 0;
        }
        if (pos == aux) {
            break;
        }
    }
    map->buckets[pos] = n;
    map->size++;
    map->current = pos;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap *map = (HashMap *) malloc(sizeof(HashMap));
    map->buckets = (Pair **) calloc(10, sizeof(Pair *));
    map->capacity = capacity;
    map->size = 0;
    map->current = -1;
    return map;
}

void eraseMap(HashMap * map,  char * key) {    

}

void * searchMap(HashMap * map,  char * key) {  
    Pair *n;
    unsigned long pos = hash(key, map->capacity);
    unsigned long aux = pos;
    n = map->buckets[pos];
    while (!is_equal(n->key, key)) {
        n = map->buckets[pos];
        pos++;
        if (pos == map->capacity) {
            pos = 0;
        }
        if (pos == aux) {
            break;
        }
        if (map->buckets[pos] == NULL) {
            return NULL;
        }
    }
    map->current = pos;
    return n->value;
}

void * firstMap(HashMap * map) {

    return NULL;
}

void * nextMap(HashMap * map) {

    return NULL;
}