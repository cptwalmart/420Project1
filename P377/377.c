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

int nprocs, me;

struct Number{
	int* arr;
	int size;
};
struct Number globalSum;


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
	free(arr1);

	if (carry == 1){
		new_arr = insertAtFront(1, new_arr, tmp_arr_size);
		struct Number num  = {new_arr, tmp_arr_size + 1};
		return num;
	}
	else {
		struct Number num = {new_arr, tmp_arr_size};
		return num;
	}

}

struct Number scatter(int me, int nprocs, int sequ_size){
	int  blocksize, orig, *my_block, *arr, k;
	/* int arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; */
	arr = malloc(sequ_size * sizeof(int));
	for (k = 1; k <= sequ_size; k++){
		arr[k-1] = k;
	}
	
	if (nprocs <=  sequ_size){
		blocksize = sequ_size/nprocs;
		orig = blocksize;

		int left = sequ_size % nprocs;
		
		int startIndex = (me * orig);

		if (me < left)		
			my_block = malloc((blocksize+1)*sizeof(int));
		else {
			my_block = malloc(blocksize*sizeof(int));
		}
		int i;
		for (i = 0; i < blocksize; i++){
			my_block[i] = arr[startIndex + i];
		}
		if (me < left){
			blocksize += 1;
			my_block[i] = arr[sequ_size - (me + 1)];

		}
	}
	else {
		blocksize = 1;
		my_block = malloc(blocksize*sizeof(int));
		if (me < sequ_size){
			my_block[0] = arr[me];
		}
		else {
			my_block[0] = 0;
		}
	}
	/* printf("BLOCK FOR NODE: %d\n", me); */
	/* printNumber(my_block, blocksize); */
	struct Number num = {my_block, blocksize};
	return num;

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

		/* printf("For node %d: ", me); */
		/* printNumber(prev, orig_size); */
		globalSum = addArrays(globalSum.arr, prev, globalSum.size, orig_size);
		return;
	}

	int first_digit_max, i; 
	first_digit_max = n_sum - (l - 1);

	if (l == orig_size){
		struct Number my_block; 
		my_block = scatter(me, nprocs, first_digit_max);
		for (i = 0; i < my_block.size; i++){
			if (my_block.arr[i] == 0){ continue; }
			/* printf("CURRENT: %d\n", my_block.arr[i]); */
			int left, spot;
			left = n_sum - my_block.arr[i];
			spot = orig_size - l;
			prev[spot] = my_block.arr[i];


			findNumsWithDigitalSum(left, l-1, prev, orig_size); //Recurse with l = l-1 and n_sum = remaining digital sum


		}
		free(my_block.arr);
	}
	else {
		for (i = 1; i <= first_digit_max; i++){
			int left, spot;
			left = n_sum - i;
			spot = orig_size - l;
			prev[spot] = i;


			findNumsWithDigitalSum(left, l-1, prev, orig_size); //Recurse with l = l-1 and n_sum = remaining digital sum


		}
	}
}



int main(int argc, char* argv[]){
	MPI_Init(NULL, NULL); 
	MPI_Comm world = MPI_COMM_WORLD;
	MPI_Comm_size(world, &nprocs);
	MPI_Comm_rank(world, &me);


	int digital_sum, result, l, *tmp_prev, i, *arr_zero;
	digital_sum = atoi(argv[1]);
	/* int arr_zero[1] = {0}; */
	arr_zero = malloc(sizeof(int));
	arr_zero[0] = 0;
	globalSum.arr = arr_zero;
	globalSum.size = 1;

	for (i = 1; i <= digital_sum; i++){
		if (i == 1 && me != 0){ continue; }
		tmp_prev = malloc(i*sizeof(int));
		findNumsWithDigitalSum(digital_sum, i, tmp_prev, i); 
		free(tmp_prev);
	}

	/* printf("Sum for node %d: ", me); */
	/* printNumber(globalSum.arr, globalSum.size); */
	/* printf("\n"); */

	if (me == 0){
		int i;
		for (i = 1; i < nprocs; i++){
			int rcv_size, *rcv_arr;
			MPI_Recv(&rcv_size, 1, MPI_INT, i, 0, world, MPI_STATUS_IGNORE);
			rcv_arr = malloc(rcv_size * sizeof(int));
			MPI_Recv(rcv_arr, rcv_size, MPI_INT, i, 0, world, MPI_STATUS_IGNORE);

			globalSum = addArrays(globalSum.arr, rcv_arr, globalSum.size, rcv_size);
			free(rcv_arr);
		}
		printf("Sum: \n");
		printNumber(globalSum.arr, globalSum.size);
		
	}
	else {
		MPI_Send(&globalSum.size, 1, MPI_INT, 0, 0, world);
		MPI_Send(globalSum.arr, globalSum.size, MPI_INT, 0, 0, world);
	}

	free(globalSum.arr);
	MPI_Finalize();
	return 0;
}

