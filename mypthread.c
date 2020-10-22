// File:	mypthread.c

// List all group member's name: Jonathan Konopka, Anthony Siu
// username of iLab:
// iLab Server:

#include "mypthread.h"

// INITAILIZE ALL YOUR VARIABLES HERE
// YOUR CODE HERE
int in_library = 0; //for scheduling?
int nextMutexId = 0; //id of next mutex creation


/* create a new thread */
int mypthread_create(mypthread_t * thread, pthread_attr_t * attr,
                      void *(*function)(void*), void * arg) {
       
    	in_library=1;

    	// create Thread Control Block
    	struct threadControlBlock *t = malloc(sizeof(*t));
		t->id = *thread;
		t->status = 0;


    	// create and initialize the context of this thread
		getcontext(&(t->context));
    	/*t->context.uc_link = &(old->context);
		t->context.uc_stack = (stack_t) {.ss_sp = malloc(MEM), .ss_size = MEM,
	       .ss_flags=0};
		*/
    	makecontext(&(t->context), &function, 2, function, arg);

       
    	// allocate space of stack for this thread to run




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







/*code to be run when SIGALRM is passed*/
static void alarm_handler(int signum) {
	
}



/* Preemptive SJF (STCF) scheduling algorithm */
static void sched_stcf() {
	// Your own implementation of STCF
	// (feel free to modify arguments and return types)

	// YOUR CODE HERE
	struct sigaction new_action;
	new_action.sa_handler = alarm_handler;
	sigaction(SIGALRM, &new_action, NULL);
}



/* scheduler */
static void schedule() {
	// Every time when timer interrupt happens, your thread library
	// should be contexted switched from thread context to this
	// schedule function
	
	// YOUR CODE HERE
	sched_stcf();
}






