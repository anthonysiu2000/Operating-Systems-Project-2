// File:	mypthread_t.h

// List all group member's name:  Jonathan Konopka, Anthony Siu 
// username of iLab:
// iLab Server:

#ifndef MYTHREAD_T_H
#define MYTHREAD_T_H

#define _GNU_SOURCE

/* To use Linux pthread Library in Benchmark, you have to comment the USE_MYTHREAD macro */
#define USE_MYTHREAD 1

/* include lib header files that you need here: */
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <sys/time.h>
#include <signal.h> 

typedef uint mypthread_t;

typedef struct threadControlBlock {
	/* add important states in a thread control block */
	// thread Id
	int id;
	// thread status
	int status;	// 0 = running, 1 = ready, 2 = blocked, 3 = scheduled
	// thread context
	ucontext_t context;
	// thread stack
	// thread priority
	// And more ...
	void *output;
	int elapsed; //indicates how many time quantum has expired since the time thread was scheduled
	
    int p_level;
    void * retval;
} tcb;




/* mutex struct definition */
typedef struct mypthread_mutex_t {
	/* add something here */
	
	// YOUR CODE HERE
	int id;
    int locked; // 0 = unlocked, 1 = locked
} mypthread_mutex_t;

/* define your data structures here: */
// Feel free to add your own auxiliary data structures (linked list or queue etc...)






// YOUR CODE HERE


struct node {
   struct threadControlBlock *tcb;
   struct node *next;
};

//insert link at the first location
struct node* insertNode(struct node *list, struct threadControlBlock *inputtcb) {
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
   link->tcb = inputtcb;
   link->next = NULL;
	
   int inputquantum = inputtcb->elapsed;
   struct node *temp = list;
   struct node *prev = NULL;
   while (temp != NULL) {
      if (inputquantum <= temp->tcb->elapsed) {
         link->next = temp;
         prev->next = link;
         break;

      }
      prev = temp;
      temp = temp->next;
   }
   if (temp == NULL) {
      prev->next = link;
   }
   return list;
}

//is list empty
int isEmpty(struct node *list) {
   return (list == NULL);
}

//delete first item
struct threadControlBlock* deleteFirst(struct node *list) {

   //save reference to first link
   struct node *firstNode = list;
	
   //mark next to first link as first 
   list = list->next;
	
   if (isEmpty(list)) {
      free(list);
   }
   //return the deleted link
   return firstNode->tcb;
}







/* Function Declarations: */

/* create a new thread */
int mypthread_create(mypthread_t * thread, pthread_attr_t * attr, void
    *(*function)(void*), void * arg);

/* give CPU pocession to other user level threads voluntarily */
int mypthread_yield();

/* terminate a thread */
void mypthread_exit(void *value_ptr);

/* wait for thread termination */
int mypthread_join(mypthread_t thread, void **value_ptr);

/* initial the mutex lock */
int mypthread_mutex_init(mypthread_mutex_t *mutex, const pthread_mutexattr_t
    *mutexattr);

/* aquire the mutex lock */
int mypthread_mutex_lock(mypthread_mutex_t *mutex);

/* release the mutex lock */
int mypthread_mutex_unlock(mypthread_mutex_t *mutex);

/* destroy the mutex */
int mypthread_mutex_destroy(mypthread_mutex_t *mutex);

/* helper for runqueque */
void thread_runner(void *(*function)(void*), void *arg);

#ifdef USE_MYTHREAD
#define pthread_t mypthread_t
#define pthread_mutex_t mypthread_mutex_t
#define pthread_create mypthread_create
#define pthread_exit mypthread_exit
#define pthread_join mypthread_join
#define pthread_mutex_init mypthread_mutex_init
#define pthread_mutex_lock mypthread_mutex_lock
#define pthread_mutex_unlock mypthread_mutex_unlock
#define pthread_mutex_destroy mypthread_mutex_destroy
#endif

#endif
