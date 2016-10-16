/** @file sort.c
 *  @brief Implementation of sort algorithms:
 *  @algorithm BubbleSort
 *  @algorithm ShakeSort
 *  @algorithm QuickSort(recursive implementation)
 *  @algorithm QuickSort(iterative implementation)
 *  @algorithm InsertionSort
 *  @algorithm ShellSort
 *
 *  @author Anton Gulyaev
 *
 *  @last_update 22.07.16
 *
 *  @bug No known bugs.
 */

#include "../ADTDefs.h"
#include "../vector/vector.h"
#include "sort.h"
#include "../stack/stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*----------------------------------------------------------------------------------------------*/
/*                           Static functions declarations                                      */

/** @brief choose pivot index. Returns _begin at the moment
	@return size_t pivot index
	@retval returns _begin, index of first element of the vector
 */  
static size_t ChoosePivotIndex(Vector* _vec, size_t _begin, size_t _end);

/** @brief Quick sort recursive function. Sorts sub-vector inside of given vector
 *  @param _vec: pointer to a vector to be sorted
 *  @param _begin: index of the beginning of the sub-vector
 *  @param _end: index of the end of the sub-vector
 *	@return void
 */ 
static void QuickRec(Vector* _vec, size_t _begin, size_t _end);

/** @brief Swaps member values inside vector. Recieves both indexes and values of the members to be swapped
 *  @param _vec: pointer to the vector
 *  @param _indexA: index of the first member
 *  @param _indexA: index of the second member
 *  @param _a: value of the first member
 *  @param _b: value of the second member
 *	@return void
 */ 
static void VectorSwap(Vector* _vec, size_t _indexA, size_t _indexB, int _a, int _b);

/** @brief Partitions vector into two sorted sub-vectors devided by the pivot
 *  @param _vec: pointer to the vector 
 *  @param _pivotIndex: current pivot index
 *  @param _begin: beginning of sub-vector index
 *  @param _end: end of sub-vector index
 *	@return pivot index
 */ 
static size_t Partition(Vector* _vec, size_t _begin, size_t end);

/** @brief Inserts member into sorted part of the vector
 *  @param _vec: pointer to the vector 
 *  @param _insertedIndex: current index of the vector to be inserted
 *	@return void
 */ 
static void InsertMember(Vector* _vec, size_t _insertedIndex, size_t gap);

/** @brief Sorts sub-vector containing members devided by given gap
 *  @param _vec: pointer to the vector 
 *  @param _gap: gap between the members of sub-vector
 *	@return void
 */ 
static void SortSubVector(Vector* _vec, size_t _gap);

/** @brief Pushes item either forward or backwards during Shake sort
 *  @param _vec: pointer to the vector 
 *  @param _runIndex: nubmer of times outer loop in Shake sort already ran. This is to make sure we're not iterating over alerady sorted items
 *  @param _isForward: 1 - moving forward, 0 - backwards
 *	@return int
 *  @retval: returns 1 if there were shifts or 0 if there weren't. Returned 0 would mean that vector is sorted alreaady
 */ 
static int PushItemForwardBack(Vector* _vec, int runIndex, int _isForward);

/*TODO add header*/
static void MergeRec(Vector* _vec, int _begin, int _end);
static void Merge(Vector* _vec, int _end1, int _begin2, int _end2);
/*static void FillFrequencies(Vector* _vec, int* _freq, size_t freqLength);*/
static void SortByDigit(Vector* _vec, int digit);
/*-----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
/*                                  API Function Defenitions                                    */


/** @brief Sort Vector with Bubble sort algorithm
 *  @param _vec: pointer to vector to be sorted
 *  @return ADTErr error codes
 */ 
ADTErr BubbleSort(Vector* _vec)
{
	size_t vectorSize;
	ADTErr result;
	int a, b;
	int runIndex, itemIndex;
	int hasSwapped = 1;
 	
 	/*get number of items and check if it worked*/
 	result = VectorItemsNum(_vec, &vectorSize);
 	if(ERR_OK != result)
 	{
 		return result;
 	}
 	
 	/*run bubble sort on vector. Use Vector API functions to get and set values inside vector*/
 	for(runIndex = 0; runIndex < vectorSize && 1 == hasSwapped; runIndex++)
 	{
 		hasSwapped = 0;
 		for(itemIndex = 0; itemIndex < vectorSize - runIndex - 1; itemIndex++)
 		{
 			/*get values*/
 			VectorGet(_vec, itemIndex, &a);
			VectorGet(_vec, itemIndex + 1, &b);
 			
 			if(a > b)
 			{
 				/*place each value in place of another*/
 				VectorSet(_vec, itemIndex, b);
				VectorSet(_vec, itemIndex + 1, a);
				
				hasSwapped = 1;
 			}
 		}
 	}
 	
 	return ERR_OK;
}

