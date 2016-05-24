#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <gcrypt.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


#include "util.h"
#include "blockheader.h"

#define MAX_HASHES 10000

unsigned long toulong(char *);
char * to_reversed_char_arr(unsigned long);

int calculate_hash(Blockheader * blockheader, int num_hashes)
{
	unsigned char * n = malloc(sizeof(char) * 4);
	memcpy(n, blockheader->nonce, sizeof(char) * 4);
	byte_reversal(n, sizeof(char) * 4);
	
	unsigned long starting_nonce = n[0] << 24 | n[1] << 16 | n[2] << 8 | n[3];
	unsigned long end_nonce = starting_nonce + num_hashes;
	unsigned long nonce = starting_nonce;
	//printf("starting_nonce: %ld\n", starting_nonce);
	
	// copy paste
	for( ; nonce <= end_nonce; nonce++) {
		// put current nonce in blockheader object
		// first, shift long back to char[4]
		n[0] = nonce >> 24;
		n[1] = nonce >> 16;
		n[2] = nonce >> 8;
		n[3] = nonce;
		// reverse byte order
		byte_reversal(n,sizeof(char)*4);
		// put n into blockheader
		blockheader->nonce[0] = n[0];
		blockheader->nonce[1] = n[1];
		blockheader->nonce[2] = n[2];
		blockheader->nonce[3] = n[3];
		//printf("blockheader->nonce val after assignment in for loop: %ld\n", toulong(blockheader->nonce));
		// calculate the hash using the sha-256 hashing algorithm
		char * hash;
		size_t size = getData(blockheader,&hash);
		char * r1;
		size = sha256_digest(hash,size,&r1);
		free(hash);
		// To calculate a valid hash, we need to do two hashing passes
		char * r2;
		size = sha256_digest(r1,size,&r2);
		free(r1);
		if(check_hash(r2,(int)size))
		{
			printf("%ld : ", nonce);
			print_hash(r2,size);
		}
		free(r2);
		
	}
	
	//printf("blockheader->nonce val after for loop: %ld", toulong(blockheader->nonce));
	
	unsigned char * end_nonce_char = to_reversed_char_arr(end_nonce - 1);
	//memcpy(&(blockheader->nonce), end_nonce_char, sizeof(char) * 4);
	blockheader->nonce[0] = end_nonce_char[0];
	blockheader->nonce[1] = end_nonce_char[1];
	blockheader->nonce[2] = end_nonce_char[2];
	blockheader->nonce[3] = end_nonce_char[3];
	
	//printf("blockheader nonce end of calc hash function: %ld\n", toulong(blockheader->nonce));
	
	free(n);
	
	return EXIT_SUCCESS;
}

unsigned long toulong(char * n) {
	char * asdf = malloc(sizeof(char) * 4);
	memcpy(asdf, n, sizeof(char) * 4);
	byte_reversal(asdf, sizeof(char) * 4);
	
	return asdf[0] << 24 | asdf[1] << 16 | asdf[2] << 8 | asdf[3];
}

char * to_reversed_char_arr(unsigned long u){
	char * n = malloc(sizeof(char) * 4);
	n[0] = u >> 24;
	n[1] = u >> 16;
	n[2] = u >> 8;
	n[3] = u;
	byte_reversal(n, sizeof(char) * 4);
	return n;
}

int bitcoin_loop(const unsigned int processcount) {
	printf("\n\nStarting bitcoin_loop\n");
	// Start, end time
	unsigned long start,end;
	// Set start time
	start = current_time_millis();
	
	Blockheader * blockheader = malloc(sizeof(Blockheader));
	getWork(blockheader);
	// TODO: Split the calculation of the hashes into several segments based on the processcount
	int segment_size = ceil((double)MAX_HASHES / processcount);
	
	for (int i = 0; i < processcount; i++)
	{
		calculate_hash(blockheader, segment_size);
		//printf("nonce after run #%i: %ld\n", i, toulong(blockheader->nonce));
	}

	end = current_time_millis();
	printf("Calculation finished after %.3fs\n", (double) (end - start) / 1000);
	free(blockheader);
	return EXIT_SUCCESS;
}

