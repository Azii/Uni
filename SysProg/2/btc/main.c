#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <gcrypt.h>
#include <math.h>


#include "util.h"
#include "blockheader.h"

#define MAX_HASHES 10000

int calculate_hash(Blockheader * blockheader, int offset, int num_hashes)
{ 
	/*
	char * n = malloc(sizeof(char)*4);
	memcpy(n,&(blockheader->nonce),sizeof(char)*4);
	byte_reversal(n,sizeof(char)*4);
	unsigned long starting_nonce = n[0] << 24 | n[1] << 16 | n[2] << 8 | n[3];
	unsigned long nonce = starting_nonce;
	*/
	char * n = malloc(sizeof(char) * 4);
	memcpy(n, &(blockheader->nonce), sizeof(char) * 4);
	byte_reversal(n, sizeof(char) * 4);
	
	unsigned long starting_nonce = n[0] << 24 | n[1] << 16 | n[2] << 8 | n[3];
	starting_nonce += offset;
	printf("%ld", starting_nonce);
	unsigned long end_nonce = starting_nonce + num_hashes;
	unsigned long nonce = starting_nonce;
	
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
	return EXIT_SUCCESS;
}

int bitcoin_loop(const unsigned int processcount) {
	printf("\n\nStarting bitcoin_loop\n");
	// Start, end time
	unsigned long start,end;
	// Set start time
	start = current_time_millis();

	// TODO: Create a Blockheader object and fill it with the initial data using the getWork Method
	Blockheader * b_header = malloc(sizeof(Blockheader));
	getWork(b_header);
	// TODO: Split the calculation of the hashes into several segments based on the processcount
	int segment_size = ceil(MAX_HASHES / processcount);
	char * initial_nonce = malloc(sizeof(char) * 4);
	memcpy(initial_nonce, &(b_header->nonce), sizeof(char) * 4);
	
	for (int i = 0; i < processcount; i++)
	{
		calculate_hash(b_header, i * segment_size, segment_size);
		memcpy(&(b_header->nonce), initial_nonce, sizeof(char) * 4);
	}
	
	// TODO: If a hash has the appropriate difficulty (hint: check_hash) print it on the console using print_hash

	end = current_time_millis();
	printf("Calculation finished after %.3fs\n", (double) (end - start) / 1000);
	free(b_header);
	return EXIT_SUCCESS;
}

int bitcoin_parallel(const unsigned int processcount) {
	printf("\n\nStarting bitcoin_parallel\n");
	// Start, end time
	unsigned long start,end;
	// Set start time
	start = current_time_millis();

	// TODO: Create a Blockheader object and fill it with the initial data using the getWork Method
	// TODO: Split the calculation of the hashes into several segments based on the processcount
	// TODO: Spawn a process for each segment
	// TODO: If a hash has the appropriate difficulty print it on the console using print_hash
	// TODO: Wait until all children finish before exiting

	end = current_time_millis();
	printf("Calculation finished after %.3fs\n", (double) (end - start) / 1000);

	return EXIT_FAILURE;
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
		printf("Error or not implemented.\n\n");
	}

	if(bitcoin_parallel(processcount) != EXIT_SUCCESS) {
		printf("Error or not implemented.\n\n");
	}
	
	return 0;
}
