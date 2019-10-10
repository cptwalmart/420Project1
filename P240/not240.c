// 420 Project 1
// Problem #240 60% difficult
// nothing clever with dividing work up
// Hardcoded for 1, 2, 3, 4 # of cores
// mpiexec -n 4 ./Proj240

#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

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

    printf("Rank:%d Count:%d\n",rank,Count);

    if(cores == 1){
        for(int a=1;a<=3;a++){
            for(int b=1;b<=12;b++){
                for(int c=1;c<=12;c++){
                    for(int d=1;d<=12;d++){
                        for(int e=1;e<=12;e++){
                            for(int f=1;f<=12;f++){
                                for(int g=1;g<=12;g++){
                                    for(int h=1;h<=12;h++){
                                        for(int i=1;i<=12;i++){
                                            for(int j=1;j<=12;j++){
                                                if((a+b+c+d+e+f+g+h+i+j)==70){
                                                    Count++;
                                                    //printf("%d %d %d %d %d %d %d %d %d %d %d\n",Count,a,b,c,d,e,f,g,h,i,j);
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
    else if(cores == 2){
        if(rank == 0){
            for(int a=1;a<=6;a++){
                for(int b=1;b<=12;b++){
                    for(int c=1;c<=12;c++){
                        for(int d=1;d<=12;d++){
                            for(int e=1;e<=12;e++){
                                for(int f=1;f<=12;f++){
                                    for(int g=1;g<=12;g++){
                                        for(int h=1;h<=12;h++){
                                            for(int i=1;i<=12;i++){
                                                for(int j=1;j<=12;j++){
                                                    if((a+b+c+d+e+f+g+h+i+j)==70){
                                                        Count++;
                                                        //printf("%d %d %d %d %d %d %d %d %d %d %d\n",Count,a,b,c,d,e,f,g,h,i,j);
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
        else{
            for(int a=7;a<=12;a++){
                for(int b=1;b<=12;b++){
                    for(int c=1;c<=12;c++){
                        for(int d=1;d<=12;d++){
                            for(int e=1;e<=12;e++){
                                for(int f=1;f<=12;f++){
                                    for(int g=1;g<=12;g++){
                                        for(int h=1;h<=12;h++){
                                            for(int i=1;i<=12;i++){
                                                for(int j=1;j<=12;j++){
                                                    if((a+b+c+d+e+f+g+h+i+j)==70){
                                                        Count++;
                                                        //printf("%d %d %d %d %d %d %d %d %d %d %d\n",Count,a,b,c,d,e,f,g,h,i,j);
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
            MPI_Send(&Count, 1, MPI_UNSIGNED_LONG_LONG, 0, 1, world);
        }
        if(rank==0){
            MPI_Recv(&Add, 1, MPI_UNSIGNED_LONG_LONG, 1, 1, world, MPI_STATUS_IGNORE);
            Count = Count + Add;
        }
    }
    else if(cores == 3){
        if(rank == 0){
            for(int a=1;a<=4;a++){
                for(int b=1;b<=12;b++){
                    for(int c=1;c<=12;c++){
                        for(int d=1;d<=12;d++){
                            for(int e=1;e<=12;e++){
                                for(int f=1;f<=12;f++){
                                    for(int g=1;g<=12;g++){
                                        for(int h=1;h<=12;h++){
                                            for(int i=1;i<=12;i++){
                                                for(int j=1;j<=12;j++){
                                                    if((a+b+c+d+e+f+g+h+i+j)==70){
                                                        Count++;
                                                        //printf("%d %d %d %d %d %d %d %d %d %d %d\n",Count,a,b,c,d,e,f,g,h,i,j);
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
        else if(rank == 1){
            for(int a=5;a<=8;a++){
                for(int b=1;b<=12;b++){
                    for(int c=1;c<=12;c++){
                        for(int d=1;d<=12;d++){
                            for(int e=1;e<=12;e++){
                                for(int f=1;f<=12;f++){
                                    for(int g=1;g<=12;g++){
                                        for(int h=1;h<=12;h++){
                                            for(int i=1;i<=12;i++){
                                                for(int j=1;j<=12;j++){
                                                    if((a+b+c+d+e+f+g+h+i+j)==70){
                                                        Count++;
                                                        //printf("%d %d %d %d %d %d %d %d %d %d %d\n",Count,a,b,c,d,e,f,g,h,i,j);
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
            MPI_Send(&Count, 1, MPI_UNSIGNED_LONG_LONG, 0, 1, world);
        }
        else{
            for(int a=9;a<=12;a++){
                for(int b=1;b<=12;b++){
                    for(int c=1;c<=12;c++){
                        for(int d=1;d<=12;d++){
                            for(int e=1;e<=12;e++){
                                for(int f=1;f<=12;f++){
                                    for(int g=1;g<=12;g++){
                                        for(int h=1;h<=12;h++){
                                            for(int i=1;i<=12;i++){
                                                for(int j=1;j<=12;j++){
                                                    if((a+b+c+d+e+f+g+h+i+j)==70){
                                                        Count++;
                                                        //printf("%d %d %d %d %d %d %d %d %d %d %d\n",Count,a,b,c,d,e,f,g,h,i,j);
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
            MPI_Send(&Count, 1, MPI_UNSIGNED_LONG_LONG, 0, 2, world);
        }
        if(rank==0){
            MPI_Recv(&Add, 1, MPI_UNSIGNED_LONG_LONG, 1, 1, world, MPI_STATUS_IGNORE);
            Count = Count + Add;
            MPI_Recv(&Add, 1, MPI_UNSIGNED_LONG_LONG, 2, 2, world, MPI_STATUS_IGNORE);
            Count = Count + Add;
            printf("\n\n%d\n\n",Count);
        }
    }
    else if(cores == 4){
        if(rank == 0){
            for(int a=1;a<=3;a++){
                for(int b=1;b<=12;b++){
                    for(int c=1;c<=12;c++){
                        for(int d=1;d<=12;d++){
                            for(int e=1;e<=12;e++){
                                for(int f=1;f<=12;f++){
                                    for(int g=1;g<=12;g++){
                                        for(int h=1;h<=12;h++){
                                            for(int i=1;i<=12;i++){
                                                for(int j=1;j<=12;j++){
                                                    if((a+b+c+d+e+f+g+h+i+j)==70){
                                                        Count++;
                                                        //printf("%d %d %d %d %d %d %d %d %d %d %d\n",Count,a,b,c,d,e,f,g,h,i,j);
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
        else if(rank == 1){
            for(int a=4;a<=6;a++){
                for(int b=1;b<=12;b++){
                    for(int c=1;c<=12;c++){
                        for(int d=1;d<=12;d++){
                            for(int e=1;e<=12;e++){
                                for(int f=1;f<=12;f++){
                                    for(int g=1;g<=12;g++){
                                        for(int h=1;h<=12;h++){
                                            for(int i=1;i<=12;i++){
                                                for(int j=1;j<=12;j++){
                                                    if((a+b+c+d+e+f+g+h+i+j)==70){
                                                        Count++;
                                                        //printf("%d %d %d %d %d %d %d %d %d %d %d\n",Count,a,b,c,d,e,f,g,h,i,j);
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
            MPI_Send(&Count, 1, MPI_UNSIGNED_LONG_LONG, 0, 1, world);
        }
        else if(rank == 2){
            for(int a=7;a<=9;a++){
                for(int b=1;b<=12;b++){
                    for(int c=1;c<=12;c++){
                        for(int d=1;d<=12;d++){
                            for(int e=1;e<=12;e++){
                                for(int f=1;f<=12;f++){
                                    for(int g=1;g<=12;g++){
                                        for(int h=1;h<=12;h++){
                                            for(int i=1;i<=12;i++){
                                                for(int j=1;j<=12;j++){
                                                    if((a+b+c+d+e+f+g+h+i+j)==70){
                                                        Count++;
                                                        //printf("%d %d %d %d %d %d %d %d %d %d %d\n",Count,a,b,c,d,e,f,g,h,i,j);
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
            MPI_Send(&Count, 1, MPI_UNSIGNED_LONG_LONG, 0, 2, world);
        }
        else{
            for(int a=10;a<=12;a++){
                for(int b=1;b<=12;b++){
                    for(int c=1;c<=12;c++){
                        for(int d=1;d<=12;d++){
                            for(int e=1;e<=12;e++){
                                for(int f=1;f<=12;f++){
                                    for(int g=1;g<=12;g++){
                                        for(int h=1;h<=12;h++){
                                            for(int i=1;i<=12;i++){
                                                for(int j=1;j<=12;j++){
                                                    if((a+b+c+d+e+f+g+h+i+j)==70){
                                                        Count++;
                                                        //printf("%d %d %d %d %d %d %d %d %d %d %d\n",Count,a,b,c,d,e,f,g,h,i,j);
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
            MPI_Send(&Count, 1, MPI_UNSIGNED_LONG_LONG, 0, 3, world);
        }
        if(rank == 0){
            MPI_Recv(&Add, 1, MPI_UNSIGNED_LONG_LONG, 1, 1, world, MPI_STATUS_IGNORE);
            Count = Count + Add;
            MPI_Recv(&Add, 1, MPI_UNSIGNED_LONG_LONG, 2, 2, world, MPI_STATUS_IGNORE);
            Count = Count + Add;
            MPI_Recv(&Add, 1, MPI_UNSIGNED_LONG_LONG, 3, 3, world, MPI_STATUS_IGNORE);
            Count = Count + Add;
            printf("\n\n%d\n\n",Count);
        }
    }

    printf("Rank:%d Count:%d\n",rank,Count);

    MPI_Finalize();
    return 0;
}