/** @brief Sort Vector with Shell sort
 *  @param _vec: pointer to vector to be sorted  
 *	@return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 *  @static_function_used: SortSubVector
 */
ADTErr ShellSort(Vector* _vec)
{
	size_t numOfItems, gap;
	/*NULL pointer check*/
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(numOfItems <= 1)
	{
		return ERR_OK;
	}

	/*set gap as number of items devided by two*/
	VectorItemsNum(_vec, &numOfItems);
	gap = numOfItems / 2;

	/*continue until gap is equal to 1*/
	while(gap >= 1)
	{
		SortSubVector(_vec, gap);
		gap /= 2;
	}

	/*Run insertion sort on what's left. Suppose to be almost best-case, so complexity of this operation is almost O(n)*/
	

	return ERR_OK;
}

/** @brief Sort Vector with Insertion sort
 *  @param _vec: pointer to vector to be sorted
 *  @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 *  @static_function_used: InsertMember
 */
ADTErr InsertionSort(Vector* _vec)
{
	size_t numOfItems;
	int i;
	ADTErr result;
	/*NULL pointer check*/
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	result = VectorItemsNum(_vec, &numOfItems);
	if(ERR_OK != result)
	{
		return result;
	}
	
	if(numOfItems <= 1)
	{
		return ERR_OK;
	}
	
	/*start with second member, first is sorted already*/
	for(i = 1; i < numOfItems; i++)
	{
		InsertMember(_vec, i, 1);
	}
	
	return ERR_OK;
}

/** @brief Sort Vector with Shake sort algorithm
 *  @param _vec: pointer to vector to be sorted
 *  @return ADTErr error codes
 *  @static_function_used: PushItemForwardBack 
 */
ADTErr ShakeSort(Vector* _vec)
{
	size_t vectorSize;
	ADTErr result;
	int runIndex;
	int hasSwapped = 1;
 	
 	/*get number of items and check if it worked*/
 	result = VectorItemsNum(_vec, &vectorSize);
 	if(ERR_OK != result)
 	{
 		return result;
 	}
 	 	
 	/*run bubble sort on vector. Use Vector API functions to get and set values inside vector*/
 	for(runIndex = 0; runIndex < vectorSize / 2 && 1 == hasSwapped; runIndex++)
 	{	
 		/*run forwad*/
 		hasSwapped = PushItemForwardBack(_vec, runIndex, 1);

		if(!hasSwapped)
		{
			break;
		}

 		/*run backwards*/
		hasSwapped = PushItemForwardBack(_vec, runIndex, 0);
	
		if(!hasSwapped)
		{
			break;
		}
 	}
 	
 	return ERR_OK;
}

/** @brief Sort Vector with Quick sort algorithm. Iterative implementation
 *  @param _vec: pointer to vector to be sorted
 *  @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 *  @static_function_used: ChoosePivotIndex
 *  @static_function_used: Partition
 */
ADTErr QuickSort_Iter(Vector* _vec)
{
	ADTErr result;
	size_t numOfItems;
	Stack* stack;
	int begin, end, pivotIndex;

	result = VectorItemsNum(_vec, &numOfItems);
	
	if(ERR_OK != result)
	{
		return result;
	}
	
	stack = StackCreate(100, 100);
	
	if(NULL == stack)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	/*in case of empty vector or single item, return*/	
	if(numOfItems <= 1)
	{
		return ERR_OK;
	}
	
	/*push beginning index, then end index to stack*/
	StackPush(stack, 0);
	StackPush(stack, numOfItems - 1);
	
	while(!StackIsEmpty(stack))
	{
		/*pop end index, then beginning index*/
		StackPop(stack, &end);
		StackPop(stack, &begin);
		
		/*get subvector and partition it*/
		pivotIndex = Partition(_vec, begin, end);
		
		/*add two resulting sub-vectors to stack for sorting it, if possible*/
		if(pivotIndex > begin)
		{
			StackPush(stack, begin);
			StackPush(stack, pivotIndex - 1);
		}
		if(pivotIndex < end)
		{
			StackPush(stack, pivotIndex + 1);
			StackPush(stack, end);
		}
	}
	StackDestroy(stack);
	return ERR_OK;
}

