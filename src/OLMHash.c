#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 10
#define MAX_LEN 32

int read_table(char*,char**,char**);
void print_table(char**,char**,int [],int);
void write_table(char*,char**,char**,int);
void E(char*, char*);
char* toy_hash(char*);
int search(char**,char*, int);
int valid_pass(char*);
void menu();
void login(char**,char**,int*);
int add_user(char*,char*);



int main( int argc, char* argv[]){


	// initial set up 
	int i,j;
	int max_attempts = 5; // should get from cmd line later
	int N = 0; // number of users 
	int logins[MAX_USERS];
	char* users[MAX_USERS];
	char* hashes[MAX_USERS];



	// initialize arrays
	for (i = 0; i < MAX_USERS; i++) { 
		logins[i] = 0;
		users[i] = (char*)malloc(sizeof(char)*MAX_LEN);
		hashes[i] = (char*)malloc(sizeof(char)*MAX_LEN);
	}


	// read table file's contents into the arrays
	N = read_table("in.table", users, hashes);


	printf("Hello Friends. Welcome Back.\n\n");
	menu();
	printf("> ");

	char c;
	while ((c = getchar()) != 'q') {
		if (c == '\n')
			continue;

		if (c == '1') {
			login(users,hashes, &N);
		} 
		else if (c == '2') {
			print_table(users,hashes,logins,N);
		} 
		else if(c == '3') {
			menu();
		} 
		else {
			printf("Invalid input:%c\n", c);
		}
		printf("> ");
	}

	write_table("out.table",users,hashes,N);

	return 0;
}
	
void menu()
{
	printf("Plese choose one of the following options.\n");
	printf("-------------------------------------------\n");
	printf("1 Log in or sign up\n");
	printf("2 List Users\n");
	printf("3 Show These Options\n");
	printf("q Quit\n\n");
	printf("-------------------------------------------\n");
}

// todo
int valid_pass(char* password) {
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

void login(char* users[], char* hashes[], int n) {

	char pass[MAX_LEN];
	char user[MAX_LEN];

	printf("Please enter a username. \n");
	printf("> ");

	scanf("%s\n", user);

	i = search(users,user);

	if (i == -1)
		add_user(user);


	printf("Please enter your password. \n");
	printf("> ");
	scanf("%s\n", pass);
}


/*
 *	add_user:  add a user to the hash table
 *
 *
 *
*/
int add_user(char* user, char* hash) {
	char buf[MAX_LEN];
	printf("Enter a new password. \n");
	printf("> ");
	
	scanf("%s",buf);
	strcpy(hash, toy_hash(buf));
	printf("Created new user %s.\n", user);
	return 1;
}




/*
 * read_table: read contents of hash table from file
 *		Column 1 is copied to char* users[]
 *		Column 2 is copied to char* hashes[]
 *	
 *	returns number of lines (ie number of users)
*/
int read_table(char* fname, char* users[], char* hashes[]) {
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
			users[i] = (char*)malloc(sizeof(char)*MAX_LEN);
			strcpy(users[i], word);
			j = 0;
		}
		// new line
		else if (c == '\n') {
			word[j] = '\0';	
			j = 0;
			hashes[i] = (char*)malloc(sizeof(char)*MAX_LEN);
			strcpy(hashes[i++], word);
		} 
		// append char to current word
		else {
			word[j] = c;
			j++;
		}
	}
	
	fclose(fp);
	return i;
}

/*
 * write_table: write contents of hash table to file
 *		char* users[] is written to column 1
 *		char* hashes[] is written to column 2
*/
void write_table(char* fname, char* users[], char* hashes[], int n) {
	FILE* fp = fopen(fname, "w");

	int i;
	for (i = 0; i < n; i++) {
		fprintf(fp,"%s,%s\n", users[i], hashes[i]);
	}
	fclose(fp);
}

/*
 * print_table:	write contents of hash table to stdin
 *		char* users[] is written to column 1
 *		char* hashes[] is written to column 2
 *		int logins[] is written to column 3
*/
void print_table(char** users, char** hashes, int logins[], int n) {
	printf("\nuid,hash,logins\n");
	int i;
	printf("-------------------------------------------\n");
	for (i = 0; i < n; i++) {

		printf("%d: %s, %s, %d\n", i,users[i], hashes[i], logins[i]);
	}
	printf("-------------------------------------------\n");
}
/*
 * search:  finds the index of a string in
 *			an array of strings, terminating
 *			after a fixed index
 *
 *	inputs:	
 *		char** arr - array of string
 *		char* val - string to find
 *		int len - termination index
 *
 *	returns:
 *		int - index in arr of val,
 *			  -1 if not found
 *
*/		
int search(char** arr, char* val, int len) {
	int i;
	for (i = 0; i < len; i++) {
		if (strcmp(arr[i],val) == 0)
			return i;
	}
	return -1;
}

/*
 * E:
 *	toy encryption function provided in lab
 *
 *	inputs:
 *		char* in - 32 bit input string
 *		char* out - 32 bit output string
 *
*/
void E(char *in, char *out)
{
	out[0]=(in[0]&0x80)^(((in[0]>>1)&0x7F)^((in[0])&0x7F));
	out[1]=((in[1]&0x80)^((in[0]<<7)&0x80))^(((in[1]>>1)&0x7F)^((in[1])&0x7F));
	out[2]=((in[2]&0x80)^((in[1]<<7)&0x80))^(((in[2]>>1)&0x7F)^((in[2])&0x7F));
	out[3]=((in[3]&0x80)^((in[2]<<7)&0x80))^(((in[3]>>1)&0x7F)^((in[3])&0x7F));
}
