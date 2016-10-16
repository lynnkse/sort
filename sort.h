/** @file sort.h
 *  @brief Bubble Sort and Shake Sort on Vector
 *
 *  @author Anton Gulyaev
 *
 *  @bug No known bugs.
 */

#ifndef __SORT_H__
#define __SORT_H__

#include "../ADTDefs.h"
#include "../vector/vector.h"
#include "../stack/stack.h"

/** @brief Sort Vector with Bubble sort algorithm
 * @param _vec: pointer to vector to be sorted
 * @return ADTErr error codes
 */
ADTErr BubbleSort(Vector* _vec);
 
/** @brief Sort Vector with Shake sort algorithm
 * @param _vec: pointer to vector to be sorted
 * @return ADTErr error codes
 */
ADTErr ShakeSort(Vector* _vec); 

/** @brief Sort Vector with Quick sort algorithm
 * @param _vec: pointer to vector to be sorted
 * @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 */
ADTErr QuickSort(Vector* _vec);

/** @brief Sort Vector with Quick sort algorithm. Iterative implementation
 * @param _vec: pointer to vector to be sorted
 * @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 */
ADTErr QuickSort_Iter(Vector* _vec);

/** @brief Sort Vector with Insertion sort
 * @param _vec: pointer to vector to be sorted
 * @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 */
ADTErr InsertionSort(Vector* _vec);

/** @brief Sort Vector with Shell sort
 * @param _vec: pointer to vector to be sorted
 * @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 */
ADTErr ShellSort(Vector* _vec);

/** @brief Sort Vector with Merge sort
 * @param _vec: pointer to vector to be sorted
 * @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 */
ADTErr MergeSort(Vector* _vec);

/** @brief Sort Vector with Merge sort(Iterative implementation)
 * @param _vec: pointer to vector to be sorted
 * @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 */
ADTErr MergeSort_Iter(Vector* _vec);

/** @brief Sort Vector with Selection sort
 * @param _vec: pointer to vector to be sorted
 * @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 */
ADTErr SelectionSort(Vector* _vec);

/** @brief Sort Vector with Counting sort
 * @param _vec: pointer to vector to be sorted
 * @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 */
ADTErr CountingSort(Vector* _vec, int _maxValue);

/** @brief Sort Vector with Radix sort
 * @param _vec: pointer to vector to be sorted
 * @return ADTErr error codes. ERR_OK in case of success, ERR_NOT_INITIALIZED in case of NULL vector
 */
ADTErr RadixSort(Vector* _vec, int _nDigits);

#endif /*__SORT_H__*/




