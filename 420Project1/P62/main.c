/* Group #62 Brute force method for finding smallest cube where five permutations of its digits are also a cube. */
#include <stdlib.h>
#include <mpi.h>
#include "work.h"

#DEFINE cubeSize 2000;

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

    //intialize cube array
    unsigned int cube[cubeSize];
    unsigned int ret[100];
    int i;
    for (i = 0; i < cubeSize; i++)
    {
        cube[i] = (i + 1) * (i + 1) * (i + 1);
    }
	
	permuter check;
	//CLR = Cores Less Root
    int CLR = cores -1;
	int range = cubeSize / CLR;
	
	int min, max;
	
	if(rank != 0)
	{
		min = range * (rank - 1);
		max = min + range;
		unsigned int i;
		int found = -1;
		unsigned int sendval;
		for(i = min; i < max; i++)
		{
			found = check.checkAllPermutations(cube, cubeSize, cube[i]);
			if(found == 5)
			{
				sendval = i;
				break;
			}
			else
			{
				found = -1;
			}
		}
		if(found == -1)
		{
			sendval = max + 1;
		}
		MPI_Send(&sendval, 1, MPI_UNSIGNED, 0, 0, world);
	}
	
    int elementsSent = cubeSize / CLR;
    int remainderFlag = 0;
    int offSet = 0;
    int stopPoint = 0;
	unsigned int sendval;
    if (rank == 0 && (cubeSize % CLR) > 0)
    {
        remainderFlag = 1;
        stopPoint = (cubeSize % CLR);
        //Do work here for remainder on root
		min = range * CLR;
		max = min + stopPoint;
		unsigned int i;
		int found = -1;
		for(i = min; i < max; i++)
		{
			found = check.checkAllPermutations(cube, cubeSize, cube[i]);
			if(found == 5)
			{
				sendval = i;
				break;
			}
			else
			{
				found = -1;
			}
		}
		if(found == -1)
		{
			sendval = max + 1;
		}
    }
	
	if(rank == 0)
	{
		unsigned int best = cubeSize + 1;
		int i;
		unsigned int potential_best;
		for(i = 1; i < cores; i++)
		{
			MPI_Recv(&potential_best, 1, MPI_UNSIGNED, i, 0, world, &status);
			if(potential_best < ((range * (i - 1)) + range - 1))
			{
				if(potential_best < best)
				{
					best = potential_best;
				}
			}
		}
		if(remainderFlag == 1)
		{
			if(sendval < best)
			{
				best = sendval;
			}
		}
	}
	
    MPI_Finalize();
    return 0;
}