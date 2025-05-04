/*
 * Process Demonstration Program
 * 
 * This program demonstrates the creation and concurrent execution of
 * parent and child processes using the fork() system call.
 * 
 * Operation:
 * - The program creates a child process using fork()
 * - Both parent and child processes then independently execute a loop
 * - Each process prints its process ID and a counter value for each iteration
 * - The output from both processes is interleaved as they run concurrently
 * 
 * Expected behavior:
 * - Two different process IDs will appear in the output
 * - The sequence of output lines will be mixed between parent and child
 * - No synchronization is implemented between processes
 * - Both processes complete their loops independently
 * 
 * This example illustrates basic process creation and concurrent execution
 * in a Unix/Linux/MacOS environment.
 */



#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>

#define   MAX_COUNT  30
#define   BUF_SIZE   100

void  main(void)
{
     pid_t  pid;
     int    i;
     char   buf[BUF_SIZE];

     fork(); // Create a child process
     pid = getpid(); // Both processes (parent "main" and the newly created process by fork()) get their own PID
     for (i = 1; i <= MAX_COUNT; i++) {
       // 
       /**
       ** Both processes execute this loop independently
       ** After the fork(), two identical processes running the same code. Each gets its 
       ** own process ID with getpid() and then runs through the loop 30 times.
       **/
          sprintf(buf, "This line is from pid %d, value = %d\n", pid, i);
          write(1, buf, strlen(buf));
     } 
}