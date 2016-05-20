#include "util.h"

#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"

unsigned long current_time_millis() {
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}


void print_hash(const unsigned char* string, const int len) {
    size_t size = ((2*len)+1);
	char * mes = malloc(size);
    char * mes_i = 0;
    int i = 0;


    mes_i = mes; //+ 2;
    for (i = 0; i < len; i++) {
        snprintf(mes_i, 3, "%02x", string[i]);
        mes_i += 2;/* XXX assert pointer width equals char width */
    }

    
    char * converter = malloc(size-1);
    memcpy(converter,mes,size-1);
    hex_byte_reversal(converter,size-1);
    memcpy(mes,converter,size-1);
    //free(converter);
    mes[(2 * len)] = 0;	
    printf(mes);
    printf("\n");
    free(mes);
}


size_t sha256_digest(const char * input, const size_t len,char ** dest) {
    BYTE b_input[len];
    memcpy(b_input,input,len);
    BYTE buf[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, b_input, len);
    sha256_final(&ctx, buf);
    char * r = malloc(sizeof(BYTE)*SHA256_BLOCK_SIZE);
    memcpy(r,buf,sizeof(BYTE)*SHA256_BLOCK_SIZE);
    *dest = r;
    return SHA256_BLOCK_SIZE;
}


void byte_reversal(char * input, size_t size) {
    char * output = malloc(size);
    int i = size-1;
    int offset = i;
    for(;i>=0;i--) {
        output[offset-i] = input[i];
    }
    memcpy(input,output,size);
    free(output);
}


void hex_byte_reversal(char * input, size_t size) {
    if(size%2==0) {
        char * output = malloc(size);
        int i = size-1;
        int offset = i;
        for(;i>=0;i-=2) {
            output[offset-i] = input[i];
            output[offset-(i+1)] = input[i-1]; 
        }
        memcpy(input,output,size);
        //free(output);
    }
}

int check_hash(const char * hash, const int len){
    int i;
    for(i=len-1;i>=24;i--)
    {
        if(hash[i]!=0)
        {
            return 0;
        }  
    }
    return 1;
}