/** @brief Sort Vector with Quick sort algorithm. Recursive implementation
 *  @param _vec: pointer to vector to be sorted
 *  @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 *  @static_function_used: QuickRec
 */
ADTErr QuickSort(Vector* _vec)
{
	ADTErr result;
	size_t numOfItems;

	result = VectorItemsNum(_vec, &numOfItems);	
	
	if(ERR_OK != result)
	{
		return result;
	}
	
	if(numOfItems > 1)
	{
		QuickRec(_vec, 0, numOfItems - 1);
	}
	
	return ERR_OK;
}

/** @brief Sort Vector with Merge sort algorithm. Recursive implementation
 *  @param _vec: pointer to vector to be sorted
 *  @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 *  @static_function_used: MergeRec
 */
ADTErr MergeSort(Vector* _vec)
{
	size_t numOfItems;

	/*NULL pointer check*/
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);
	
	/*if empty vector or single item, no sorting neccessary*/
	if(numOfItems <= 1)
	{
		return ERR_OK;
	}
	
	MergeRec(_vec, 0, numOfItems - 1);
	
	return ERR_OK;
}

/*TODO not finished!*/
ADTErr MergeSort_Iter(Vector* _vec)
{
	size_t numOfItems;
	int i;


	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);
	

	if(numOfItems <= 1)
	{
		return ERR_OK;
	}
	
	for(i = 0; i < numOfItems - 1; i++)
	{
		Merge(_vec, 0, i + 1, i + 1);
	}
	
	return ERR_OK;
}

/** @brief Sort Vector with Selection sort algorithm
 *  @param _vec: pointer to vector to be sorted
 *  @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 *  @static_function_used: MergeRec
 */
ADTErr SelectionSort(Vector* _vec)
{
	size_t numOfItems, minIndex;
	int itemIndex, runIndex, min, temp;
	/*NULL pointer check*/
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);
	
	if(numOfItems <= 1)
	{
		return ERR_OK;
	}
	
	/*TODO make findMinElement function*/
	
	for(runIndex = 0; runIndex < numOfItems - 1; runIndex++)
	{
		VectorGet(_vec, runIndex, &min);
		for(itemIndex = runIndex; itemIndex < numOfItems; itemIndex++)
		{
			VectorGet(_vec, itemIndex, &temp);
			if(temp < min)
			{
				min = temp;
				minIndex = itemIndex;	
			}
		}
		VectorGet(_vec, runIndex, &temp);
		if(temp > min)
		{
			VectorSwap(_vec, runIndex, minIndex, temp, min);
		}
	}
	
	return ERR_OK;
}


ADTErr CountingSort(Vector* _vec, int _maxValue)
{
	/*TODO check maxValue range*/
	int i, item, prevSum;
	size_t numOfItems;
	int* resultArray;
	int* frequencies = (int*) calloc((_maxValue + 1), sizeof(int));
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);
	

	if(numOfItems <= 1)
	{
		return ERR_OK;
	}
	
	resultArray = (int*) malloc(sizeof(int) * numOfItems);
	
	/*TODO check that item isin in correct range*/
	for(i = 0; i < numOfItems; i++)
	{
		VectorGet(_vec, i, &item);
		frequencies[item]++;
	}
	
	/*cumulative frequencies*/
	for(i = 1; i <= _maxValue; i++)
	{
		prevSum = frequencies[i - 1];
		frequencies[i] += prevSum;
	}
	
	for(i = numOfItems - 1; i >= 0; i--)
	{
		VectorGet(_vec, i, &item);
		resultArray[frequencies[item] - 1] = item;
		frequencies[item]--;
	}
	
	for(i = 0; i < numOfItems; i++)
	{
		VectorSet(_vec, i, resultArray[i]);
	}
	
	free(frequencies);
	free(resultArray);
	
	return ERR_OK;
}

