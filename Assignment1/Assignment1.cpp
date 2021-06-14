#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
//Controls the amount of time the threads iterate (total/2 = amount of time each thread is ran)
int Iteration;
//bool to control if the thread can print the specific string
bool M_P;
//mux allowing to pause a thread to allow the other to print its statement
mutex mux;
//Total iterations/2 = amount of times each thread is ran
const int totalIterations = 20;

//Marco function ran during the thread
void Marco() {
    //while loop ran until broken, after maxIterations has been hit
    while (true) {
        //Locking thread using mutex until M_P condition has been met
        mux.lock();
        //condition to check if totalIterations has been hit
        //If true the while loop will be broken, and the thread will be unlocked so it can join()
        if (Iteration >= totalIterations) {
            mux.unlock();
            break;
        }
        //condition to check if statement is able to be printed
        if (M_P == true) {
            //adding to iteration each time Marco is printed
            Iteration++;
            //Setting condition to be false allowing for " Polo\n to be printed"
            M_P = false;
            //Print statement
            cout << "Marco ";
        }
        //After totalIterations has been hit, the mutex unlocks allowing the thread to join
        mux.unlock();
    }
}
//Basically just a repeat of the previous function, just changing the string to be " Polo\n" and adding "That's all folks\n at the end"
void Polo() {
    while (true) {
        mux.lock();
        if (Iteration >= totalIterations) {
            mux.unlock();
            break;
        }
        if (M_P == false) {
            Iteration++;
            M_P = true;
            cout << " Polo\n";
        }
        mux.unlock();
    }
    cout  << "That's all folks\n";
}

int main() {
    //Setting Iteration value to be 0 to start towards totalIterations
    Iteration = 0;
    //Setting M_P to be true to allow for Marco to be the first string printed
    M_P = true;
    //Initializing marco and polo threads
    thread marco_thread(Marco);
    thread polo_thread(Polo);
    //joining threads after totalIterations has been met
    marco_thread.join();
    polo_thread.join();
}
