#include "heap.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int parent(int i)
{
	return (i-1)/2;
}

int left(int i)
{
	/* TODO */
}

int right(int i)
{
	/* TODO */
}

void swap(int i, int j)
{
	node temp = Mem->heap[i];
	Mem->heap[i] = Mem->heap[j];
	Mem->heap[j] = temp;
}

/*
 * Sucht das groesste Element zwischen dem Knoten an der Array-Position i und
 * seinen bis zu zwei Kindern.
 */
 int getGreatest(int i)
 {
	int left = left(i);
	int right = right(i);
	return max(i, left, right);
 }

/*
 * Sorgt dafuer, dass die Heap-Bedingung wieder stimmt, falls die Heap-
 * Bedingung bei allen Kind-Baeumen erfuellt ist. (Wenn man von unten nach
 * oben geht, kann man so automatisch die komplette Bedingung wieder
 * herstellen, da die Heap-Eigenschaft auf Blaettern immer erfuellt ist).
 */
void heapify(int i) {
    int greatest = getGreatest(i);
    if (greatest != i) 
    {
        swap(i, greatest);
        heapify(greatest);
    }
}

/* 
 * Loescht den Knoten mit der hoechsten Prioritaet und gibt ihn zurueck.
 */
node getRemHighestPrio() {
	node en;
	en.blocks = -1;
	en.mempos = NULL;
	en.key = -1;
	memcpy(en.type, ((char [3]){'%', 'p', '\0'}), 3*sizeof(char));
    if (Mem->heapSize <= 0)
        return en;

    node highestPrio = Mem->heap[0];
    Mem->heapSize--;
    Mem->heap[0] = Mem->heap[Mem->heapSize];
    heapify(0);
    return highestPrio;
}

void* _malloc(int len, int key)
{
	/* TODO */
	/* Wie viele bloecke muessen reserviert werden? */
	int num_blocks = ceil((float)len / BLOCK_SIZE);
	/* Was muss in den Heap eingefuegt werden? */
	node n = (node *) malloc(sizeof(node));
	n->key = key;
	n->blocks = num_blocks;
	
	/* Wo muss der Speicher reserviert werden? */
	/* Initialisiere den Datentypen Inhalts des Speichers mit z.B. Integer.
	 * Reine Willkuer.
	 */
	setType("%i", key);
	 
	/* Wohin sollte Mem->currMemPos jetzt zeigen? */
	/* Was soll zurueckgegeben werden? */
}

int initMem()
{
	Mem = (heap *) malloc(sizeof(heap));
	Mem->mem = (void *) malloc(MEMORY_SIZE);
	Mem->heapSize = 0;
	Mem->currMemPos = Mem->mem;
	return 1;
}

node getHighestPrio()
{
	/* TODO */
}

node find(int key)
{
	for (int i = 0; i < Mem->heapSize; i++)
	{
		if (heap[i].key == key)
		{
			return heap[i];
		}
	}
	return NULL;
}

void freeMem()
{
	free(Mem->mem);
}

/* VORGABE */
void printHeap()
{
	printf("Heapsize: %i\n", Mem->heapSize);
	printf("Key\tBlocks\n");
	int heapHeight = ceil(log2(Mem->heapSize+1));
	int newline = 1;
	int spaceCnt = heapHeight;
	for (int i = 0; i < Mem->heapSize; ++i)
	{
		if (newline)
		{
			spaceCnt --;
			for (int j = 0; j < 1 << (heapHeight-2); ++j)
			{
				printf("       ");
			}
			newline = 0;
			printf("%i %i", Mem->heap[i].key, Mem->heap[i].blocks);
			for (int j = 0; j < spaceCnt*2; ++j)
			{
				printf("  ");
			}
		} else
		{
			for (int j = 0; j < spaceCnt*2; ++j)
			{
				printf("  ");
			}
			if (i % 2)
			{
				for (int j = 0; j < spaceCnt; ++j)
				{
					printf("  ");
				}
			}
			printf("%i %i", Mem->heap[i].key, Mem->heap[i].blocks);
			for (int j = 0; j < spaceCnt*2; ++j)
			{
				printf("  ");
			}
		}
		if (floor(log2(i+2)) == log2(i+2))
		{
			printf("\n");
			newline = 1;
		}
	}
	printf("\n");
}
/* VORGABE */
int setType(char type[3], int key)
{
	for (int i = 0; i < Mem->heapSize; ++i)
	{
		if (Mem->heap[i].key == key)
		{
			Mem->heap[i].type[0] = type[0];
			Mem->heap[i].type[1] = type[1];
			return 0;
		}
	}
	return -1;
}