ADTErr RadixSort(Vector* _vec, int _nDigits)
{
	/*TODO make generic with f. pointer*/
	size_t numOfItems;
	int digit;
	
	if(NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);
	
	if(numOfItems <= 1)
	{
		return ERR_OK;
	}
	
	for(digit = 1; digit <= _nDigits; digit++)
	{
		SortByDigit(_vec, digit);
	}
	
	return ERR_OK;
}
/*----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/
/*                                Static Functions Defenitions                                  */

static size_t Partition(Vector* _vec, size_t _begin, size_t _end)
{
	int a, b, pivot;
	size_t pivotIndex = ChoosePivotIndex(_vec, _begin, _end);
	
	/*place pivot in the beginning if it isn't there yet*/	
	if(pivotIndex != _begin)
	{
		VectorGet(_vec, pivotIndex, &pivot);
		VectorGet(_vec, _begin, &a);
		VectorSwap(_vec, pivotIndex, _begin, pivot, a);
	}

	VectorGet(_vec, pivotIndex, &pivot);
	pivotIndex = _begin;

	/*pivot is on the first position so start with second*/	
	_begin++;

	while(_end >= _begin)
	{
		VectorGet(_vec, _begin, &a);
		VectorGet(_vec, _end, &b);
		
		if(b <= pivot && a > pivot)
		{
			VectorSwap(_vec,  _begin, _end, a, b);
			_begin++;
			_end--;
		}
		else
		{
			if(a <= pivot)
			{
				_begin++;
			}
		
			if(b > pivot)
			{
				_end--;
			}
		}
	}
	
	/*place the pivot in its place*/
	VectorGet(_vec, _end, &b);
	VectorSwap(_vec, pivotIndex, _end, pivot, b);

	/*return the position of the pivot*/	
	return _end;
}

static void QuickRec(Vector* _vec, size_t _begin, size_t _end)
{
	size_t pivotIndex;
	/*put pivot in the first place*/
	pivotIndex = Partition(_vec, _begin, _end);

	/*enter recursion if there are more than one member in each sub-vector. Single-memberd vector is base case*/
	if(pivotIndex < _end)
	{
		QuickRec(_vec, pivotIndex + 1, _end);
	}	
	if(pivotIndex > _begin)
	{
		QuickRec(_vec, _begin, pivotIndex - 1);
	}
}

static size_t ChoosePivotIndex(Vector* _vec, size_t _begin, size_t _end)
{
	return _begin;
}

static void VectorSwap(Vector* _vec, size_t _indexA, size_t _indexB, int _a, int _b)
{
	VectorSet(_vec, _indexA, _b);
	VectorSet(_vec, _indexB, _a);
}


static void InsertMember(Vector* _vec, size_t _insertedIndex, size_t _gap)
{
	int insertedMember, prevMember;

	while(_insertedIndex > _gap - 1)
	{
		VectorGet(_vec, _insertedIndex, &insertedMember);
		VectorGet(_vec, _insertedIndex - _gap, &prevMember);
	
		if(insertedMember < prevMember)
		{
			VectorSwap(_vec, _insertedIndex - _gap, _insertedIndex, prevMember, insertedMember);
			_insertedIndex -= _gap;
		}
		else
		{
			break;/*no swap - means we found the right place*/
		}
	}
}
 

static void SortSubVector(Vector* _vec, size_t _gap)
{
	size_t run = 0, vectorSize;
	
	/*get the number of items in a vector*/
	VectorItemsNum(_vec, &vectorSize);

	/*run until index of element we start with plus gap will exeed the length of the vector, i.e. no items to sort*/
	while(run + _gap < vectorSize)	
	{	
		
		InsertMember(_vec, run + 1, _gap);
		
		/*sub-vector is sorted, start next iteration from next item*/			
		run++;
	}
}

