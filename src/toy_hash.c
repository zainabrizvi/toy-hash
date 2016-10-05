#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "toy_hash.h"



// look through this carefully
// maybe look for a better comparator
// for the hashes
char* toy_hash(char* str) {
	int i;

	char* A0 = (char*)malloc(sizeof(char)*5);
	char* A1 = (char*)malloc(sizeof(char)*5);
	char* A2 = (char*)malloc(sizeof(char)*5);

	char* B0 = (char*)malloc(sizeof(char)*5);
	char* B1 = (char*)malloc(sizeof(char)*5);
	char* B2 = (char*)malloc(sizeof(char)*5);

	
	/*
	 * I think the problem is in correctly splitting
	 * the input word into three blocks of size
	 * 4 bytes each. I think I am doing something
	 * stupid with malloc, strings, copying, 
	 * whatever.
	*/

	// splitting the input string into 3 blocks
	strncpy(A0, str,4);
	strncpy(A1, str+4,4);
	strncpy(A2, str+8,4);



	A0[4] = A1[4] = A2[4] = '\0';

	E(A0,B0);
	E(A1,B1);
	E(A2,B2);

	char* result = (char*)malloc(sizeof(char)*13);
	result[0] = '\0';
	strcat(result, B0);
	strcat(result, B1);
	strcat(result, B2);

	result[13] = '\0';

	return result;
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

