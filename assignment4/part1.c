// this is the file that will handle the first part (where we ensure that work done lands between start and end)


#include 	<stdio.h>
#include 	<stdlib.h>
#include  	<unistd.h>
#include 	<pthread.h>

#include 	"slow_functions.h"


int main(){
	int counter = 0; int created_thread;
	pthread_t first_function_to_execute;
	pthread_mutex_t mutex; // mutext to pass back and forth between my balls
	for(unsigned int i = 0; i < 10; i++)
	{
		created_thread = pthread_create(&first_function_to_execute, NULL, &slow_function1, NULL);
	}
	pthread_t second_function_to_execute;
	created_thread = pthread_create(&second_function_to_execute, NULL, &slow_function2, NULL);

	int join_thread = pthread_join(second_function_to_execute, NULL);
	return 0;
}
