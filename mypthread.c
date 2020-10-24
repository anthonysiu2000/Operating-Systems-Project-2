// File:	mypthread.c

// List all group member's name: Jonathan Konopka, Anthony Siu
// username of iLab:
// iLab Server:

#include "mypthread.h"
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <sys/time.h>
#include <signal.h> 

// INITAILIZE ALL YOUR VARIABLES HERE
// YOUR CODE HERE
int in_library = 0; //for scheduling?
int nextMutexId = 0; //id of next mutex creation
int alarmSignalMade = 0; // so that the system for generating SIGVTALRM only occurs once
int tcbTimeIncrease = 0; //for time signal
//initialize tcb arraylist
struct node *scheduleList;
//initialize schedule context
struct ucontext_t *schedContext;
//initialize quantum and pause;
struct itimerval *quantum;
struct itimerval *pauseTime;







/*code to be run when SIGALRM is passed*/
static void alarm_handler(int signum) {

	tcbTimeIncrease = 1;
	
	//Context switch to stcf context
	setcontext(schedContext);
}



/* Preemptive SJF (STCF) scheduling algorithm */
static void sched_stcf() {

	//initialize schedule context
	getcontext(schedContext);
	
	//while linked list is not empty:
	while (!isEmpty(scheduleList)) {
		//remove and obtain tcb at front of arraylist
		struct threadControlBlock *currtcb = deleteFirst(scheduleList);
		//set timer to quantum
		setitimer(ITIMER_VIRTUAL, quantum, NULL);
		//context switch to that tcb's context from schedule context
		swapcontext(schedContext, currtcb->context);
		//pause timer
		setitimer(ITIMER_VIRTUAL, pauseTime, NULL);

		if (tcbTimeIncrease == 1) {
			//increase current thread TCB elapsed
			currtcb->elapsed++;
			//set current TCB status to 3
			currtcb->status = 3;
			//insert tcb into arraylist
			insertNode(scheduleList, currtcb);
			//reset alarm_handler
			tcbTimeIncrease == 0;
		}
	}
}


/* scheduler */
static void schedule() {

	//change alarm signal
	struct sigaction new_action;
	new_action.sa_handler = alarm_handler;
	sigaction(SIGVTALRM, &new_action, NULL);
	alarmSignalMade = 1;

	//initialize schedule arraylist
	scheduleList->tcb = NULL;
	scheduleList->next = NULL;

	//initialize quantum and pause;
	quantum->it_interval.tv_sec = 0;
	quantum->it_interval.tv_usec = 5000;
	quantum->it_value.tv_sec = 0;
	quantum->it_value.tv_usec = 5000;
	pauseTime->it_interval.tv_sec = 0;
	pauseTime->it_interval.tv_usec = 0;
	pauseTime->it_value.tv_sec = 0;
	pauseTime->it_value.tv_usec = 0;

	sched_stcf();
}






//#define MEM 64000
#define MEM (SIGSTKSZ - 60)


/* create a new thread */
void thread_runner(void *(*function)(void*), void *arg) {
    void *ret_val = function(arg);
    mypthread_exit(ret_val);
}

int mypthread_create(mypthread_t * thread, pthread_attr_t * attr,
                      void *(*function)(void*), void * arg) {
      //ualarm(0, 0);
    	in_library=1;

    	// create Thread Control Block
    	struct threadControlBlock *t = malloc(sizeof(*t));
		t->id = *thread;
		t->status = 0;


    	// create and initialize the context of this thread
<<<<<<< HEAD
	getcontext(t->context);
	     t->context->uc_link=0;
	     t->context->uc_stack.ss_sp= malloc(MEM);
	     t->context->uc_stack = ss_size=MEM;
	     t->context->uc_stack = ss_flags = 0;
=======
	getcontext(&(t->context));
	     t->context.uc_link=0;
	     t->context.uc_stack.ss_sp= malloc(MEM);
	     t->context.uc_stack.ss_size=MEM;
	     t->context.uc_stack.ss_flags = 0;
>>>>>>> a83eb0f8ae3c121b7f792e77c893571d175a76fe
    	//uc link
      //uc stack
    	makecontext(t->context, function, 0);


    	// allocate space of stack for this thread to run


		// after everything is all set, push this thread int
		if (alarmSignalMade == 0) {
			schedule();
		} else {
			insertNode(scheduleList, t);
			setcontext(schedContext);
		}
    	

    return 0;
};

/* give CPU possession to other user-level threads voluntarily */
int mypthread_yield() {

	// change thread state from Running to Ready
	// save context of this thread to its thread control block
	// wwitch from thread context to scheduler context

	// YOUR CODE HERE
	//need timer interrupt

  //ualarm(0, 0);
	return 0;
};

/* terminate a thread */
void mypthread_exit(void *value_ptr) {
	// Deallocated any dynamic memory created when starting this thread

	// YOUR CODE HERE

	in_library=1;
  //ualarm(0, 0);

	if (value_ptr !=NULL ) {
		//save return value of thread
	}
};


/* Wait for thread termination */
int mypthread_join(mypthread_t thread, void **value_ptr) {

	// wait for a specific thread to terminate
	// de-allocate any dynamic memory created by the joining thread

	// YOUR CODE HERE

  //ualarm(0, 0);
	in_library = 1;
	if (value_ptr != NULL) {
		//pass back return value of thread
		// *value_ptr = thread->retval;
	}
	return 0;
};




/* initialize the mutex lock */
int mypthread_mutex_init(mypthread_mutex_t *mutex,
                          const pthread_mutexattr_t *mutexattr) {
	//initialize data structures for this mutex

  //struct mypthread_mutex_t  *m = malloc(sizeof(*m));
  mutex->id = nextMutexId++;
  mutex->locked = 0;
	return 0;
};

/* aquire the mutex lock */
int mypthread_mutex_lock(mypthread_mutex_t *mutex) {
        // use the built-in test-and-set atomic function to test the mutex
        // if the mutex is acquired successfully, enter the critical section
        // if acquiring mutex fails, push current thread into block list and //
        // context switch to the scheduler thread
	       in_library = 1;
         //ualarm(0, 0);
        if (mutex->locked == 0) {
          mutex->locked = 1;
          //insert to queue a tcb
          //insertNode(scheduleList, );
          return 0;
        }

        return 0;
};

/* release the mutex lock */
int mypthread_mutex_unlock(mypthread_mutex_t *mutex) {
	// Release mutex and make it available again.
	// Put threads in block list to run queue
	// so that they could compete for mutex later.

	// YOUR CODE HERE

  //ualarm(0, 0);
  in_library = 1;
  mutex->locked = 0;

  deleteFirst(scheduleList); //delete queue
	return 0;
};


/* destroy the mutex */
int mypthread_mutex_destroy(mypthread_mutex_t *mutex) {
	// Deallocate dynamic memory created in mypthread_mutex_init

  //ualarm(0, 0);
  free(mutex->id);
  free(mutex->locked);
  free(mutex);
	return 0;
};













