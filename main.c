#include "sort.h"
#include "../vector/vector.h"
#include "stdio.h"
#include <time.h>
#include <stdlib.h>

#define RUNS 10000
#define MAX_VECTOR_SIZE 10000
#define MAX_NUMBER 100

/*Shake sort and Bubble sort tests*/
void TimeCompare();

/*Test functions. All test functions recieve function pointer to the tested function as a parameter*/
void SimpleGenericSort(ADTErr(*SortFunc)(Vector* _vec));
void SimpleGenericSortForSingleMember(ADTErr(*SortFunc)(Vector* _vec));
void GenericSortNULLVector(ADTErr(*SortFunc)(Vector* _vec));
void MassiveGenericSortTest(ADTErr(*SortFunc)(Vector* _vec));
void GenericSortEmptyVector(ADTErr(*SortFunc)(Vector* _vec));
void MassiveGenericSortTestWithNegatives(ADTErr(*SortFunc)(Vector* _vec));

/*Counting sort tests*/
void SimpleCountingSort();
void SimpleCountingSortForSingleMember();
void CountingSortNULLVector();
void CountingSortEmptyVector();
void MassiveCountingSortTest();

/*Radix sort tests*/
void SimpleRadixSort();
void SimpleRadixSortForSingleMember();
void RadixSortNULLVector();
void RadixSortEmptyVector();
void MassiveRadixSortTest();

int main()
{	
	/*Time Compare
	
	printf("\nTime compare:\n");	

	TimeCompare();*/
	
	/*Bubble sort tests
	
	printf("\nBubble sort test:\n");
	
	SimpleGenericSort(BubbleSort);
	SimpleGenericSortForSingleMember(BubbleSort);
	GenericSortNULLVector(BubbleSort);
	GenericSortEmptyVector(BubbleSort);
	MassiveGenericSortTest(BubbleSort);
	MassiveGenericSortTestWithNegatives(BubbleSort);*/	

	/*Shake sort tests

	printf("\nShake sort test:\n");

	SimpleGenericSort(ShakeSort);
	SimpleGenericSortForSingleMember(ShakeSort);
	GenericSortNULLVector(ShakeSort);
	GenericSortEmptyVector(ShakeSort);
	MassiveGenericSortTest(ShakeSort);
	MassiveGenericSortTestWithNegatives(ShakeSort);*/
	
	/*Quick sort tets

	printf("\nQuick sort test:\n");

	SimpleGenericSort(QuickSort);
	SimpleGenericSortForSingleMember(QuickSort);
	GenericSortNULLVector(QuickSort);
	GenericSortEmptyVector(QuickSort);
	MassiveGenericSortTest(QuickSort);
	MassiveGenericSortTestWithNegatives(QuickSort);*/
	
	/*Quick Sort test - Iterative

	printf("\nQuick sort - Iterative test:\n");
	
	SimpleGenericSort(QuickSort_Iter);
	SimpleGenericSortForSingleMember(QuickSort_Iter);
	GenericSortNULLVector(QuickSort_Iter);
	MassiveGenericSortTest(QuickSort_Iter);
	GenericSortEmptyVector(QuickSort_Iter);
	MassiveGenericSortTestWithNegatives(QuickSort_Iter);*/
	
	/*Insertion sort tests
	
	printf("\nInsertion sort test:\n");
	
	SimpleGenericSort(InsertionSort);
	SimpleGenericSortForSingleMember(InsertionSort);
	GenericSortNULLVector(InsertionSort);
	GenericSortEmptyVector(InsertionSort);
	MassiveGenericSortTest(InsertionSort);
	MassiveGenericSortTestWithNegatives(InsertionSort);*/

	/*Shell sort tests

	printf("\nShell sort test:\n");
	
	SimpleGenericSort(ShellSort);
	SimpleGenericSortForSingleMember(ShellSort);
	GenericSortNULLVector(ShellSort);
	GenericSortEmptyVector(ShellSort);
	MassiveGenericSortTest(ShellSort);
	MassiveGenericSortTestWithNegatives(ShellSort);*/
	
	/*Merge sort tests

	printf("\nMerge sort test:\n");
	
	SimpleGenericSort(MergeSort);
	SimpleGenericSortForSingleMember(MergeSort);
	GenericSortNULLVector(MergeSort);
	GenericSortEmptyVector(MergeSort);
	MassiveGenericSortTest(MergeSort);
	MassiveGenericSortTestWithNegatives(MergeSort);*/
	
	/*Merge sort tests - Iterative

	printf("\nMerge sort - Iterative test:\n");
	
	SimpleGenericSort(MergeSort_Iter);
	SimpleGenericSortForSingleMember(MergeSort_Iter);
	GenericSortNULLVector(MergeSort_Iter);
	GenericSortEmptyVector(MergeSort_Iter);
	MassiveGenericSortTest(MergeSort_Iter);
	MassiveGenericSortTestWithNegatives(MergeSort_Iter);*/
	
	/*Selection sort tests

	printf("\nSelection sort tests:\n");
	
	SimpleGenericSort(SelectionSort);
	SimpleGenericSortForSingleMember(SelectionSort);
	GenericSortNULLVector(SelectionSort);
	GenericSortEmptyVector(SelectionSort);
	MassiveGenericSortTest(SelectionSort);
	MassiveGenericSortTestWithNegatives(SelectionSort);*/
	
	/*Counting sort tests*/

	printf("Counting sort tests:\n");
	
	SimpleCountingSort();
	SimpleCountingSortForSingleMember();
	CountingSortNULLVector();
	CountingSortEmptyVector();
	MassiveCountingSortTest();

	/*Radix sort tests*/

	printf("Radix sort tests:\n");
	
	SimpleRadixSort();
	SimpleRadixSortForSingleMember();
	RadixSortNULLVector();
	RadixSortEmptyVector();
	MassiveRadixSortTest();
	
	return 0;
}


