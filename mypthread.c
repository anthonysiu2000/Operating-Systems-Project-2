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
	// Your own implementation of STCF
	// (feel free to modify arguments and return types)

	// YOUR CODE HERE

	//initialize schedule context
	getcontext(schedContext);
	
	//while linked list is not empty:
	while (!isEmpty(scheduleList)) {
		//remove and obtain tcb at front of arraylist
		struct threadControlBlock *currtcb = deleteFirst(scheduleList);
		//set timer to quantum
		setitimer(ITIMER_VIRTUAL, quantum, NULL);
		//context switch to that tcb's context from schedule context
		swapcontext(schedContext, );
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
	// Every time when timer interrupt happens, your thread library
	// should be contexted switched from thread context to this
	// schedule function
	// YOUR CODE HERE
	struct sigaction new_action;
	new_action.sa_handler = alarm_handler;
	sigaction(SIGVTALRM, &new_action, NULL);
	alarmSignalMade = 1;
	scheduleList->tcb = NULL;
	scheduleList->next = NULL;
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


/* create a new thread */
int mypthread_create(mypthread_t * thread, pthread_attr_t * attr,
                      void *(*function)(void*), void * arg) {
       
    	in_library=1;

    	// create Thread Control Block
    	struct threadControlBlock *t = malloc(sizeof(*t));
		t->id = *thread;
		t->status = 0;


    	// create and initialize the context of this thread
	//tcb* old;
	//tcb*t = tcb_init();
		getcontext(&(t->context));
    	/*t->context.uc_link = &(old->context);
		t->context.uc_stack = (stack_t) {.ss_sp = malloc(MEM), .ss_size = MEM,
	       .ss_flags=0};
		*/
    	makecontext(&(t->context), &function, 0);

       
    	// allocate space of stack for this thread to run



		if (alarmSignalMade == 0) {
			schedule();
		} else {
			insertNode(scheduleList, t);
			setcontext(schedContext);
		}
    	// after everything is all set, push this thread int


    return 0;
};

/* give CPU possession to other user-level threads voluntarily */
int mypthread_yield() {

	// change thread state from Running to Ready
	// save context of this thread to its thread control block
	// wwitch from thread context to scheduler context

	// YOUR CODE HERE
	//need timer interrupt
	return 0;
};

/* terminate a thread */
void mypthread_exit(void *value_ptr) {
	// Deallocated any dynamic memory created when starting this thread

	// YOUR CODE HERE
	
	in_library=1;

	if (value_ptr !=NULL ) {
		//save return value of thread 
	}
};


/* Wait for thread termination */
int mypthread_join(mypthread_t thread, void **value_ptr) {

	// wait for a specific thread to terminate
	// de-allocate any dynamic memory created by the joining thread

	// YOUR CODE HERE
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
	
	// YOUR CODE HERE
	*mutex = (mypthread_mutex_t) {.id = nextMutexId++, .locked=0};
	return 0;
};

/* aquire the mutex lock */
int mypthread_mutex_lock(mypthread_mutex_t *mutex) {
        // use the built-in test-and-set atomic function to test the mutex
        // if the mutex is acquired successfully, enter the critical section
        // if acquiring mutex fails, push current thread into block list and //
        // context switch to the scheduler thread
	in_library = 1;
        // YOUR CODE HERE
        return 0;
};

/* release the mutex lock */
int mypthread_mutex_unlock(mypthread_mutex_t *mutex) {
	// Release mutex and make it available again.
	// Put threads in block list to run queue
	// so that they could compete for mutex later.

	// YOUR CODE HERE
	return 0;
};


/* destroy the mutex */
int mypthread_mutex_destroy(mypthread_mutex_t *mutex) {
	// Deallocate dynamic memory created in mypthread_mutex_init

	return 0;
};













