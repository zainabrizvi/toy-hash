#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* toy_hash(char*);
void E(char* in, char* out);


int main( int argc, char* argv[]){

	if (argc == 2) 
		printf("toy_hash(%s) = %s\n",argv[1], toy_hash(argv[1]));
	else if (argc == 3)
		printf("%d\n",strcmp(toy_hash(argv[1]), toy_hash(argv[2])));


	return 0;
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