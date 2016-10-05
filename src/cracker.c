#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "toy_hash.h"
#include "table.h"

#define N 4

char* crack(char* hash);

// doesn't work right now, but if you can
// figure out what is wrong with line 30


int main(int argc, char* argv[]) {
	struct hash_table ht; // hash table 

	read_table("ht.csv", &ht);
	print_table(&ht);

	FILE* fp = fopen("passwords", "w");

	clock_t start = clock(), stop;
	
	int i;
	int j = 0;
	char password[256];
	for (i = 0; i < ht.size; i++) {
		printf("Searching for password of user %s with hash %s...\n", ht.users[i], ht.hashes[i]);
		strcpy(password, crack(ht.hashes[i]));
		if (strlen(password)) {
			fprintf(fp, "%s,%s\n", ht.users[i], password);
			j++;
		} 
	}
	stop = clock();
	int msec = (stop-start) * 1000 / CLOCKS_PER_SEC;
	printf("Cracked %d passwords in %d seconds %d milliseconds. \n", j, msec/1000, msec%1000);

	fclose(fp);
	return 0;
}


// cracks upperase ASCII passwords of length 4
// with very slight modification you can 
// AT LEAST use this to print the table of
// all four letter words 
char* crack(char* hash) {
	int i,j,k,l;
	int n,lo,hi,cmp;

	lo = 65;
	hi = 91;
	char* result = (char*) malloc(sizeof(char)*(16)); 
	for(i = lo ; i < hi; i++) {
		for (j = lo; j < hi; j++) {
			for (k = lo; k < hi; k++) {
				for(l = lo ; l < hi; l++) {
					char word[5] = {(char)i, (char)j,
									(char)k, (char)l,
									'\0'};
					cmp = strcmp(toy_hash(word), hash);
					if (cmp==0) {  // hash match
						int m;
						for(m = 0; m < 5; m++)
							result[m] = word[m];
						return result;
					}

				}
			}	
		}
	}
	return NULL;
}