/*
 *      Various sorting algorithms implemented Paul Johnson
 *
 *	The slow O(n^2) have a much smaller number of elements in which to sort.
 *	This was done because they consume significantly more time to sort a 
 *	large random array.
 *
 *      paulie@pauliesworld.org
 *      http://www.pauliesworld.org
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE_NLOGN	320000
#define SIZE_N2		20000

void
swap(int* a, int* b)
{
	if (a != b) {
		*a ^= *b;
		*b ^= *a;
		*a ^= *b;
	}
}


void
print_sorted_array(int A[], int size)
{
	int i;

	for(i = 0; i < size; i++) {
		printf("%i\n",A[i]);
	}
}

void
shell_sort(int A[])
{
	int i, j, inc, tmp;

	inc = SIZE_NLOGN/2;

	while (inc > 0) {
		for (i = 0; i < SIZE_NLOGN; i++) {
      			tmp = A[i];
			j = i;

      			while ((j >= inc) && (A[j-inc] > tmp)) {
				A[j] = A[j-inc];
				j = j-inc;
			}

			A[j] = tmp;
		}
		inc = inc/2;
	}
}

void
heap_sort(int A[])
{
	int i, j, tmp, parent, child;

	i = SIZE_NLOGN;
	j = i/2;
 
	while (1) {
		if (j > 0) {
			j--;
			tmp = A[j];
		} else {
			i--;
			if (i == 0) {
				break;
			}

			tmp = A[i];
			A[i] = A[0];
		}
 
		parent = j;
		child = j*2 + 1;
 
		while (child < i) {
			if (((child+1) < i) && (A[child+1] > A[child])) {
				child++;
			}

			if (A[child] > tmp) {
				A[parent] = A[child];
				parent = child;
				child = parent*2 + 1;
			} else {
				break;
			}
		}

		A[parent] = tmp;
	}
}

void
merge(int A[], int B[], int first, int middle, int last)
{
	int i, start, size, tmp;

	start = middle-1;
	size = last-first+1;
	tmp = first;

	while(first <= start && middle <= last) {
		if(A[first] <= A[middle] ) {
			B[tmp++] = A[first++];
		} else {
			B[tmp++] = A[middle++];
		}
	}

	while(first <= start) {
		B[tmp++] = A[first++];
	}

	while(middle <= last) { 
		B[tmp++] = A[middle++];
	}

	for(i = 0; i < size; i++, last--) {
                A[last] = B[last];
	}
}

void
merge_sort(int A[], int B[], int left, int right)
{
	int middle;

	if(left < right) {
		middle = (left+right)/2;
		merge_sort(A,B,left,middle);
		merge_sort(A,B,middle+1,right);
		merge(A,B,left,middle+1,right);
	}
}


void
quick_sort(int A[], int min, int max)
{
	int i, j, tmp;

	i = min;
	j = max;
	tmp = A[(min+max)/2];

	while (i <= j) {
		while(A[i] < tmp) {
			i++;
		}

		while(A[j] > tmp) {
			j--;
		}

		if(i <= j) {
			swap(&A[i], &A[j]);
			i++;
			j--;
		}
	}

	if(j > min) {
		quick_sort(A, min, j);
	}

	if(i < max) {
		quick_sort(A, i, max);
	}
}

void
selection_sort(int A[])
{
	int i, j, min;

	for (i = 0; i < SIZE_N2; i++) {
		min = i;
		for (j = i; j < SIZE_N2; j++) {
			if (A[min] > A[j]) {
				min = j;
			}
		}
		swap(&A[i], &A[min]);
	}
}

void
insertion_sort(int A[])
{
	int i, j, tmp;

	for (i = 0; i < SIZE_N2; i++) {
		tmp = A[i];

		for (j = i-1; j >= 0; j--) {
			if (A[j] <= tmp) {
				break;
			}

			A[j+1] = A[j];
		}
		A[j+1] = tmp;
	}
}

void
bubble_sort(int A[])
{
	int i, j;

	for (i = 0; i < SIZE_N2; i++) {
		for (j = 0; j < SIZE_N2-1; j++) {
			if (A[j] > A[j+1]) {
				swap(&A[j], &A[j+1]);
			}
		}
	}
}

int
main()
{
	int i;

	int A_1[SIZE_N2],A_2[SIZE_N2],A_3[SIZE_N2];
	int A_4[SIZE_NLOGN],A_5[SIZE_NLOGN],A_6[SIZE_NLOGN];
	int A_7[SIZE_NLOGN],A_8[SIZE_NLOGN],A_9[SIZE_NLOGN];
	clock_t t0, t1;


	for(i=0; i<SIZE_N2; i++) {
		A_1[i] = rand()%SIZE_N2;
	}

	for(i=0; i<SIZE_NLOGN; i++) {
		A_4[i] = rand()%SIZE_NLOGN;
	}

	memcpy(A_2,A_1,SIZE_N2);
	memcpy(A_3,A_1,SIZE_N2);
	memcpy(A_5,A_4,SIZE_NLOGN);
	memcpy(A_6,A_4,SIZE_NLOGN);
	memcpy(A_7,A_4,SIZE_NLOGN);
	memcpy(A_8,A_4,SIZE_NLOGN);
	memcpy(A_9,A_4,SIZE_NLOGN);

	printf("Algorithm\tComplexity\tSpeed\tTime (sec)\n");
	printf("---------------------------------------------------\n");

	printf("Bubble Sort\tO(n^2)\t\tSLOW\t");
	t0=clock();
	bubble_sort(A_1);
	t1=clock();

	printf("%6.6f \n",(double)(t1-t0)/CLOCKS_PER_SEC);
	printf("Selection Sort\tO(n^2)\t\tSLOW\t");

	t0=clock();
	selection_sort(A_2);
	t1=clock();

	printf("%6.6f \n",(double)(t1-t0)/CLOCKS_PER_SEC);
	printf("Insertion Sort\tO(n^2)\t\tSLOW\t");

	t0=clock();
	insertion_sort(A_3);
	t1=clock();

	printf("%6.6f \n",(double)(t1-t0)/CLOCKS_PER_SEC);
	printf("Shell Sort\tO(n log^2 n)\tFAST\t");

	t0=clock();
	shell_sort(A_5);
	t1=clock();

	printf("%6.6f \n",(double)(t1-t0)/CLOCKS_PER_SEC);
	printf("Merge Sort\tO(n log n)\tFASTEST\t");

	t0=clock();
	merge_sort(A_6,A_7,0,SIZE_NLOGN-1);
	t1=clock();

	printf("%6.6f \n",(double)(t1-t0)/CLOCKS_PER_SEC);
	printf("Quick Sort\tO(n log n)\tFASTEST\t");

	t0=clock();
	quick_sort(A_8,0,SIZE_NLOGN-1);
	t1=clock();

	printf("%6.6f \n",(double)(t1-t0)/CLOCKS_PER_SEC);
	printf("Heap Sort\tO(n log n)\tFASTEST\t");

	t0=clock();
	heap_sort(A_9);
	t1=clock();
        
	printf("%6.6f \n",(double)(t1-t0)/CLOCKS_PER_SEC);
}
