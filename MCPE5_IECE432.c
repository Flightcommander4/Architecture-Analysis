//Matthew Calandrella - Programming Exercise #5 - ECE 432: Computer Architecture

//Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

//Defining Outer Loops and Vector Size
#define size 2048
#define outerLoops 2E0



int main(){
	
	//Initializing for User Choice, Vector Size and Processor, as well as start and end times for the Timers
	int processor;
	double start;
	double end;
	double** a;
	double** b;
	double** c;
	double *a_block, *b_block, *c_block;
	long long i, k, j, l;
	double AOpTime;
	double ExecTimeTotal;
	double VectorExecTime;

	
	//Credentials
	printf("Matthew Calandrella - PE#5 ECE 432\n\n");
		
		
	//Which Processor are we running on?
	printf("Which Processor are we Running On?\n\n");
	printf("1 - Intel XeonE5-2690 (Sandy Bridge)\n");
	printf("2 - Intel Xeon 4210 (Cascade Lake)\n");
	printf("3 - AMD EPYC 7452 (Rome)\n\n");
		
	scanf("%d", &processor);
	printf("\n");

		
		
	//If the user chooses an invalid processor, the following error occurs
	if(processor > 3){
		printf("Error, Invalid\n");
		return 0;
	}
		
	printf("\n");
 
		
	//Allocating Memory for the Vectors
	a = (double**)_mm_malloc(size * sizeof(double), 64);
	b = (double**)_mm_malloc(size  * sizeof(double), 64);
	c = (double**)_mm_malloc(size * sizeof(double), 64);
	
	//Storage for the Matrices
	a_block = (double *)_mm_malloc(size*size * sizeof(double),64); 
	b_block = (double *)_mm_malloc(size*size * sizeof(double),64);
	c_block = (double *)_mm_malloc(size*size * sizeof(double),64);

	//Initialize pointers to a rows a_block is start of row x col 1D array 
    //adding i*SIZE to it provied pointer to first element of each row in long 1D array
	for (i = 0; i < size; i++){
		
		a[i] = a_block + i*size;
		
    }

	for (i = 0; i < size; i++){
		
		b[i] = b_block + i*size;
	  
    }

	for (i = 0; i < size; i++){
		
		c[i] = c_block + i*size;
		
    }
	
    	
	for (i = 0; i < size; i++){
		
		for (j = 0; j < size; j++){
			
			a[i][j] = (double)(1 + rand() % 100);
			//printf("value %e \n", a[i][j]);
			
		}
    }

	for (i = 0; i < size; i++){
		
		for (j = 0; j < size; j++){
			
			b[i][j] = (double)(1 + rand() % 100); 
			//printf("value %e \n", b[i][j]);
			
		}
    }

	for (i = 0; i < size; i++){
		
		for (j = 0; j < size; j++){
			
			c[i][j] = 0.0; 
			//printf("value %e \n", c[i][j]);
			
		}
    }
	
	//Start Total Execution Time Timer
	start = omp_get_wtime();
	
	//Outer Loop
	for (l = 0; l < outerLoops; l++)
	{
 
		for(i = 0; i < size; i++){
		
			//Performing the Vector Operation	
			for(j = 0; j < size; j++){
				
				c[i][j] = 0.0;
				
				for(k = 0; k < size; k++){
				
					c[i][j] += a[i][k] * b[k][j];
				
				}
			
			}
		
		}
		
	}
	
	//End Total Execution Time Timer
	end = omp_get_wtime();
	
	//Computations
	ExecTimeTotal = (end - start);
	double FLOPS = (((2 * pow(size, 3)) - pow(size, 2)) * outerLoops) / ExecTimeTotal;
	
	//Benchmarks
	
	//Benchmark i-ii
	if(processor == 1){
		printf("Processor Being Tested: Intel Xeon E5-2690 (Sandy Bridge)\n");
		printf("Processor Clock Frequency: 3.8 GHz\n");
	}
	else if(processor == 2){
		printf("Processor Being Tested: Intel Xeon 4210 (Cascade Lake)\n");
		printf("Processor Clock Frequency: 3.2 GHz\n");
	}
	else if(processor == 3){
		printf("Processor Being Tested: AMD EPYC 7452 (Rome)\n");
		printf("Processor Clock Frequency: 3.35 GHz\n");
	}
	
	//Benchmark iii
	printf("Expression being tested: c[i][j] += a[i][k] * b[k][j]\n");
	
	//Benchmark iv
	printf("Array Dimension: %d\n", size);
	
	//Benchmark v
	printf("Number of Outer Resolution Loops: %E\n", outerLoops);
	
	//Benchmark vi
	printf("Total Elapsed Execution Time for the Benchmark: %f Seconds\n", ExecTimeTotal);
	
	//Benchmark vii
	printf("Execution Time per 1 iteration of the Matrix Multiplication: %E Seconds\n", (VectorExecTime = ExecTimeTotal / outerLoops));
	
	//Benchmark viii
	printf("Execution Time per Arithmetic Operation: %E Seconds\n", AOpTime = (VectorExecTime / size));
	
	//Benchmark ix
	printf("Sustained DP Floating Point Operations: %E FLOPS\n", FLOPS);
	
	//Benchmark x-xi
	if(processor == 1){
		printf("The Number of CPU Clock Cycles per DP FLOP: %f CPO\n", (3.8E9 / FLOPS));
		printf("The Number of DP FLOPs per Clock Cycle: %f OPC\n", (FLOPS / 3.8E9));
	}
	if(processor == 2){
		printf("The Number of CPU Clock Cycles per DP FLOP: %f CPO\n", (3.2E9 / FLOPS));
		printf("The Number of DP FLOPs per Clock Cycle: %f OPC\n", (FLOPS / 3.2E9));
	}
	if(processor == 3){
		printf("The Number of CPU Clock Cycles per DP FLOP: %f CPO\n", (3.35E9 / FLOPS));
		printf("The Number of DP FLOPs per Clock Cycle: %f OPC\n", (FLOPS / 3.35E9));
	}
	
	//Benchmark xii
	printf("Estimated L1D to/from the CPU Data BW (Bytes/sec) to sustain Computation (Ops/sec): %e\n", (3 * (pow(size, 2) * 8)) / ExecTimeTotal);
	
	//Benchmark xiii
	printf("Computational Intensity: %f\n", ((2.0 * size) - 1.0) / 24.0);

	//Freeing the Memory from the Vectors
	_mm_free(a);
	_mm_free(b);
	_mm_free(c);
 	_mm_free(a_block);
	_mm_free(b_block);
	_mm_free(c_block);
  
	return 0;
}
