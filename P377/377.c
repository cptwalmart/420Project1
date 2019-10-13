// 420 Project 1
// Problem #377
// How to compile
// make

#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int global_sum[1] = {0};
int global_sum_size = 1;


struct Number{
	int* arr;
	int size;
};
struct Number globalSum;

unsigned long long int getNumFromIntArray(int* arr, int size){
	int i;
	unsigned long long int cur;
	cur = 0;
	for (i = 0; i < size; i++){
		/* printf("CurL : %d\n", arr[i]); */
		cur = 10 * cur + arr[i];
		/* printf("K: %d\n", cur); */
	}
	return cur;
}

void printNumber(int* arr, int arr_size){
	int i;
	for (i = 0; i < arr_size; i++){
		printf("%d", arr[i]);
	}
	printf("\n");
}

int * intdup(int const * src, size_t len){
	int * p = malloc(len * sizeof(int));
	memcpy(p, src, len * sizeof(int));
	return p;
}

int * insertAtFront(int value, int* arr, int size){
	int *new_arr, i;
	new_arr = malloc((size+1) * sizeof(int));
	new_arr[0] = value;
	for (i = 1; i < size+1; i++){
		new_arr[i] = arr[i-1];
	}	
	free(arr);
	return new_arr;
}


struct Number addArrays(int* arr1, int* arr2, int arr1_size, int arr2_size){
	int *new_arr, *tmp_arr, *tmp_arr2, tmp_arr_size;
	if (arr1_size >= arr2_size){
		int diff, i;
		diff = arr1_size - arr2_size;
		tmp_arr = malloc(arr1_size * sizeof(int));
		tmp_arr_size = arr1_size;
		
		for (i = 0; i < arr1_size; i++){ //Pad smaller array with 0s
			if (i < diff){
				tmp_arr[i] = 0;
			}
			else {
				tmp_arr[i] = arr2[i - diff];
			}
		}	
		tmp_arr2 = intdup(arr1, arr1_size);
	}
	else{
		int diff, i;
		diff = arr2_size - arr1_size;
		tmp_arr = malloc(arr2_size * sizeof(int));
		tmp_arr_size = arr2_size;
		
		for (i = 0; i < arr2_size; i++){ //Pad smaller array with 0s
			if (i < diff){
				tmp_arr[i] = 0;
			}
			else {
				tmp_arr[i] = arr1[i - diff];
			}
		}	
		tmp_arr2 = intdup(arr2, arr2_size);
	}	

	int j, carry;
	carry = 0;
	new_arr = malloc(tmp_arr_size * sizeof(int));
	for (j = tmp_arr_size-1; j >= 0; j--){
		int digit, diff;
		digit = tmp_arr2[j] + tmp_arr[j];
		if (digit > 9){ //Need to carry 
			diff = digit - 10;	
			new_arr[j] = diff;
			if (j > 0){
				tmp_arr[j-1] += 1;
			}
			else {
				carry = 1;
			}
		}
		else {
			new_arr[j] = digit; 
		}
	}
	free(tmp_arr);
	free(tmp_arr2);
	/* free(arr1); */
	/* free(arr2); */

	if (carry == 1){
		new_arr = insertAtFront(1, new_arr, tmp_arr_size);
	/* printNumber(tmp_arr2, tmp_arr_size); */
	/* printNumber(tmp_arr, tmp_arr_size); */
	/* printNumber(new_arr, tmp_arr_size + 1); */
		 struct Number num  = {new_arr, tmp_arr_size + 1};
		 return num;
	}
	else {
	/* printNumber(tmp_arr2, tmp_arr_size); */
	/* printNumber(tmp_arr, tmp_arr_size); */
	/* printNumber(new_arr, tmp_arr_size); */
		struct Number num = {new_arr, tmp_arr_size};
		return num;
	}

}


//n_sum = target digital sum
//l = current digit length being tested
//prev = previous digits in recursion 
//orig_size = l at the first iteration
void findNumsWithDigitalSum(int n_sum, int l, int* prev, int orig_size){ 

	if (l == 1){ //Base case. Gather permutation
		prev[orig_size-l] = n_sum;

		int i, j;
		for (j = 0; j < orig_size; j++){ //Check if array has an 2-digit numbers
			if (prev[j] > 9){
				return;
			}
		}

		/* printNumber(prev, orig_size); */
		globalSum = addArrays(globalSum.arr, prev, globalSum.size, orig_size);
		printf("Sum: ");
		printNumber(globalSum.arr, globalSum.size);

		/* global_sum = addArrays(global_sum, prev, global_sum_size, orig_size); */

		/* unsigned long long int num; */
		/* num = getNumFromIntArray(prev, orig_size); */
		/* printf("CHECK: %lld\n", num); */
		return;
	}

	int first_digit_max, i; 
	first_digit_max = n_sum - (l - 1);

	for (i = 1; i <= first_digit_max; i++){
		int left, spot;
		left = n_sum - i;
		spot = orig_size - l;
		prev[spot] = i;


		findNumsWithDigitalSum(left, l-1, prev, orig_size); //Recurse with l = l-1 and n_sum = remaining digital sum


	}
}


int main(int argc, char* argv[]){
	int digital_sum, result, l, *tmp_prev, i;
	digital_sum = atoi(argv[1]);
	int arr_zero[1] = {0};
	/* globalSum = {arr_zero, 1}; */
	globalSum.arr = arr_zero;
	globalSum.size = 1;
	/* l = atoi(argv[2]); */
	
	/* l = 3; */
	for (i = 1; i <= digital_sum; i++){
		tmp_prev = malloc(i*sizeof(int));
		findNumsWithDigitalSum(digital_sum, i, tmp_prev, i); 
	}
	free(tmp_prev);

	/* int arr1[2] = {7, 4}; */
	/* int arr2[2] = {4, 1}; */
	/* struct Number num; */
	/* num = addArrays(arr2, arr1, 2, 2); */
}

