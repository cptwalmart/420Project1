/* Group #62 Brute force method for finding smallest cube where five permutations of its digits are also a cube. */
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);
    //init cores
    int cores;
    MPI_Comm world = MPI_COMM_WORLD;
    MPI_Comm_size(world, &cores);
    int rank;
	
    //sets rank = to what core
    MPI_Comm_rank(world, &rank);
    log_set_rank(rank);
    MPI_Status status;
	
	unsigned long long globalsum = 0;
	char * upperlimitstring;
	int iteration;
	unsigned long long int key;
	unsigned long long int upperlimit;
	unsigned long long int i;
	for(iteration = 1; iteration < 18; iteration++)
	{
		unsigned long long int localsum = 0;
		key = 13;
		for(i = 1; i < iteration; i++)
		{
			key *= key;
		}
		upperlimitstring = malloc(sizeof(char) * key);
		for(i = 0; i < key; i++)
		{
			upperlimitstring[i] = '1';
		}
		upperlimit = atoi(upperlimitstring);
		unsigned long long int CLR = cores - 1;
		unsigned long long int chunk;
		unsigned long long int min;
		unsigned long long int max;
		chunk = upperlimit / CLR;
		min = chunk * (rank - 1);
		max = min + chunk;
		unsigned long long stringlength;
		unsigned long long j;
		if( rank != 0)
		{
			for(i = min; i < max; i++)
			{
				int flag = 1;
				stringlength = sprintf(upperlimitstring, "%d", i)
				for(j = 0; j < stringlength; j++)
				{
					if(upperlimitstring[j] == 0)
					{
						flag = 0 ;
					}
				}
				if(flag == 1)
				{
					int testsum = 0;
					for(j = 0; j < stringlength; j++)
					{
						testsum += atoi(upperlimitstring[j]);
					}
					if(testsum == key)
					{
						localsum += i;
					}
					MPI_Send(&localsum, 1, MPI_UNSIGNED_LONG_LONG, 0, iteration, world);
				}
			}
		}
		if(rank == 0 && (upperlimit % CLR) > 0)
		{
			min = chunk * CLR;
			max = min + (upperlimit % CLR);
			for(i = min; i < max; i++)
			{
				int flag = 1;
				stringlength = sprintf(upperlimitstring, "%d", i)
				for(j = 0; j < stringlength; j++)
				{
					if(upperlimitstring[j] == 0)
					{
						flag = 0 ;
					}
				}
				if(flag == 1)
				{
					int testsum = 0;
					for(j = 0; j < stringlength; j++)
					{
						testsum += atoi(upperlimitstring[j]);
					}
					if(testsum == key)
					{
						globalsum += i;
					}
				}
			}
		}
		free(upperlimitstring);
		unsigned long long int recbuf;
		for(i = 1; i < cores, i++)
		{
			MPI_Recv(&recbuf, 1, MPI_UNSIGNED_LONG_LONG, i, iteration, world, &status);
			globalsum += recbuf;
		}
	}
    MPI_Finalize();
    return 0;
}