/*VORGABE */
void printMem()
{
	node vals[MEMORY_SIZE/BLOCK_SIZE];
	for (int i = 0; i < MEMORY_SIZE/BLOCK_SIZE; ++i)
	{
		vals[i].mempos = NULL;
		vals[i].type[0] = '%';
		vals[i].type[1] = 'i';
		vals[i].type[2] = '\0';
	}
	for (int i = 0; i < Mem->heapSize; ++i)
	{
		int valsPos = (Mem->heap[i].mempos - Mem->mem)/BLOCK_SIZE;
		vals[valsPos] = Mem->heap[i];
		for (int j = 1; j < Mem->heap[i].blocks; ++j)
		{
			vals[valsPos+j].mempos = (void*) INT_MIN;
		}
	}
	printf("+--------------------+\n");
	for (int j = 0; j < MEMORY_SIZE/BLOCK_SIZE; ++j)
	{
		if (j != 0)
		{
			printf("|--------------------|\n");
		}
		if (vals[j].mempos == NULL)
		{
			printf("|        NULL        |\n");
		}
		else if (vals[j].mempos == (void*) INT_MIN)
		{
			printf("|        -''-        |\n");
		}
		else
		{
			printf("|");
			if (!strcmp(vals[j].type, "%i"))
			{
				printf(vals[j].type, *((int *) vals[j].mempos));
			} else if (!strcmp(vals[j].type, "%s"))
			{
				printf(vals[j].type, (char *) vals[j].mempos);
			} else if (!strcmp(vals[j].type, "%c"))
			{
				printf(vals[j].type, *((char*) vals[j].mempos));
			} else if (!strcmp(vals[j].type, "%d"))
			{
				printf(vals[j].type, *((double*) vals[j].mempos));
			} else if (!strcmp(vals[j].type, "%p"))
			{
				printf(vals[j].type, 
					*((unsigned long **) vals[j].mempos));
			}
			printf("|\n");
		}
	}
	printf("+--------------------+\n");
}

/* HIER KANN AUSPROBIERT WERDEN - AENDERUNGEN ERLAUBT UND ERWUENSCHT */
int main()
{
	initMem();
	int** i = (int**) _malloc(sizeof(int*), 10);
	setType("%p",10);
	*i = (int*) 0x1234;
	char* str = (char*) _malloc(sizeof(char) * 500, 11);
	for (int j = 0; j < 499; ++j)
	{
		str[j] = 'x';
	}
	str[499] = '\0';
	setType("%s",11);
	int* k = (int*) _malloc(sizeof(int), 9);
	*k =  10;
	int* l = (int*) _malloc(sizeof(int), 13);
	*l =  13;
	int* m = (int*) _malloc(sizeof(int), 2);
	*m =  1000;
	int* n = (int*) _malloc(sizeof(int), 99);
	*n =  50;
	int* o = (int*) _malloc(sizeof(int), 15);
	*o =  42;
	int* p = (int*) _malloc(sizeof(int), 14);
	*p =  41;
	printHeap();
	printMem();
	getRemHighestPrio();
	printHeap();
	printMem();
	freeMem();
	return 0;
}