int bitcoin_parallel(const unsigned int processcount) {
	printf("\n\nStarting bitcoin_parallel\n");
	// Start, end time
	unsigned long start,end;
	// Set start time
	start = current_time_millis();

	// TODO: Create a Blockheader object and fill it with the initial data using the getWork Method
	Blockheader * blockheader = malloc(sizeof(Blockheader));
	// TODO: Split the calculation of the hashes into several segments based on the processcount
	int segment_size = ceil((double) MAX_HASHES / processcount);
	unsigned long starting_nonce = toulong(&(blockheader->nonce));
	// TODO: Spawn a process for each segment
	int pos = 0;
	int * child_pids = malloc(sizeof(int) * processcount);
	
	for (; pos < processcount; pos++)
	{
		child_pids[pos] = fork();
		if (child_pids[pos] < 0)
			return EXIT_FAILURE;
		if (child_pids[pos] == 0)
			break;
	}
	
	if (child_pids[pos] == 0)
	{
		starting_nonce += pos * segment_size;
		char * n = to_reversed_char_arr(starting_nonce);
		memcpy(&(blockheader->nonce), n, sizeof(char) * 4);
		calculate_hash(blockheader, segment_size);
		return EXIT_SUCCESS;
	}
	
	int status;
	for (int i = 0; i < processcount; i++)
	{
		wait(&status);
	}
	
	end = current_time_millis();
	printf("Calculation finished after %.3fs\n", (double) (end - start) / 1000);

	return EXIT_SUCCESS;
}


/*
Calculates Blockhashes in a simple loop.
*/
int bitcoin_simple() {
	printf("Starting bitcoin_simple\n");
	// Start, end time
	unsigned long start,end;
	// Set start time
	start = current_time_millis();


	// Creates and retrieves the Block-Header information
	Blockheader * blockheader = malloc(sizeof(Blockheader));
	// The getWork method fills an empty Blockheader struct with all the neccesary information needed to calcualte the Hash of a Block.
	getWork(blockheader);
	// The nonce is the value that is incremented in each run to get a different hash value
	char * n = malloc(sizeof(char)*4);
	memcpy(n,&(blockheader->nonce),sizeof(char)*4);
	// The values in the Blockheader are actually in reverse byte order and need to be reversed in order to increment the nonce value. 
	byte_reversal(n,sizeof(char)*4);
	// Convert the 4 byte long raw data into an unsinged long 
	unsigned long starting_nonce = n[0] << 24 | n[1] << 16 | n[2] << 8 | n[3];
	// The nonce value we received in the getWork method is the actual starting nonce value. We start to calculate hashes with this initial nonce and increase it by one in each run. 
	unsigned long nonce = starting_nonce;
	//char * hash;
	// In practice it is very hard to find a valid hash, so in this exercise we will limit the amount of hashes we calculate.
	for(;nonce<=(starting_nonce+MAX_HASHES);nonce++) {
		// put current nonce in blockheader object
		// first, shift long back to char[4]
		n[0] = nonce >> 24;
		n[1] = nonce >> 16;
		n[2] = nonce >> 8;
		n[3] = nonce;
		// reverse byte order
		byte_reversal(n,sizeof(char)*4);
		// put n into blockheader
		blockheader->nonce[0] = n[0];
		blockheader->nonce[1] = n[1];
		blockheader->nonce[2] = n[2];
		blockheader->nonce[3] = n[3];
		//printf("blockheader->nonce val after assignment in for loop: %ld\n", toulong(blockheader->nonce));
		// calculate the hash using the sha-256 hashing algorithm
		char * hash;
		size_t size = getData(blockheader,&hash);
		char * r1;
		size = sha256_digest(hash,size,&r1);
		free(hash);
		// To calculate a valid hash, we need to do two hashing passes
		char * r2;
		size = sha256_digest(r1,size,&r2);
		free(r1);
		if(check_hash(r2,(int)size))
		{
			printf("%ld : ", nonce);
			print_hash(r2,size);
		}
		free(r2);
	}
	printf("blockheader->nonce after calculation in bitcoin simple: %ld", toulong(blockheader->nonce));
	free(n);

	end = current_time_millis();
	printf("Calculation finished after %.3fs\n", (double) (end - start) / 1000);

	free(blockheader);
	return EXIT_SUCCESS;

}

int main(int argc, char** argv) {

	if(argc != 2) {
		printf("Usage: bitcoin PROCESSCOUNT\n");
		return EXIT_FAILURE;
	}

	unsigned int processcount = strtol(argv[1],NULL,10);

	if(bitcoin_simple() != EXIT_SUCCESS) {
		printf("Error or not implemented.\n\n");
	}

	if(bitcoin_loop(processcount) != EXIT_SUCCESS) {
		printf("Error or not implemented bitcoin_loop.\n\n");
	}

	if(bitcoin_parallel(processcount) != EXIT_SUCCESS) {
		printf("Error or not implemented.\n\n");
	}
	
	return 0;
}
