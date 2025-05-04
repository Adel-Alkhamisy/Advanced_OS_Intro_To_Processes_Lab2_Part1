/*
 * Multi-Process Demonstration Program
 * 
 * This program demonstrates process creation and synchronization using fork() and wait().
 * It creates a parent process and two child processes, where:
 * - Each child process runs for a random number of iterations (between 1-25)
 * - Each child sleeps for a random time during each iteration
 * - The parent process waits for both children to complete
 * 
 * The program showcases:
 * - Process creation using fork()
 * - Process identification using getpid() and getppid()
 * - Process synchronization using wait()
 * - Random number generation
 * - Process sleep functionality
 */

#include <stdio.h>      /* For printf() */
#include <stdlib.h>     /* For exit(), rand(), srand() */
#include <unistd.h>     /* For getpid(), getppid(), sleep(), fork() */
#include <sys/types.h>  /* For pid_t */
#include <sys/wait.h>   /* For wait() */
#include <time.h>       /* For time() to seed random */
#include <string.h>     /* For strlen() */

#define MAX_ITERATIONS_UPPER 20  /* Maximum possible iterations */
#define MAX_ITERATIONS_LOWER 1   /* Minimum possible iterations */
#define MAX_SLEEP_TIME 5         /* Maximum sleep time in seconds */
#define MIN_SLEEP_TIME 1         /* Minimum sleep time in seconds */

void main(void) {
    pid_t first_child_pid, second_child_pid, completed_child_pid;
    int wait_status;
    char message_buffer[100];  /* Buffer for formatted messages */
    
    /* Initialize random number generator */
    srand(time(0));
    
    /* Generate random iteration counts for each child */
    int first_child_iterations = (rand() % (MAX_ITERATIONS_UPPER - MAX_ITERATIONS_LOWER + 1)) + MAX_ITERATIONS_LOWER;
    int second_child_iterations = (rand() % (MAX_ITERATIONS_UPPER - MAX_ITERATIONS_LOWER + 1)) + MAX_ITERATIONS_LOWER;
    
    /* Display the number of iterations each child will perform */
    printf("First child will execute %d iterations, Second child will execute %d iterations\n", 
           first_child_iterations, second_child_iterations);
    
    /* Create first child process */
    first_child_pid = fork();
    
    if (first_child_pid == 0) {
        /* First child process code */
        int child_process_id = getpid();
        int parent_process_id = getppid();
        int iteration;
        
        /* Loop for the determined number of iterations */
        for (iteration = 1; iteration <= first_child_iterations; iteration++) {
            printf("Child Pid: %d is going to sleep!\n", child_process_id);
            
            /* Generate random sleep time and sleep */
            srand(time(NULL) + child_process_id); /* Reseed with child's PID for better randomness */
            int sleep_duration = (rand() % MAX_SLEEP_TIME) + MIN_SLEEP_TIME;
            sleep(sleep_duration);
            
            /* Print wake-up message */
            printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", 
                   child_process_id, parent_process_id);
        }
        
        /* Child process terminates after completing all iterations */
        exit(0);
    } else {
        /* Parent process creates second child */
        second_child_pid = fork();
        
        if (second_child_pid == 0) {
            /* Second child process code */
            int child_process_id = getpid();
            int parent_process_id = getppid();
            int iteration;
            
            /* Loop for the determined number of iterations */
            for (iteration = 1; iteration <= second_child_iterations; iteration++) {
                printf("Child Pid: %d is going to sleep!\n", child_process_id);
                
                /* Generate random sleep time and sleep */
                srand(time(NULL) + child_process_id); /* Reseed with child's PID for better randomness */
                int sleep_duration = (rand() % MAX_SLEEP_TIME) + MIN_SLEEP_TIME;
                sleep(sleep_duration);
                
                /* Print wake-up message */
                printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", 
                       child_process_id, parent_process_id);
            }
            
            /* Child process terminates after completing all iterations */
            exit(0);
        } else {
            /* Parent process code */
            
            /* Wait for first child to complete */
            completed_child_pid = wait(&wait_status);
            sprintf(message_buffer, "Child Pid: %d has completed\n", completed_child_pid);
            write(1, message_buffer, strlen(message_buffer));
            
            /* Wait for second child to complete */
            completed_child_pid = wait(&wait_status);
            printf("Child Pid: %d has completed\n", completed_child_pid);
        }
    }
}