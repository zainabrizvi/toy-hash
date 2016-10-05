#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "toy_hash.h"
#include "table.h"

#define MAX_ATTEMPTS 5

int valid_password(char*);
int main( int argc, char* argv[]){

	struct hash_table ht;
	ht.size = 0;

	read_table("ht.csv", &ht);
	//print_table(&ht);


	// maybe just allocate tonnes of space
	// and you wont get weird behaviour?? 
	int i,n,login_attempts;
	char* user = (char*)malloc(sizeof(char)*32);
	char* pass = (char*)malloc(sizeof(char)*12);
	char* hash = (char*)malloc(sizeof(char)*12);


	// get valid username from stdin
	n = 0;
	while (n < 4 || n > 32) {
		printf("Please enter a username: ");
		scanf("%s", user);
		n = strlen(user);
	}

	// look for user in table
	i = search(&ht, user);
	login_attempts = 0;
	// no such user found in table
	if (i == -1) {
		while (1) {
			printf("Please enter a new password: ");
			scanf("%s", pass);
			// todo 
			if(valid_password(pass))  
				break;
			printf("Invalid password breh.\n");
		}
		add(&ht, user, toy_hash(pass));
		printf("Created user %s.\n", user);
	}
	// user found at index i 
	else {
		while (login_attempts < MAX_ATTEMPTS) {
			login_attempts++;
			printf("Please enter your password: ");
			scanf("%s", pass);
			int cmp = strcmp(toy_hash(pass), ht.hashes[i]);
			printf("Your actual password hash: %s\n", ht.hashes[i]);
			printf("Your input password hash: %s\n", toy_hash(pass));
			if (cmp == 0) {
				while (1) {
					printf("Please enter a new password: ");
					scanf("%s", pass);
					if(valid_password(pass))
						break;
					printf("Invalid password.\n");	
				}
				strcpy(ht.hashes[i], toy_hash(pass));
				printf("Password updated.\n Tnx cheers.\n");
				login_attempts = 0; // logins are reset each successful login
				break;
			} else {
				printf("Wrong password.\n");
				int remaining = MAX_ATTEMPTS - login_attempts;
				printf("%d attempts left.\n" ,remaining);
				if (remaining == 0) {
					printf("Account locked.\n");
					break;
				}
			}
		}
	}
	write_table("ht.csv", &ht);
	return 0;
}

// todo
int valid_password(char* password) {
	int i, c;
	// verify all chars are one of the three
	//
	//	numbers: ascii 48-57
	//	capitals: 65-90
	//  lowercase: 97-122
	for (i = 0; i < strlen(password); i++) {
		if (i == 12) {
			password[i] = '\0';
			break;
		}
		c = (int)password[i];

		// if you find a c that isn't in any of the 
		// ranges, return -1
	}
	return 1;
}