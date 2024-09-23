// gcc -Wall -pedantic -g -pthread -o parallel parallel.c

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double 	lim 	= 25000000000.0,	// Max iterations of the Leibniz equation
		PI 		= 0.0,
		thd_cnt;

pthread_mutex_t myLock;	

void* leibniz_portion(void* args){
	double 	start	= *(double*)&args[0],	// Thread specific start point
			sign	= 1.0,
			pi	 	= 0.0;					// Thread local portion of pi
	
	if ((int)start % 2 == 1)
		sign = -1.0;

	// Leibniz calculation
	if ((int)thd_cnt % 2 == 1){	// Odd number of threads requires a sign flip for additions
		for (; start < lim; start += thd_cnt){
    	    pi = pi + (sign / ((2 * start) + 1));	sign = -sign;
    	}
	} else {					// Even number of threads doesn't require a sign flip for additions
		for (; start < lim; start += thd_cnt)
    	    pi = pi + (sign / ((2 * start) + 1));
	}

	pthread_mutex_lock(&myLock);
        PI += (pi * 4); 
	pthread_mutex_unlock(&myLock);

	return NULL;
}

void input_check(int* argc, const char** argv){
	if (*argc != 2){
		printf("!ERROR! INCORRECT USEAGE\nCORRECT USAGE: ./<out> <thd_cnt>\n");
		exit(-1);
	}
	
	unsigned char val = (unsigned char)atoi(argv[1]);
	if (val == 0){
		printf("!ERROR! INVALID CONVERSION OF:\t%s\n", argv[1]);
		exit(-2);
	} else if (val >= 255) {	// check for 2's compliment overflow and values larger than 255
		printf("!ERROR! CANNOT SPAWN MORE THAN:\t%d THREADS\n", val);
		exit(-3);
	} else {
		printf("Good input. Continuing to thread creation\n");
		thd_cnt = val;
	}
}

void setup_and_fire_threads(){
	unsigned char	thd_err;	// Error check for thread spawn
	pthread_t*		thds;		// Array of POSIX threads
	double*			t_id;		// Array of thread Id's

	// Create array of threads and thread_ids based on thd_cnt
	thds 	= (pthread_t*) 	malloc(sizeof(pthread_t) * thd_cnt);
	t_id 	= (double*)		malloc(sizeof(double) 	 * thd_cnt);

	// Create mutex for shared memory variable pi.
    thd_err = pthread_mutex_init(&myLock, NULL);
	if (thd_err != 0)
		perror("!ERROR! FAILED TO CREATE MUTEX");

	// Fire off threads
	for (unsigned char i = 0; i < thd_cnt; i++){
		t_id[i] = i;
		thd_err = pthread_create(&thds[i], NULL, &leibniz_portion, &t_id[i]);

		if (thd_err != 0){
			printf("!ERROR! FAILED TO CREATE THREAD %d\n", (int)i); perror("");
		}
	}
	
	// Request thread return values
	printf("\nThreads\t\t = %f\n", thd_cnt);
	printf("Iterations\t = %f\n", lim);

	for (unsigned char i = 0; i < thd_cnt; ++i)
		pthread_join(thds[i], NULL);

	printf("Final Leibniz PI = %1.15f\n\n", PI);

	free(t_id); 
	free(thds); 
}

int main(int argc, char const *argv[]){
	// printf("before input check");
	input_check(&argc, argv);
	// printf("after input chec/k");
	setup_and_fire_threads(); 
	return 0;
}
