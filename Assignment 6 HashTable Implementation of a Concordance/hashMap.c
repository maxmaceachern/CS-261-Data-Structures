#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "hashMap.h"



/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
    printf("hash1\n");
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
    printf("hash2\n");
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{
	/*write this*/
	struct hashLink* current;       /*Pointer to current hashLink*/
	struct hashLink* next;          /*Pointer to next hashLink, after current*/
	int index;

    for(index = 0; index < ht->tableSize; index++){
        current = ht->table[index];     /*Index starts at element zero of the hashMap*/
        while(current != NULL){         /*Iterate through until the end where current would equal NULL*/
            next = current->next;
            free(current);
            current = next;
        }
        ht->table[index] = NULL;        /*As it iterates through, make each hashLink NULL*/
    }
    free(ht->table);
    ht->tableSize = NULL;
    ht->count = NULL;
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/*
Resizes the hash table to be the size newTableSize
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	/*write this*/
	hashMap* tempMap = createMap(newTableSize);   /*Create temporary hashMap with new table size to copy to*/
	int index = 0;

	for(index = 0; index < ht->tableSize; index++){
        if (ht->table[index] == NULL)               /*Iterate through until it reaches the end where table[index] is NULL*/
            continue;
        hashLink* current = ht->table[index];
        do{
            insertMap(tempMap, current->key, current->value);   /*Copy input hashMap to temporary hashMap*/
            current = current->next;
        } while (current != NULL);
	}
	_freeMap(ht);
	ht->count = tempMap->count;                 /*Copy values back to ht*/
	ht->tableSize = tempMap->tableSize;
	ht->table = tempMap->table;

	tempMap->table = NULL;                      /*Free temporary hashMap*/
	free(tempMap);

}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".

 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.

 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{
	/*write this*/
	assert(ht != NULL);
    int hashVal;

    if (HASHING_FUNCTION == 1){
        hashVal = stringHash1(k) % ht->tableSize;
        }
    else if (HASHING_FUNCTION == 2){
        hashVal = stringHash2(k) % ht->tableSize;
        }

    hashLink *current = ht->table[hashVal];

	if(current == NULL){                /*Execute this if key does not exist*/
        ht->table[hashVal] = malloc(sizeof(hashLink));
        ht->table[hashVal]->key = malloc((strlen(k)+1)*sizeof(char));
        strcpy(ht->table[hashVal]->key,k);          /*Copy string from k to table[hashVal] key*/
        ht->table[hashVal]->value = v;
        ht->table[hashVal]->next = NULL;

        if(((float)(++(ht->count)) / (float)(ht->tableSize)) > LOAD_FACTOR_THRESHOLD)  /*Assess load factor by typecasting to float*/
            _setTableSize(ht, (ht->tableSize*2));
        return;
	}
	else if (strcmp(current->key,k) == 0){ /*Execute this if hashVal key and k are equal, thereby making the current value equal to v*/
        current->value = v;
        return;
	}
	else{
        while(current->next != NULL){      /*Iterate through until it gets to the end of the list*/
            if(strcmp(current->next->key,k) == 0){      /*Execute if the keys are equivalent*/
                current->value = v;
                return;
            }
            current = current->next;
        }
        /*Execute this if the keys do not match*/
        hashLink *newL = malloc(sizeof(hashLink));
        newL->key = malloc((strlen(k)+1)*sizeof(char));
        strcpy(newL->key,k);
        newL->value = v;
        newL->next = NULL;
        current->next = newL;

        if(((float)(++(ht->count)) / (float)(ht->tableSize)) > LOAD_FACTOR_THRESHOLD)
            _setTableSize(ht, (ht->tableSize*2));
        return;
	}
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.

 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.

 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{
	/*write this*/
    assert(ht != NULL);
    int hashVal;
    if (HASHING_FUNCTION == 1){
        hashVal = stringHash1(k) % ht->tableSize;
        }
    else if (HASHING_FUNCTION == 2){
        hashVal = stringHash2(k) % ht->tableSize;
        }

    hashLink *current = ht->table[hashVal];

    while(current != NULL){                 /*Iterate through until it gets to the end*/
        if (strcmp(current->key,k) == 0)
            return &(current->value);
        current = current->next;
    }

	return NULL;
}

/*
 a simple yes/no if the key is in the hashtable.
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{
	/*write this*/
	assert(ht != NULL);
    int hashVal;
    if (HASHING_FUNCTION == 1){
        hashVal = stringHash1(k) % ht->tableSize;
        }
    else if (HASHING_FUNCTION == 2){
        hashVal = stringHash2(k) % ht->tableSize;
        }

    hashLink *current = ht->table[hashVal];

    while(current != NULL){
        if (strcmp(current->key,k) == 0)
            return 1;
        current = current->next;
    }
	return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{
	/*write this*/
	assert(ht != NULL);
    int hashVal;

    if (HASHING_FUNCTION == 1){
        hashVal = stringHash1(k) % ht->tableSize;
        }
    else if (HASHING_FUNCTION == 2){
        hashVal = stringHash2(k) % ht->tableSize;
        }

    hashLink *current = ht->table[hashVal];

    if (current == NULL)
        return;

    hashLink *nextL = ht->table[hashVal]->next;

    if (strcmp(current->key,k) == 0){
        free(current->key);
        ht->table[hashVal] = nextL;
        free(current);
        return;
    }

    while (nextL != NULL){
        if (strcmp(current->key,k)){
            free(nextL->key);
            current->next = nextL->next;
            free(nextL);
            return;
        }
        current = current->next;
        nextL = nextL->next;
    }
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{
	/*write this*/
	return ht->count;

}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{
	/*write this*/
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{
	/*write this*/
	int numBuckets = 0;
	int index;

	for(index = 0; index < ht->tableSize; index++){
        if (ht->table[index] == NULL)
            numBuckets++;
	}

	return numBuckets;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)

 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{
	/*write this*/
	return ((float)(ht->count) / (float)(ht->tableSize));
}
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {
			printf("\nBucket Index %d -> ", i);
		}
		while(temp != 0){
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;
		}
	}
}


