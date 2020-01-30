/*
Example Code teaching the use of the thread pool.
Author of example: Kevin Deming
Date: January 29th, 2020

------------------------------IMPORTANT NOTE: ------------------------------------
1) The amount of cores that this program uses is determined in the header files. 

2) It is automatically set to use all processors possible.

3) If you don't want to use all of your processors then follow these steps:

-----------STEPS TO CHANGE PROCESSORS USED---------------------

1) Open threadPool.hpp
2) Find the code: 

ThreadPool(void)
	:ThreadPool{ max(std::thread::hardware_concurrency(), 2u) - 1u }
{
	
3) Below the code is an explination of how its getting the processor amount.
   In case you want a different explination
   It finds the max of (A and 2) - 1. 
   So what you would want to change is std::thread::hardware_concurrency() to however many cores you can use.
   Ex. 
   :ThreadPool{ max(16u, 2u) - 1u } would then statically only use 16 cores. 
   --OR--
   :ThreadPool{ 16u - 1u } Where 16 is the amount of cores you would want to use.

*/

/*
Other libraries for example(rand, output, and string.)
*/
#include <iostream>
#include <string>
#include <stdio.h> 
#include <stdlib.h>
#include <windows.h>

/*
Include the header files for the thread pool
*/
#include "threadPool.hpp"
#include "ThreadSafeQueue.hpp"

int exampleFunction(int x, int gradeNum, std::string word, char letter);

int main()
{
	//variables to be passed into the thread pool
	int threadNumber, gradeNum;
	std::string name;
	char grade;
	name = "Student";

	/*
	main is the thread that sends out the tasks to the other worker threads.
	main is master thread, others are slave threads.
	*/

	/*
	IMPORTANT FOR MULTITHREADING
	Create a que to put the threads in. This data structure is where the Master thread gets functions to send to the processors.
	*/
	std::vector<MyNamespace::ThreadPool::TaskFuture<void>> exPool; //the vector or container that the threadpool threads are in. Can be any name you want


	/*
	Loop for sending tasks. Easiest way to send a lot of tasks.
	*/
	for (int a = 1; a < 101; a++)
	{
		gradeNum = rand() % 101;
		threadNumber = a;

		/*
		Not important and not a good way to make an if statement, but used for output example ;D
		*/
		if (gradeNum > 90)
		{
			grade = 'A';
		}
		else if (gradeNum > 80)
		{
			grade = 'B';
		}
		else if (gradeNum > 70)
		{
			grade = 'C';
		}
		else
		{
			grade = 'F';
		}

		/*
		-----------------Put your function into the thread pool.----------------------------
		1) you have to re-declare the vaiables you need for each thread in this lambda function.
		2) at the end re-type the variables you are using without type declaration.
		3) in between the brackets {} will be where you put your function.
		Note: The lambda function has same access that the main thread does to functions. However it only has access to variables passed into it. 

		*/
		exPool.push_back(MyNamespace::DefaultThreadPool::submitJob([](int threadNumber, int gradeNum, std::string name, char grade) //This is the function declaration mixed with putting it in a que.
		{

			//YOUR FUNCTIONS HERE
			exampleFunction(threadNumber, gradeNum, name, grade);
	
			//Wait to show how it is using multiple processors.
			Sleep(5000); //wait for 5 seconds
			
			//Note: when outputing, multiple threads may finish at the same time. This can cause the output to come out not as intended. Plan accordingly
			

		}, threadNumber, gradeNum, name, grade)); //pass in variables
	}

	//Pause the command prompt to display output.
	getchar();
}

/*
Example function can be replaced with any function that you want to run on mutiple threads.
In order to call the function from the thread pool you have to go through a lambda function.
*/
int exampleFunction(int x, int gradeNum, std::string word, char letter)
{
	//lots of difficult calculations
	std::cout << "Thread" << x << ": Name: " << word << " Grade: " << letter << " " << gradeNum << std::endl;
	
	//return values can be weird to get back from a thread on a different cpu so know that ahead of time.
	return 0;
}