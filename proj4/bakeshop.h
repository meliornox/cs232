/*
** Theodore Bigelow
** jgb23
** 04/05/17
**
** This is the .h file containing declarations implied as a requirement
** for compliance with the standards for cs 232 projects found at
** https://cs.calvin.edu/courses/cs/232/policies/coding.html
*/

//Guard - It's a header file Thing
#ifndef BAKESHOP_H_
#define BAKESHOP_H_

//Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sched.h>

// Declare global variables
// Create semaphores:
// One to restrict the baker to one task,
sem_t bakerSem;
// one to prevent race conditions on the amount of bread available,
sem_t breadSem;
// one to indicate if there is a receipt available for a customer to take,
sem_t recSem;
// one to restrict the number of customers that can step up to the register
//     to one,
sem_t regSem;
// one to make sure there are no more than 5 customers in the store,
sem_t storeSem;
// and one for the protection of the CustomersWaiting variable.
sem_t waitSem;

// Check when customers may take bread
int breadAvailable = 0;
// Check when to make the baker work as a cashier
int customersWaiting = 0;

// Declare a thread to represent the baker baking
pthread_t bakerBake;
// Declare a thread to represent the baker cashiering
pthread_t bakerCheckout;
// Declare customer threads
pthread_t tid[10];

//Declare functions
void *makeBread();
void *getBread(void *);
void *checkout();
int main();

//BAKESHOP_H_
#endif
