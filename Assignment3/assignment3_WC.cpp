#include <iostream>
#include <string>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

//Website that helped me figure out the syntax for semaphore https://www.bogotobogo.com/cplusplus/multithreading_pthread.php

#define MAX 1

sem_t sem1;
sem_t sem2;

void *see(void *arg){
    int count = 0;
    while(count < 5)
    {
      double FredHeight = 1;
      double WilmaHeight = 7;
      sem_wait(&sem1);
      while(FredHeight < 7)
      {
        FredHeight++;
        WilmaHeight--;
        cout << "See: Fred Height: " << FredHeight << " Wilma Height: " << WilmaHeight << endl;
        sleep(1);
      }
      cout << "SWITCHING DIRECTIONS" << endl;
      sem_post(&sem2);
      count++;
    }
  }

void *saw(void *arg){
  int count1 = 0;
  while(count1 < 5)
  {
    double WilmaHeight = 1;
    double FredHeight = 7;
    sem_wait(&sem2);
    while(WilmaHeight < 7)
    {
      WilmaHeight += 1.5;
      FredHeight -= 1.5;
      cout << "Saw: Fred Height: " << FredHeight << " Wilma Height: " << WilmaHeight << endl;
      sleep(1);
    }
      cout << "SWITCHING DIRECTIONS" << endl;
      sem_post(&sem1);
      count1++;
  }
}

int main(){

  sem_init(&sem1, 0, MAX);
  sem_init(&sem2, 0, 0);

  pthread_t see_thread;
  pthread_t saw_thread;

  int int_see;
  int int_saw;

  int_see = pthread_create(&see_thread, 0, &see, 0);
  int_saw = pthread_create(&saw_thread, 0, &saw, 0);

  pthread_join(see_thread, NULL);
  pthread_join(saw_thread, NULL);

  return 0;
}
