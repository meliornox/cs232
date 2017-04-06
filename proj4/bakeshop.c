/*
** Theodore Bigelow
** jgb23
** 04/05/17
**
** This is the file for the main() function in accordance with the coding
** standards for cs 232 projects found at
**     https://cs.calvin.edu/courses/cs/232/policies/coding.html
** except for the part where the main() function must be in its own file, since
** the compilation command was given as the entire program being contained in
** one .c file.
**
** I used several online resources for this project, most notably
** stackOverflow.com and the Linux man page website.
**
** Compile and run by navigating to this folder and typing
**     gcc bakeshop.c -o bakeshop -lpthread
**     ./bakeshop
**
** ~Special Instructions~
*/

//Include header file
#include "bakeshop.h"

/*
** makeBread() directs the baker to bake bread and add it to
**     the available stock, keeping track of how much bread has been baked.
**
** returns a void pointer because it is a thread, this doesn't actually require
**     a return statement when the return is NULL.
*/
void *makeBread() {
    // Check when to stop baking bread
    int breadBaked = 0;
    // While we haven't made 10 bread yet
    while(breadBaked != 10) {
        // Call the baker over
        sem_wait(&bakerSem);
        // Put bread on the pile
        breadAvailable++;
        // Record that we made bread
	    breadBaked++;
        // Required message
        fprintf(stderr, "Baker: Completed a loaf of bread that is available for sale\n");
        // Release baker from service
        sem_post(&bakerSem);
        // Required wait
        usleep(1000000);
    }
    // Required message
    fprintf(stderr, "All the baking is done\n");
}

/*
** getBread() directs the actions of each customer.
**
** takes in a void * thread number for messaging purposes
**
** returns a void pointer because it is a thread, this doesn't actually require
**     a return statement when the return is NULL.
*/
void *getBread(void *id_num) {
    // Enter the store (Limit 5)
    sem_wait(&storeSem);
    // Required message
    fprintf(stderr, "Customer: #%ld entered the store\n", (long)id_num);
    // Control breadAvailable
    sem_wait(&breadSem);
    // Wait for bread
    while(breadAvailable == 0) {
      	usleep(1000000);
    }
    // Take bread
    breadAvailable--;
    // Let other people control breadAvailable
    sem_post(&breadSem);
    // Required message
    fprintf(stderr, "Customer: #%ld obtained a loaf of bread\n", (long)id_num);
    // Required wait
    usleep(1000000);
    // Step up to the register
    sem_wait(&regSem);
    // Required message
    fprintf(stderr, "Customer: #%ld has paid\n", (long)id_num);
    // Control waitSem
    sem_wait(&waitSem);
    // Get baker's attention at the register
    customersWaiting++;
    // Let others control waitSem
    sem_post(&waitSem);
    // Ensures checkout() gets recSem() first
    usleep(1000000);
    // Wait for a receipt
    sem_wait(&recSem);
    // Literally: Give the receipt back to the cashier
    // Theoretically: Let the baker know it was received
    sem_post(&recSem);
    // Required message
    fprintf(stderr, "Customer: #%ld has gotten a receipt\n", (long)id_num);
    // Let someone else step up to the register
    sem_post(&regSem);
    // Required message
    fprintf(stderr, "Customer: #%ld has left the store\n", (long)id_num);
    // Leave the store
    sem_post(&storeSem);
}

/*
** checkout() directs the actions of each customer.
**
** returns a void pointer because it is a thread, this doesn't actually require
**     a return statement when the return is NULL.
*/
void *checkout() {
    // Variable for keeping track of customers
    int customersHelped = 0;
    // If we haven't helped 10 customers yet
    while(customersHelped != 10) {
        // If there is a customer waiting
        if(customersWaiting > 0) {
            // Call the baker over
            sem_wait(&bakerSem);
            // Print a receipt
            fprintf(stderr, "Register: printed a receipt\n");
            // Record that the customer was helped
            customersHelped++;
            // Control customersWaiting
            sem_wait(&waitSem);
            // Take customer off the waiting list
            customersWaiting--;
            // Let others control waitSem
            sem_post(&waitSem);
            // Give receipt
            sem_post(&recSem);
            // Required pause
            usleep(1000000);
            // Literally: Take the receipt from the customer
            // Theoretically: Acknowledge that the customer received the receipt
            sem_wait(&recSem);
            // Release the baker from service
            sem_post(&bakerSem);
        }
    }
    // Stop handing out receipts
    sem_post(&recSem);
}

/*
** main() initializes necessary variables and starts threads as the driver for
**     the bakery
**
** returns a status code, 0 is normal
*/
int main() {
    fprintf(stderr, "The bakery is starting up\n");
    // Initialize semaphores with a limit of one available space
    sem_init(&bakerSem, 0, 1);
    sem_init(&breadSem, 0, 1);
    sem_init(&recSem, 0, 1);
    sem_init(&regSem, 0, 1);
    sem_init(&waitSem, 0, 1);

    // Initialize the store customer capacity to be 5
    sem_init(&storeSem, 0, 5);

    // Initialize a thread to represent the baker baking
    pthread_create(&bakerBake, NULL, makeBread, NULL);
    // Initialize a thread to represent the baker cashiering
    pthread_create(&bakerBake, NULL, checkout, NULL);
    // Initialize threads for the customers
    long i;
    for(i = 0; i < 10; i++) {
        pthread_create(&tid[i], NULL, getBread, (void *)i);
    }

    // Wait for all threads to complete before exiting
    pthread_exit(NULL);
}
