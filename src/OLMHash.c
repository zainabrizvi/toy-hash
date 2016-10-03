#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 10
#define MAX_LEN 14

void print_table(char**,char**,int[],int);
char* hash_da_pass(char*);
void E(char*, char*);
int dumbo_search(char**,char*, int);



int main(){

	int max_attempts = 5; // should get from cmd line later
	int total_users = 0;
	int badLogins[MAX_USERS];
	char* userIDs[MAX_USERS];
	char* passwordHashes[MAX_USERS];

	// initialize badlogins to 0
	int i,j;

	for (i = 0; i < MAX_USERS; i++) {
		badLogins[i] = 0;
	}

	// make some space for userIDs and
	// passwordHashes
	for (i = 0; i < MAX_USERS; i++) {
		userIDs[i] = malloc(sizeof(char)*MAX_LEN);
		passwordHashes[i] = malloc(sizeof(char)*MAX_LEN);
	}

	// make a few toy users
	userIDs[0] = "jimbo";
	userIDs[1] = "jonny";
	userIDs[2] = "judy";
	total_users = 3;

	// hash their toy passwords
	passwordHashes[0] = hash_da_pass("dumbo");
	passwordHashes[1] = hash_da_pass("me");
	passwordHashes[2] = hash_da_pass("moue");


//	print_table(userIDs, passwordHashes, badLogins, total_users);


	// user prompt
	while (1) {
		char user_input [MAX_LEN];
		printf("Hello Friends. Enter a user id (q to quit): ");
		scanf("%s", user_input);

		if (strcmp(user_input, "q")==0) {
			printf("tnx cheers.\n");
			exit(0);
		}

		i = dumbo_search(userIDs, user_input, total_users);
		// existing user
		if (i != -1) {
			while (badLogins[i] < max_attempts) {
				printf("Hi %s. Please enter your password: ", userIDs[i]);
				scanf("%s", user_input);

				// compare hash of password with stored value
				int cmp = strcmp(hash_da_pass(user_input), passwordHashes[i]);

				// match
				if (cmp == 0) {
					printf("Congratulation breh. U got da pass right.");
					printf("Please enter a new password: ");
					scanf("%s", user_input);



					printf("Thank u. I have updated ur passwerdhash to %s\n", passwordHashes[i]);
				}
				// fail 
				else {
					badLogins[i]++;
					printf("Noomaannnnnn. You have %d more tries.\n\n",
							max_attempts-badLogins[i]);
				}
			}
			printf("Too many bad logins lol.\n");
		}
		// new user
		else  {
			printf("Hi %s lol ur a dumbo\n", user_input);
			exit(0);
		}
	}



	return 0;
}

/*
 * search the first len elements of arr for val
 * returns:  -1 if not found
 *			 index of val if found
*/
int dumbo_search(char** arr, char* val, int len) {
	int i;
	for (i = 0; i < len; i++) {
		if (strcmp(arr[i],val) == 0)
			return i;
	}
	return -1;
}

char* hash_da_pass (char* pass) {
	return pass;
}


void E(char *in, char *out)
{
	out[0]=(in[0]&0x80)^(((in[0]>>1)&0x7F)^((in[0])&0x7F));
	out[1]=((in[1]&0x80)^((in[0]<<7)&0x80))^(((in[1]>>1)&0x7F)^((in[1])&0x7F));
	out[2]=((in[2]&0x80)^((in[1]<<7)&0x80))^(((in[2]>>1)&0x7F)^((in[2])&0x7F));
	out[3]=((in[3]&0x80)^((in[2]<<7)&0x80))^(((in[3]>>1)&0x7F)^((in[3])&0x7F));
}




void print_table(char* A[], char* B[], int C[], int n) {
	int i;
	printf("----------------------\n");
	printf("uid,hash,badLogins\n");
	printf("----------------------\n");
	for (i = 0; i < n; i++) {
		printf("%s,%s,%d\n", A[i], B[i], C[i]);
	}
	printf("----------------------\n");
	printf("Total Users: %d\n", n);
}
