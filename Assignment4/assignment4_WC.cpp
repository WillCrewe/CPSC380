#include <iostream>
#include <string>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

//initializing semaphores
sem_t sem1;
sem_t sem2;
sem_t sem3;
sem_t sem4;
//priority values
int t1_p = 9;
int t2_p = 8;
int t3_p = 7;
int t4_p = 6;
//doWork array initialization
double myArr[10][10];


int doWork(){
  int count = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
    {
			myArr[j][i] = myArr[j][i];
      count++;
    }
		for (int j = 0; j < 10; j++)
    {
			myArr[j][i] = myArr[j][i+5];
      count++;
    }
	}
  return count;
}


void *t1(void *arg){
  int rounds = 100;
  int count = 0;
  int over = 0;
  for(int i = 0; i < rounds; i++)
  {
    int check = doWork();
    if(check == 100)
    {
      count++;
    } else {
      over++;
    }
  }
  t1_p = t1_p - 2;
  cout << "T1: Ran: " << count << " times, Overran: " << over << " times" << endl;
}

void *t2(void *arg){
  int rounds = 200;
  int count = 0;
  int over = 0;
  for(int i = 0; i < rounds; i++)
  {
    int check = doWork();
    if(check == 100)
    {
      count++;
    } else {
      over++;
    }
  }
  t2_p = t2_p - 2;
  cout << "T2: Ran: " << count << " times, Overran: " << over << " times" << endl;
}

void *t3(void *arg){
  int rounds = 400;
  int count = 0;
  int over = 0;
  for(int i = 0; i < rounds; i++)
  {
    int check = doWork();
    if(check == 100)
    {
      count++;
    } else {
      over++;
    }
  }
  t3_p = t3_p - 2;
  cout << "T3: Ran: " << count << " times, Overran: " << over << " times" << endl;
}

void *t4(void *arg){
  int rounds = 1600;
  int count = 0;
  int over = 0;
  for(int i = 0; i < rounds; i++)
  {
    int check = doWork();
    if(check == 100)
    {
      count++;
    } else {
      over++;
    }
  }
  //cycling priority
  t4_p = t4_p - 2;
  cout << "T4: Ran: " << count << " times, Overran: " << over << " times" << endl;
}


//Scheduler creates and runs threads based off of the t#_p priority cycling
//The threads are created and synchronized using semaphores
//Each thread runs its respective function, and loops through the amount of times needed, finding whether or not the doWork function completed by checking the amount of times it has done a calculation (which should be 100)
//Then prints the amount of times it was ran, and the amount of overruns based off of my logic
void Scheduler(){
  if(t1_p >= t2_p && t1_p >= t3_p && t1_p >= t4_p){
    sem_init(&sem1, 0, 1);
    sem_wait(&sem1);
    pthread_t t1_thread;
    int int_t1;
    int_t1 = pthread_create(&t1_thread, NULL, &t1, NULL);
    pthread_join(t1_thread, NULL);
    sem_post(&sem2);
    sem_post(&sem3);
    sem_post(&sem4);
  } else if (t2_p >= t1_p && t2_p >= t3_p && t2_p >= t4_p){
    sem_init(&sem2, 0, 1);
    sem_wait(&sem2);
    pthread_t t2_thread;
    int int_t2;
    int_t2 = pthread_create(&t2_thread, NULL, &t2, NULL);
    pthread_join(t2_thread, NULL);
    sem_post(&sem2);
    sem_post(&sem2);
    sem_post(&sem2);
  } else if (t3_p >= t1_p && t3_p >= t2_p && t3_p >= t4_p){
    sem_init(&sem3, 0, 1);
    sem_wait(&sem3);
    pthread_t t3_thread;
    int int_t3;
    int_t3 = pthread_create(&t3_thread, NULL, &t3, NULL);
    pthread_join(t3_thread, NULL);
    sem_post(&sem2);
    sem_post(&sem2);
    sem_post(&sem2);
  } else {
    sem_init(&sem4, 0, 1);
    sem_wait(&sem4);
    pthread_t t4_thread;
    int int_t4;
    int_t4 = pthread_create(&t4_thread, NULL, &t4, NULL);
    pthread_join(t4_thread, NULL);
    sem_post(&sem2);
    sem_post(&sem2);
    sem_post(&sem2);
  }
}

int main(){
  //filling the doWork array with the value 1
  for(int k=0; k<10; k++)
  {
    for(int l=0; l<10; l++)
    {
      myArr[k][l] = 1.0;
    }
  }
  //running through 10 times by calling the scheduler function
  for(int i = 0; i < 10; i++)
  {
      Scheduler();
  }

  return 0;
}