static int PushItemForwardBack(Vector* _vec, int _runIndex, int _isForward)
{
	int itemIndex;
	int hasSwapped = 0;
	size_t vectorSize;
	int a, b;	

	VectorItemsNum(_vec, &vectorSize);
	
	if(_isForward)
	{
		for(itemIndex = 0; itemIndex < vectorSize - _runIndex - 1; itemIndex++)
		{
			/*get values*/
			VectorGet(_vec, itemIndex, &a); 
			VectorGet(_vec, itemIndex + 1, &b);
		
			if(a > b)
			{
				VectorSwap(_vec, itemIndex, itemIndex + 1, a,  b); 				
				hasSwapped = 1;
			}
		}
	}
	else
	{
		for(itemIndex = vectorSize - _runIndex - 2; itemIndex >= 1 + _runIndex; itemIndex--)
		{
			/*get values*/
			VectorGet(_vec, itemIndex, &a);
			VectorGet(_vec, itemIndex - 1, &b);
	
			if(a < b)
			{
				VectorSwap(_vec, itemIndex, itemIndex - 1, a,  b); 					
				hasSwapped = 1;
			}
		}
	}
	return hasSwapped;
}

static void MergeRec(Vector* _vec, int _begin, int _end)
{
	int endOfFirst;
	/*TODO what if more than INT_MAX?*/	
	endOfFirst = _begin + (_end - _begin) / 2;
	
	if(_begin < endOfFirst)
	{
		MergeRec(_vec, _begin, endOfFirst);
	}
	
	if(endOfFirst + 1 < _end)
	{
		MergeRec(_vec, endOfFirst + 1, _end);
	}
	
	Merge(_vec, _begin, endOfFirst + 1, _end);
}

static void Merge(Vector* _vec, int _begin1, int _begin2, int _end2)
{
	/*TODO what if vectora only one in length?*/
	Vector* tempVec;
	size_t index1, index2;
	int item1, item2, i = 0;
	int _end1 = _begin2 - 1;
	
	tempVec = VectorCreate(100, 100);
	
	/*TODO return if vector didnt careate*/
	
	index1 = _begin1;
	index2 = _begin2;
	
	while(index1 <= _end1 && index2 <= _end2)
	{
		VectorGet(_vec, index1, &item1);/*TODO insert thise into if's*/
		VectorGet(_vec, index2, &item2);
	
		if(item1 < item2)
		{
			VectorAdd(tempVec, item1);
			index1++;
		}
		else if(item2 < item1)
		{
			VectorAdd(tempVec, item2);
			index2++;
		}
		else
		{
			VectorAdd(tempVec, item1);/*TODO no need this*/
			VectorAdd(tempVec, item2);
			index1++;
			index2++;	
		}		
	}
	
	while(index1 <= _end1)
	{
		VectorGet(_vec, index1, &item1);
		VectorAdd(tempVec, item1);
		index1++;
		
	}
	
	while(index2 <= _end2)
	{
		VectorGet(_vec, index2, &item2);
		VectorAdd(tempVec, item2);
		index2++;	
	}
	
	while(_begin1 <= _end2)
	{
		VectorGet(tempVec, i, &item1);
		VectorSet(_vec, _begin1, item1);
		_begin1++;
		i++;
	}
	
	VectorDestroy(tempVec);
}

static void SortByDigit(Vector* _vec, int digit)
{
	/*digit enumeration starts with 1*/	
	int i, item, prevSum;
	size_t numOfItems;
	int* resultArray;
	int* frequencies = (int*) calloc(10, sizeof(int));
	if(NULL == _vec)
	{
		return;
	}
	
	VectorItemsNum(_vec, &numOfItems);

	resultArray = (int*) malloc(sizeof(int) * numOfItems);
	
	for(i = 0; i < numOfItems; i++)
	{
		VectorGet(_vec, i, &item);
		frequencies[(item % (int)pow(10, digit))/(int)pow(10, digit - 1)]++;
	}
	
	/*cumulative frequencies*/
	for(i = 1; i < 10; i++)
	{
		prevSum = frequencies[i - 1];
		frequencies[i] += prevSum;
	}
	
	for(i = numOfItems - 1; i >= 0; i--)
	{
		VectorGet(_vec, i, &item);

		resultArray[frequencies[(item % (int)pow(10, digit))/(int)pow(10, digit - 1)] - 1] = item;
		

		frequencies[(item % (int)pow(10, digit))/(int)pow(10, digit - 1)]--;
	}
	
	for(i = 0; i < numOfItems; i++)
	{
		VectorSet(_vec, i, resultArray[i]);
	}
	
	/*VectorPrint(_vec);*/

	free(resultArray);
	free(frequencies);	

	return;
}
/*----------------------------------------------------------------------------------------------*/













































































