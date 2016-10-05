#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "table.h"


//read csv file to hash table
void read_table(char* fname, struct hash_table* ht) {
	FILE* fp = fopen(fname, "r");
	if (fp == NULL) 
		return;


	char c;
	int i,j; 
	i = j = 0;


	// read by characters and build words
	char word[MAX_LEN];
	while ( (c = fgetc(fp)) != EOF) {
		// new column
		if (c == ',') {
			word[j] = '\0';
			ht->users[i] = (char*)malloc(sizeof(char)*MAX_LEN);
			strcpy(ht->users[i], word);
			j = 0;
		}
		// new line
		else if (c == '\n') {
			word[j] = '\0';
			j = 0;
			ht->hashes[i] = (char*)malloc(sizeof(char)*MAX_LEN);
			strcpy(ht->hashes[i++], word);
		}
		// append char to current word
		else {
			word[j] = c;
			j++;
		}
	}
	ht->size = i;
	fclose(fp);
}

// write contents of hash table to file
void write_table(char* fname, struct hash_table* ht) {
	FILE* fp = fopen(fname, "w+");

	int i;
	for(i=0; i < ht->size; i++) 
		fprintf(fp, "%s,%s\n", ht->users[i], ht->hashes[i]);

	fclose(fp);
}

//print_table:	write contents of hash table to stdin
void print_table(struct hash_table* ht) {
	printf("user => ( password hash )\n");
	printf("------------------------\n");
	int i;
	for (i = 0; i < ht->size; i++) {
		printf("%s => ( %s )\n",ht->users[i], ht->hashes[i]);
	}
}	

void add (struct hash_table* ht, char* user, char* hash) {
	if (ht->size < MAX_USERS) {
		ht->users[ht->size] = (char*)malloc(sizeof(user));
		ht->hashes[ht->size] = (char*)malloc(sizeof(hash));
		strcpy(ht->users[ht->size], user);
		strcpy(ht->hashes[ht->size], hash);
		ht->size++;
	}
}

/*
 * search:  find value for a given key in hash table
 *
 *	returns NULL if not found*/		
int search(struct hash_table* ht, char* user) {
	int i, cmp;

	for (i = 0; i < ht->size; i++) {
		cmp = strcmp(ht->users[i], user);
		if (cmp == 0) {
			return i;
		}
	}
	return -1;
}