void TimeCompare()
{
	Vector* vec;
	int i, functionsRun, sizes;
	clock_t start, end; 
	float seconds;
	ADTErr(*functions[9])(Vector* _vec) = {BubbleSort, ShakeSort, QuickSort, QuickSort_Iter, InsertionSort, ShellSort, MergeSort, MergeSort_Iter, SelectionSort};
	int vectorSizes[4] = {100, 100, 100, 100};/*TODO check for 10000*/
	
	printf("\nRunning time compare.\n");

	for(sizes = 0; sizes < 4; sizes++)
	{
		printf("\nFor vector of %d integers:\n\n", vectorSizes[sizes]);	
	
		for(functionsRun = 0; functionsRun < 11; functionsRun++)
		{
			vec = VectorCreate(100, 100);

			for(i = 0; i < vectorSizes[sizes]; i++)
			{
				VectorAdd(vec, rand() % 1000);
			}

			if(functionsRun == 9)
			{
				start = clock();
				CountingSort(vec, MAX_NUMBER);
				end = clock();
				seconds = (float)(end - start) / CLOCKS_PER_SEC;
			}
			else if(functionsRun == 10)
			{
				start = clock();
				CountingSort(vec, 3);
				end = clock();
				seconds = (float)(end - start) / CLOCKS_PER_SEC;
			}
			else 
			{
				start = clock();
				functions[functionsRun](vec);
				end = clock();
				seconds = (float)(end - start) / CLOCKS_PER_SEC;
			}

			switch(functionsRun)
			{
				case 0:
					printf("BubbleSort: %f\n", seconds);
					break;
				case 1:
					printf("ShakeSort: %f\n", seconds);
					break;
				case 2:
					printf("QuickSort: %f\n", seconds);
					break;
				case 3:
					printf("QuickSort_Iter: %f\n", seconds);
					break;
				case 4:
					printf("InsertionSort: %f\n", seconds);
					break;
				case 5:
					printf("ShellSort: %f\n", seconds);
					break;
				case 6:
					printf("MergeSort: %f\n", seconds);
					break;
				case 7:
					printf("MergeSort - Iterative: %f\n", seconds);
					break;
				case 8:
					printf("SelectionSort: %f\n", seconds);
					break;
				case 9:
					printf("Counting: %f\n", seconds);
					break;
				case 10:
					printf("Radix: %f\n", seconds);
					break;
			}

			VectorDestroy(vec);
		}
	}
}



/*--------------------------------------------------------------------*/
/*                           Sort tests                               */


void SimpleGenericSort(ADTErr(*SortFunc)(Vector* _vec))
{
	Vector* vec; 
	int a;
	
	vec = VectorCreate(100, 100);
	
	VectorAdd(vec, 46);
	VectorAdd(vec, 2);
	VectorAdd(vec, 83);
	VectorAdd(vec, 41);
	VectorAdd(vec, 102);
	VectorAdd(vec, 5);
	VectorAdd(vec, 17);
	VectorAdd(vec, 31);
	VectorAdd(vec, 64);
	VectorAdd(vec, 49);
	VectorAdd(vec, 18);

	/*VectorPrint(vec);*/

	SortFunc(vec);
	
	/*VectorPrint(vec);*/
	
	VectorDelete(vec, &a);
	
	if(a == 102)
	{
		printf("SimpleSort..................OK\n");
	}	
	else
	{
		printf("SimpleSort..................FAIL\n");
	}
	
	VectorDestroy(vec);
}

