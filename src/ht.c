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


void read_table(char* fname, struct hash_table* ht);
void write_table(char* fname, struct hash_table* ht);
void print_table(struct hash_table* ht);
void E(char* in,char* out);
void add(struct hash_table* ht, char* key, char* value);
int valid_username(char*);
int valid_password(char*);
char* get(struct hash_table* ht, char* key);
char* toy_hash(char*pass);
void clear() {while ( getchar() != '\n');}

int main( int argc, char* argv[]){
	char user[MAX_LEN];
	char pass[MAX_LEN];
	char* hash;
	int login_attempts;
	struct hash_table ht;
	read_table("ht.csv", &ht);


	while (1) {
		printf("Please enter a username between 4 and 32 charactrs: ");
		scanf("%s\n", user);
		int n = strlen(user);
		if (n > 4 && n < 32)
			break;
	}

	hash = get(&ht, user);
	login_attempts = 0;

	if (hash == NULL) {
		while (1) {
			printf("Please enter a new password: ");
			scanf("%s", pass);
			if(valid_password(pass))
				break;
		}
		add(&ht, user, toy_hash(pass));
		printf("Created user %s.\n", user);
	}
	else {
		while (login_attempts < MAX_ATTEMPTS) {
			login_attempts++;
			printf("Please enter your password: ");
			int i;
			for(i = 0; i < MAX_LEN; i++)
				pass[i] = getchar();

			int cmp = strcmp(toy_hash(pass), hash);
			if (cmp == 0) {
				while (1) {
					pass[0] = '\0';
					printf("Please enter a new password: ");
					scanf("%s", pass);
					if(valid_password(pass))
						break;
				}
				strcpy(hash, toy_hash(pass));
				printf("Password update. Tnx cheers. \n");
			}
		}
	}

	write_table("ht.csv", &ht);
	return 0;
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
char* get(struct hash_table* ht, char* user) {
	int i, cmp;
	for (i = 0; i < ht->size; i++) {
		cmp = strcmp(ht->users[i], user);
		if (cmp == 0)
			return ht->hashes[i];
	}
	return NULL;
}



char* toy_hash(char* pass) {
	int i;

	// null pad to length 12
	for (i = strlen(pass); i < 12; i++)
		pass[i] = '\0';

	// to upper case
	for (i = 0; i < 12; i++)
		pass[i] = toupper(pass[i]);


	// use toy encryption function
	char* in = pass;
	char* out = (char*)malloc(32);
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



