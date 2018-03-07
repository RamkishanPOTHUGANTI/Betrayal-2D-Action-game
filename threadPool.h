#pragma once
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include<functional>
#include <iostream>
#include <condition_variable>
#include <stdarg.h>
/** Thread pool class used to manage the worker threads and post jobs on the job queue
*	Here the threads are continuously waiting for the jobs to be posted on the job queue 
*	and once posted will execute the jobs.
*/
class threadPool {
	public:
		/*Constructor for the thread pool*/
		threadPool(int);
		~threadPool() {
			std::cout << "Destroyed" << std::endl;
		}
		/** Method to add the jobs on the jobqueue
		*
		*	The first parameter is the count indicating the number of jobs posted and the second 
		*	has a variadic argument list containing the jobs
		*
		*	function return 0 if sucessfull
		*/
		int addJob(int count,std::function<int()>,...);
		/** Method to destroy the threads after the game is exited
		*
		*	function takes no parameters
		*
		*	return void
		*/
		void destroy();
		/** Method to wait until the job is finished and the worker pool is empty
		*
		*	Function takes no parameter
		*
		*
		*	return 0 if sucessful
		*/
		int waitFinished();
	private:

		int isJobQueueEmpty; // if job queue is empty or not
		std::mutex m1, m2; // mutexes for the unique lock
		int isStop;  // wether to stop the thread pool or not
		int remainingThreads; 
		/** Function for the looping the threads until the threads are given jobs
		*
		*	Function takes no parameters
		*
		*	return 0 if the threadpool is allowed to stop
		*/
		int loopingFunction();
		// vector to hold the threads-
		std::vector<std::thread> myThreads;
		// Condition variables for waiting for jobs to be posted and jobs to be finished
		std::condition_variable c,w;
		// Jobs queue holding the jobs
		std::queue<std::function<int()>> jobQueue;
		int flag;
		int isWorkToDo;

		

};