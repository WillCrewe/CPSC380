#include <iostream>
#include <string>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

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
        cout << "See: Fred Height: " << FredHeight << endl;
        cout << "See: Wilma Height: " << WilmaHeight << endl;
        sleep(1);
      }
      count++;
    }
      sem_post(&sem2);
  }

void *saw(void *arg){
  int count1 = 0;
  while(count1 < 5)
  {
    double WilmaHeight = 7;
    double FredHeight = 1;
    sem_wait(&sem2);
    while(WilmaHeight > 1)
    {
      WilmaHeight -= 1.5;
      FredHeight += 1.5;
      cout << "Saw: Fred Height: " << FredHeight << endl;
      cout << "Saw: Wilma Height: " << WilmaHeight << endl;
      sleep(1);
    }
      count1++;
  }
    sem_post(&sem1);
}

int main(){

  pthread_t see_thread;
  pthread_t saw_thread;

  int int_see;
  int int_saw;

  int_see = pthread_create(&see_thread, NULL, &see, NULL);
  int_saw = pthread_create(&saw_thread, NULL, &saw, NULL);

  pthread_join(see_thread, NULL);
  pthread_join(saw_thread, NULL);

  return 0;
}
