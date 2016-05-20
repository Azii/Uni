#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <gcrypt.h>
#include <stdio.h>
#include <sys/types.h>


#include "util.h"
#include "blockheader.h"

#define MAX_HASHES 10000

int calc_hash(int num_hashes, char * starting_nonce_offset, Blockheader * blockheader)
{
	// copy paste
	// The nonce is the value that is incremented in each run to get a different hash value
	char * n = malloc(sizeof(char)*4);
	memcpy(n,&(blockheader->nonce),sizeof(char)*4);
	// The values in the Blockheader are actually in reverse byte order and need to be reversed in order to increment the nonce value. 
	byte_reversal(n,sizeof(char)*4);
	// Convert the 4 byte long raw data into an unsinged long 
	unsigned long starting_nonce = n[0] << 24 | n[1] << 16 | n[2] << 8 | n[3];
	starting_nonce += starting_nonce_offset;
	// The nonce value we received in the getWork method is the actual starting nonce value. We start to calculate hashes with this initial nonce and increase it by one in each run. 
	unsigned long nonce = starting_nonce;
	char * hash;
	// In practice it is very hard to find a valid hash, so in this exercise we will limit the amount of hashes we calculate.
	for(;nonce<=(starting_nonce + num_hashes);nonce++) {
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
		size_t size = getData(blockheader,&hash);
		size = sha256_digest(hash,size,&hash);
		// To calculate a valid hash, we need to do two hashing passes
		size = sha256_digest(hash,size,&hash);
		if(check_hash(hash,(int)size))
		{
			printf("%ld : ", nonce);
			print_hash(hash,size);
		}
	}

	end = current_time_millis();
	printf("Calculation finished after %.3fs\n", (double) (end - start) / 1000);

	free(blockheader);
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
	int * pids = malloc(sizeof(int) * processcount);
	for (int i = 0; i < processcount; i++)
	{
		if (i > 0)
		{
			if (pids[i - 1] == 0)
			{
				break;
			}
		}
		pids[i] = fork();
	}
	if (pids[processcount - 1] != 0)
	{
		
	}
	
	
	int child_pid = 0;
	int num_process = 0;
	
	for (int i = 0; i < processcount - 1; i++)
	{	
		child_pid = fork();
		
		if (child_pid != 0)
			break;
		
		num_process++;
	}
	printf("%i", num_process);
	
	calc_hashes((int)floor(MAX_HASHES / processcount));
	wait(child_pid);
	
	return 0;
	
	/*char * n = malloc(sizeof(char) * 4);
	memcpy(n, &(b_header->nonce), sizeof(char) * 4);
	byte_reversal(n, sizeof(char) * 4);
	
	// copy paste
	unsigned long starting_nonce = n[0] << 24 | n[1] << 16 | n[2] << 8 | n[3];
	starting_nonce += 0;
	// The nonce value we received in the getWork method is the actual starting nonce value. We start to calculate hashes with this initial nonce and increase it by one in each run. 
	unsigned long nonce = starting_nonce;
	char * hash;
	// In practice it is very hard to find a valid hash, so in this exercise we will limit the amount of hashes we calculate.
	for( ; nonce<=(starting_nonce + MAX_HASHES); nonce++) {
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
		size_t size = getData(blockheader,&hash);
		size = sha256_digest(hash,size,&hash);
		// To calculate a valid hash, we need to do two hashing passes
		size = sha256_digest(hash,size,&hash);
		if(check_hash(hash,(int)size))
		{
			printf("%ld : ", nonce);
			print_hash(hash,size);
		}
	}
	
	
	if(child_pid != 0)
		wait(child_pid);
	
	
	
	// TODO: If a hash has the appropriate difficulty (hint: check_hash) print it on the console using print_hash

	end = current_time_millis();
	printf("Calculation finished after %.3fs\n", (double) (end - start) / 1000);

	return EXIT_FAILURE;*/
}

/*
printf("\n\nStarting bitcoin_loop\n");
	// Start, end time
	unsigned long start,end;
	// Set start time
	start = current_time_millis();

	// TODO: Create a Blockheader object and fill it with the initial data using the getWork Method
	Blockheader * b_header = malloc(sizeof(Blockheader));
	getWork(b_header);
	// TODO: Split the calculation of the hashes into several segments based on the processcount
	int * pids = malloc(sizeof(int) * processcount);
	for (int i = 0; i < processcount; i++)
	{
		if (i > 0)
		{
			if (pids[i - 1] == 0)
			{
				break;
			}
		}
		pids[i] = fork();
	}
	if (pids[processcount - 1] != 0)
	{
		
	}
	
	
	int child_pid = 0;
	int num_process = 0;
	
	for (int i = 0; i < processcount - 1; i++)
	{	
		child_pid = fork();
		
		if (child_pid != 0)
			break;
		
		num_process++;
	}
	printf("%i", num_process);
	
	calc_hashes((int)floor(MAX_HASHES / processcount));
	wait(child_pid);
	
	return 0;
	
	/*char * n = malloc(sizeof(char) * 4);
	memcpy(n, &(b_header->nonce), sizeof(char) * 4);
	byte_reversal(n, sizeof(char) * 4);
	
	// copy paste
	unsigned long starting_nonce = n[0] << 24 | n[1] << 16 | n[2] << 8 | n[3];
	starting_nonce += 0;
	// The nonce value we received in the getWork method is the actual starting nonce value. We start to calculate hashes with this initial nonce and increase it by one in each run. 
	unsigned long nonce = starting_nonce;
	char * hash;
	// In practice it is very hard to find a valid hash, so in this exercise we will limit the amount of hashes we calculate.
	for( ; nonce<=(starting_nonce + MAX_HASHES); nonce++) {
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
		size_t size = getData(blockheader,&hash);
		size = sha256_digest(hash,size,&hash);
		// To calculate a valid hash, we need to do two hashing passes
		size = sha256_digest(hash,size,&hash);
		if(check_hash(hash,(int)size))
		{
			printf("%ld : ", nonce);
			print_hash(hash,size);
		}
	}
	
	
	if(child_pid != 0)
		wait(child_pid);
	
	
	
	// TODO: If a hash has the appropriate difficulty (hint: check_hash) print it on the console using print_hash

	end = current_time_millis();
	printf("Calculation finished after %.3fs\n", (double) (end - start) / 1000);

	return EXIT_FAILURE;*/
	

int bitcoin_parallel(const unsigned int processcount) {
	printf("\n\nStarting bitcoin_parallel\n");
	// Start, end time
	unsigned long start,end;
	// Set start time
	start = current_time_millis();

	// TODO: Create a Blockheader object and fill it with the initial data using the getWork Method
	Blockheader * b_header = malloc(sizeof(Blockheader));
	getWork(b_header);
	// TODO: Split the calculation of the hashes into several segments based on the processcount
	int hashes_per_process = MAX_HASHES / processcount;
	for (int i = 0; i < processcount; i++)
	{
		Blockheader * temp = malloc(sizeof(Blockheader));
		memcpy(temp, b_header, sizeof(Blockheader));
		//temp->nonce += i * 0;
	}
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
	char * hash;
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
		size_t size = getData(blockheader,&hash);
		size = sha256_digest(hash,size,&hash);
		// To calculate a valid hash, we need to do two hashing passes
		size = sha256_digest(hash,size,&hash);
		if(check_hash(hash,(int)size))
		{
			printf("%ld : ", nonce);
			print_hash(hash,size);
		}
	}

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
