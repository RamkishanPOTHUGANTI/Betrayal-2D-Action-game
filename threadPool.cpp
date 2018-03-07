#include "threadPool.h"

threadPool::threadPool(int n) {
	isWorkToDo = 0;
	isJobQueueEmpty = 1;
	myThreads.reserve(n+2);

	for (int i = 0; i < n; i++)
	{
		myThreads.push_back(std::thread(&threadPool::loopingFunction,this));
	}

}
int threadPool::waitFinished() {
	{
		std::unique_lock<std::mutex> lock(m1);
		while (isJobQueueEmpty == 0) {
			w.wait(lock);
		}

	}
	return 1;
}
int threadPool::loopingFunction() {
	//std::condition_variable c;
	std::function<int()> job;
	while (true) {
		//totalThreads += 1;
		{
			std::unique_lock<std::mutex> lock(m1);

			while (jobQueue.size() == 0 && !isStop) {
				c.wait(lock);
			}
			if (isStop) return 0;

			job = jobQueue.front();
			jobQueue.pop();
		}
		job();
		{
			std::unique_lock<std::mutex> lock2(m2);
			isWorkToDo -= 1;
			if (isWorkToDo == 0) {
				isJobQueueEmpty = 1;
				w.notify_all();
			}
		}
		//std::this_thread::sleep_for(std::chrono::seconds(4));
	}
}
//template<typename T1, typename T2>

//template<typename T1,typename T2>
int threadPool::addJob(int count,std::function<int()> newJob,...) {  // If mulitple threads will be acessing then see that it is locked
	va_list jobs;
	va_start(jobs, newJob);
	std::unique_lock<std::mutex> lock(m1);
	jobQueue.push(newJob);
	isWorkToDo += 1;
	isJobQueueEmpty = 0;
	lock.unlock();
	c.notify_one();
	for (int i = 1; i < count; i++) {
		lock.lock();
		jobQueue.push(va_arg(jobs,std::function<int()>));
		isWorkToDo += 1;
		isJobQueueEmpty = 0;
		lock.unlock();
		c.notify_one();

	}
	va_end(jobs);
	return 1;
}
//template<typename T1, typename T2>
void threadPool::destroy() {
	isStop = 1;
	c.notify_all();
	for (int i = 0; i < 10; i++) {
		if (myThreads[i].joinable()) myThreads[i].join();
	}
}
