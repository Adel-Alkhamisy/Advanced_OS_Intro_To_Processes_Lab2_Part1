/*
 * Parent-Child Process Demonstration
 * 
 * This program demonstrates basic process creation and execution in C
 * using the fork() system call. It creates a parent-child relationship
 * between processes and shows how they execute independently.
 * 
 * Program flow:
 * 1. The main process calls fork() to create a child process
 * 2. Based on the process ID returned by fork():
 *    - The child process (pid == 0) executes ChildProcess()
 *    - The parent process (pid > 0) executes ParentProcess()
 * 3. Each process runs its own loop, printing messages with incrementing values
 * 4. Each process prints a completion message when finished
 * 
 * Expected output:
 * - The output from parent and child processes will be interleaved
 * - The exact ordering depends on the operating system's process scheduling
 * - Both processes run concurrently without synchronization
 * 
 * This example illustrates fundamental concepts of process creation,
 * parent-child relationships, and concurrent execution in Unix/Linux systems.
 */

#include  <stdio.h>
#include  <sys/types.h>

#define   MAX_COUNT  30    /* Number of iterations for both processes */

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

void  main(void)
{
     pid_t  pid;    /* Process ID returned by fork() */

     /* Create a new process by duplicating the current process */
     pid = fork();
     
     /* Determine whether this is the parent or child process */
     if (pid == 0) 
          ChildProcess();    /* pid == 0 indicates this is the child process */
     else 
          ParentProcess();   /* pid > 0 indicates this is the parent process */
     
     /* After this point, both processes continue their execution independently */
}

void  ChildProcess(void)
{
     int   i;    /* Loop counter */

     /* Child process loop - prints message for each iteration */
     for (i = 1; i <= MAX_COUNT; i++)
          printf("   This line is from child, value = %d\n", i);
     
     /* Indicate completion of child process */
     printf("   *** Child process is done ***\n");
     
     /* Child process terminates after this function returns */
}

void  ParentProcess(void)
{
     int   i;    /* Loop counter */

     /* Parent process loop - prints message for each iteration */
     for (i = 1; i <= MAX_COUNT; i++)
          printf("This line is from parent, value = %d\n", i);
     
     /* Indicate completion of parent process */
     printf("*** Parent is done ***\n");
     
     /* Parent process continues execution after this function returns */
     /* Note: In this program, the parent does not wait for the child to complete */
}