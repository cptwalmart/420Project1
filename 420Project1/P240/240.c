// 420 Project 1
// Problem #240 60% difficult
// Hardcoded for mpiexec -n 72 ./Proj240
// How to compile
// make

#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int Loop(int x, int y, int* List){
    int Count = 0;

    for(int a=x;a<=x;a++){
        for(int b=y;b<=(y+1);b++){
            for(int c=1;c<=12;c++){
                for(int d=1;d<=12;d++){
                    for(int e=1;e<=12;e++){
                        for(int f=1;f<=12;f++){
                            for(int g=1;g<=12;g++){
                                for(int h=1;h<=12;h++){
                                    for(int i=1;i<=12;i++){
                                        for(int j=1;j<=12;j++){
                                            for(int k=1;k<=12;k++){
                                                for(int l=1;l<=12;l++){
                                                    for(int m=1;m<=12;m++){
                                                        for(int n=1;n<=12;n++){
                                                            for(int o=1;o<=12;o++){
                                                                for(int p=1;p<=12;p++){
                                                                    for(int q=1;q<=12;q++){
                                                                        for(int r=1;r<=12;r++){
                                                                            for(int s=1;s<=12;s++){
                                                                                for(int t=1;t<=12;t++){
                                                                                    List[0]=a;
                                                                                    List[1]=b;
                                                                                    List[2]=c;
                                                                                    List[3]=d;
                                                                                    List[4]=e;
                                                                                    List[5]=f;
                                                                                    List[6]=g;
                                                                                    List[7]=h;
                                                                                    List[8]=i;
                                                                                    List[9]=j;
                                                                                    List[10]=k;
                                                                                    List[11]=l;
                                                                                    List[12]=m;
                                                                                    List[13]=n;
                                                                                    List[14]=o;
                                                                                    List[15]=p;
                                                                                    List[16]=q;
                                                                                    List[17]=r;
                                                                                    List[18]=s;
                                                                                    List[19]=t;
                                                                                    qsort(List, 20, sizeof(int), cmpfunc);
                                                                                    if((List[19]+List[18]+List[17]+List[16]+List[15]+List[14]+List[13]+List[12]+List[11]+List[10])==70){
                                                                                        Count++;
                                                                                        //printf("%d %d %d %d %d %d %d %d %d %d %d\n",Count,List[19],List[18],List[17],List[16],List[15],List[14],List[13],List[12],List[11],List[10]);
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }   
                                    }   
                                }   
                            }   
                        }        
                    }                
                }
            }
        }
    }
    return Count;
}

int main(int argc, char* argv[]){
    MPI_Init(NULL, NULL);

    MPI_Comm world = MPI_COMM_WORLD;

    int cores;
    MPI_Comm_size(world, &cores);
    int rank;
    MPI_Comm_rank(world, &rank);

    unsigned long long Count = 0;
    unsigned long long Add = 0;

    int List[20];
    int x = 1;
    int y = 1;

    if(cores == 72){
        for(int Start = 1; Start<72; Start++){
            if(rank == Start){
                Count=Count+Loop(x,y,List);
                MPI_Send(&Count, 1, MPI_UNSIGNED_LONG_LONG, 0, Start, world);
                y = y + 2;
            }
            if(Start%12 == 5){
                x = x + 1;
            }
            if(Start%6 == 0){
                y = 1;
            }
        }


        if(rank == 0){
            for(int Start = 0; Start<72; Start++){
                MPI_Recv(&Add, 1, MPI_UNSIGNED_LONG_LONG, Start, Start, world, MPI_STATUS_IGNORE);
                Count = Count + Add;
            }
            printf("\n\nANSWER ANSWER ANSWER %d ANSWER ANSWER ANSWER\n\n",Count);
        }

        printf("Rank:%d Count:%d\n",rank,Count);
    }

    MPI_Finalize();

    return 0;
}