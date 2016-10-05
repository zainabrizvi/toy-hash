#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 10
#define MAX_USERS 10
#define MAX_LEN 32

struct hash_table {
	int size; // number of users 
	char* users[MAX_USERS];
	char* hashes[MAX_USERS];
};

void read_table(char* fname, struct hash_table* ht);
void write_table(char* fname, struct hash_table* ht);
void print_table(struct hash_table* ht);
void add(struct hash_table* ht, char* key, char* value);
int search(struct hash_table* ht, char* user);