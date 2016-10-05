#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 10
#define MAX_LEN 32
#define MAX_ATTEMPTS 5

struct hash_table {
	int size; // number of users 
	int logins[MAX_USERS];
	char* users[MAX_USERS];
	char* hashes[MAX_USERS];
};

char* read(int n);
void read_table(char* fname, struct hash_table* ht);
void write_table(char* fname, struct hash_table* ht);
void print_table(struct hash_table* ht);
void E(char* in,char* out);
void add(struct hash_table* ht, char* key, char* value);
int valid_username(char*);
int valid_password(char*);
int search(struct hash_table* ht, char* key);
char* toy_hash(char*pass);
void clear() {while ( getchar() != '\n');}

int main( int argc, char* argv[]){
	
	int login_attempts;
	struct hash_table ht;

	printf("Reading hashtable from csv...\n");
	read_table("ht.csv", &ht);
	print_table(&ht);
	


	// prompt for username until receiving
	// a valid one
	int n = 0;
	int i;
	char* user = (char*)malloc(sizeof(char)*32);
	char* pass = (char*)malloc(sizeof(char)*12);
	char* hash = (char*)malloc(sizeof(char)*12);




	while (n < 4 || n > 32) {
		printf("Please enter a username: ");
	//	strcpy(user,read(32));
		strcpy(user, argv[1]);
		printf("%s\n", user);
		n = strlen(user);
	}

	i = search(&ht, user);
	login_attempts = 0;

	// no hash found in table
	if (i == -1) {
		while (1) {
			printf("Please enter a new password: ");
			strcpy(pass, argv[3]);

			if(valid_password(pass))
				break;
		}
		add(&ht, user, toy_hash(pass));
		printf("Created user %s.\n", user);
	}
	// hash found at index i 
	else {
		while (login_attempts < MAX_ATTEMPTS) {
			login_attempts++;
			printf("Please enter your password: ");
			int i;
			strcpy(pass,argv[2]);
			printf("%s\n", pass);
			int cmp = strcmp(toy_hash(pass), ht.hashes[i]);
			if (cmp == 0) {
				while (1) {
					//pass[0] = '\0';
					printf("Please enter a new password: ");
					strcpy(pass,argv[3]);
					if(valid_password(pass))
						break;
				}
				strcpy(ht.hashes[i], toy_hash(pass));
				printf("Password update. Tnx cheers. \n");
				break;
			} else {
				printf("Wrong password. (%d left)\n",MAX_ATTEMPTS-login_attempts);
			}
		}
	}


	write_table("ht.csv", &ht);
	return 0;
}

// read up to n chars from stdin into str
char* read(int n) {
		char* out = (char*)malloc(sizeof(char)*n);
		char c;
		int i;
		while ((c = getchar() != '\n') && i < n) {
			out[i] = c;
			printf("%c",c);
			i++;
		}
		out[i] = '\0';
	return out;
}

int valid_username(char* input) {
		return 1;
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


void add (struct hash_table* ht, char* user, char* hash) {
	if (ht->size < MAX_USERS) {
		strcpy(ht->users[ht->size], user);
		strcpy(ht->hashes[ht->size], hash);
		ht->size++;
	}
}






/*
 * get:  find value for a given key in hash table
 *
 *	returns NULL if not found*/		
int search(struct hash_table* ht, char* user) {
	int i, cmp;
	printf("Searching for %s\n", user);
	for (i = 0; i < ht->size; i++) {

		cmp = strcmp(ht->users[i], user);
		if (cmp == 0) {
			return i;
		}
	}
	return -1;
}

char* toy_hash(char* pass) {
	int i;
	char* in = (char*)malloc(32);
	char* out = (char*)malloc(32);
	
	strcpy(in,pass);

	// null pad to length 12
	for (i = strlen(in); i < 12; i++)
		in[i] = '\0';

	// to upper case
	for (i = 0; i < 12; i++)
		in[i] = toupper(in[i]);

	
	
	E(in,out);

	return out;
}

/*
 * E:
 *	toy encryption function provided in lab
 *
 *	inputs:
 *		char* in - 32 bit input string
 *		char* out - 32 bit output string
 **/
void E(char *in, char *out)
{
	out[0]=(in[0]&0x80)^(((in[0]>>1)&0x7F)^((in[0])&0x7F));
	out[1]=((in[1]&0x80)^((in[0]<<7)&0x80))^(((in[1]>>1)&0x7F)^((in[1])&0x7F));
	out[2]=((in[2]&0x80)^((in[1]<<7)&0x80))^(((in[2]>>1)&0x7F)^((in[2])&0x7F));
	out[3]=((in[3]&0x80)^((in[2]<<7)&0x80))^(((in[3]>>1)&0x7F)^((in[3])&0x7F));
}


//read csv file to hash table
void read_table(char* fname, struct hash_table* ht) {
	FILE* fp = fopen(fname, "r");

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
	FILE* fp = fopen(fname, "w");

	int i;
	for(i=0; i < ht->size; i++) 
		fprintf(fp, "%s,%s\n", ht->users[i], ht->hashes[i]);

	fclose(fp);
}

//print_table:	write contents of hash table to stdin
void print_table(struct hash_table* ht) {
	printf("------------------------\n");
	printf("user => ( password hash )\n");
	printf("------------------------\n");
	int i;
	for (i = 0; i < ht->size; i++) {
		printf("%s => ( %s )\n",ht->users[i], ht->hashes[i]);
	}
	printf("------------------------\n");
}