void SimpleGenericSortForSingleMember(ADTErr(*SortFunc)(Vector* _vec))
{
	Vector* vec; 
	int a;
	
	vec = VectorCreate(100, 100);
	
	VectorAdd(vec, 5);

	SortFunc(vec);
	
	VectorDelete(vec, &a);
	
	if(a == 5)
	{
		printf("SimpleSortForSingleMember..................OK\n");
	}	
	else
	{
		printf("SimpleSortForSingleMember..................FAIL\n");
	}
	
	VectorDestroy(vec);
}

void GenericSortNULLVector(ADTErr(*SortFunc)(Vector* _vec))
{
	Vector* vec = NULL; 
	
	SortFunc(vec);
	printf("SortNULLVector..................OK\n");
}

void GenericSortEmptyVector(ADTErr(*SortFunc)(Vector* _vec))
{
	Vector* vec = NULL; 
	
	vec = VectorCreate(100, 100);
	
	SortFunc(vec);
	printf("SortEmptyVector..................OK\n");
	
	VectorDestroy(vec);
}

void MassiveGenericSortTest(ADTErr(*SortFunc)(Vector* _vec))
{
	int vectorSize, i, j;
	int num1, num2;
	Vector* vec;
	srand(time(NULL));
	
	for(j = 0; j < RUNS; j++)
	{
		
		vectorSize = rand() % MAX_VECTOR_SIZE;

		vec = VectorCreate(vectorSize, 100);

		for(i = 0; i < vectorSize; i++)
		{
			VectorAdd(vec, rand() % MAX_NUMBER);
		}
		
		SortFunc(vec);
		
		VectorDelete(vec, &num1);

		for(i = 0; i < vectorSize - 1; i++)
		{
			VectorDelete(vec, &num2);
			if(num2 > num1)
			{
				printf("MassiveSortTest..................FAIL\n");
				/*VectorPrint(vec);*/
				VectorDestroy(vec);
				return;
			}
			num1 = num2;
		}

		VectorDestroy(vec);
	}

	printf("MassiveSortTest..................OK\n");
}

void MassiveGenericSortTestWithNegatives(ADTErr(*SortFunc)(Vector* _vec))
{
	int vectorSize, i, j;
	int num1, num2;
	Vector* vec;
	srand(time(NULL));
	
	for(j = 0; j < RUNS; j++)
	{
		
		vectorSize = rand() % MAX_VECTOR_SIZE;

		vec = VectorCreate(vectorSize, 100);
		

		for(i = 0; i < vectorSize; i++)
		{
			i % 2 == 0 ? VectorAdd(vec, rand() % MAX_NUMBER) : VectorAdd(vec, - rand() % MAX_NUMBER);
		}

		SortFunc(vec);

		VectorDelete(vec, &num1);

		for(i = 0; i < vectorSize - 1; i++)
		{
			VectorDelete(vec, &num2);
			if(num2 > num1)
			{
				printf("MassiveSortTestWithNegatives..................FAIL\n");
				VectorDestroy(vec);
				return;
			}
			num1 = num2;
		}

		VectorDestroy(vec);
	}

	printf("MassiveSortTestWithNegatives..................OK\n");
}


/*--------------------------------------------------------------------*/
/*                          Counting Sort tests                       */


void SimpleCountingSort()
{
	Vector* vec; 
	int a;
	
	vec = VectorCreate(100, 100);
	
	VectorAdd(vec, 46);
	VectorAdd(vec, 2);
	VectorAdd(vec, 83);
	VectorAdd(vec, 41);
	VectorAdd(vec, 102);
	VectorAdd(vec, 5);
	VectorAdd(vec, 17);
	VectorAdd(vec, 31);
	VectorAdd(vec, 64);
	VectorAdd(vec, 49);
	VectorAdd(vec, 18);

	CountingSort(vec, 102);
	
	VectorDelete(vec, &a);
	VectorDelete(vec, &a);
	VectorDelete(vec, &a);
	
	if(a == 64)
	{
		printf("SimpleSort..................OK\n");
	}	
	else
	{
		printf("SimpleSort..................FAIL\n");
	}
	
	VectorDestroy(vec);
}

void SimpleCountingSortForSingleMember()
{
	Vector* vec; 
	int a;
	
	vec = VectorCreate(100, 100);
	
	VectorAdd(vec, 5);

	CountingSort(vec, 10);
	
	VectorDelete(vec, &a);
	
	if(a == 5)
	{
		printf("SimpleSortForSingleMember..................OK\n");
	}	
	else
	{
		printf("SimpleSortForSingleMember..................FAIL\n");
	}
	
	VectorDestroy(vec);
}

void CountingSortNULLVector()
{
	Vector* vec = NULL; 
	
	CountingSort(vec, 100);
	printf("SortNULLVector..................OK\n");
}

void CountingSortEmptyVector()
{
	Vector* vec = NULL; 
	
	vec = VectorCreate(100, 100);
	
	CountingSort(vec, 100);
	
	printf("SortEmptyVector..................OK\n");
	
	VectorDestroy(vec);
}

void MassiveCountingSortTest()
{
	int vectorSize, i, j;
	int num1, num2;
	Vector* vec;
	srand(time(NULL));
	
	for(j = 0; j < RUNS; j++)
	{
		
		vectorSize = rand() % MAX_VECTOR_SIZE;

		vec = VectorCreate(vectorSize, 100);

		for(i = 0; i < vectorSize; i++)
		{
			VectorAdd(vec, rand() % MAX_NUMBER);
		}
		
		CountingSort(vec, MAX_NUMBER);
		
		VectorDelete(vec, &num1);

		for(i = 0; i < vectorSize - 1; i++)
		{
			VectorDelete(vec, &num2);
			if(num2 > num1)
			{
				printf("MassiveSortTest..................FAIL\n");
				/*VectorPrint(vec);*/
				VectorDestroy(vec);
				return;
			}
			num1 = num2;
		}

		VectorDestroy(vec);
	}

	printf("MassiveSortTest..................OK\n");
}

/*--------------------------------------------------------------------*/
/*                          Radix Sort tests                       */


void SimpleRadixSort()
{
	Vector* vec; 
	int a;
	
	vec = VectorCreate(100, 100);
	
	VectorAdd(vec, 46);
	VectorAdd(vec, 2);
	VectorAdd(vec, 83);
	VectorAdd(vec, 41);
	VectorAdd(vec, 102);
	VectorAdd(vec, 5);
	VectorAdd(vec, 17);
	VectorAdd(vec, 31);
	VectorAdd(vec, 64);
	VectorAdd(vec, 49);
	VectorAdd(vec, 18);

	RadixSort(vec, 3);
	


	VectorDelete(vec, &a);
	VectorDelete(vec, &a);
	VectorDelete(vec, &a);
	
	if(a == 64)
	{
		printf("SimpleSort..................OK\n");
	}	
	else
	{
		printf("SimpleSort..................FAIL\n");
	}
	
	VectorDestroy(vec);
}

void SimpleRadixSortForSingleMember()
{
	Vector* vec; 
	int a;
	
	vec = VectorCreate(100, 100);
	
	VectorAdd(vec, 5);

	RadixSort(vec, 1);
	
	VectorDelete(vec, &a);
	
	if(a == 5)
	{
		printf("SimpleSortForSingleMember..................OK\n");
	}	
	else
	{
		printf("SimpleSortForSingleMember..................FAIL\n");
	}
	
	VectorDestroy(vec);
}

void RadixSortNULLVector()
{
	Vector* vec = NULL; 
	
	RadixSort(vec, 1);
	printf("SortNULLVector..................OK\n");
}

void RadixSortEmptyVector()
{
	Vector* vec = NULL; 
	
	vec = VectorCreate(100, 100);
	
	RadixSort(vec, 1);
	
	printf("SortEmptyVector..................OK\n");
	
	VectorDestroy(vec);
}

void MassiveRadixSortTest()
{
	int vectorSize, i, j;
	int num1, num2;
	Vector* vec;
	srand(time(NULL));
	
	for(j = 0; j < RUNS; j++)
	{
		
		vectorSize = rand() % MAX_VECTOR_SIZE;

		vec = VectorCreate(vectorSize, 100);

		for(i = 0; i < vectorSize; i++)
		{
			VectorAdd(vec, rand() % MAX_NUMBER);
		}

		RadixSort(vec, 3);

		
		VectorDelete(vec, &num1);

		for(i = 0; i < vectorSize - 1; i++)
		{
			VectorDelete(vec, &num2);
			if(num2 > num1)
			{
				printf("MassiveSortTest..................FAIL\n");
				VectorDestroy(vec);
				return;
			}
			num1 = num2;
		}

		VectorDestroy(vec);
	}

	printf("MassiveSortTest..................OK\n");
}



























