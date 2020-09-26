#include <iostream>
#include <thread>
#include <mutex>
//#include <atomic>
#include <condition_variable>
using namespace std;

int compteur = 0;
int compteurImpair = -1;
int compteurPair = -2;
//atomic<int> compteurAtomic;
condition_variable cond_var;
mutex m;

void incrementImpair() {
    for(int i = 0; i < 500; i++)
    {
        compteurImpair += 2;
        cout << "Thread 2 " << endl;
        cout << compteurImpair << endl;
    }
}

void incrementPair() {
    for(int i = 0; i <= 500; i++)
    {
        compteurPair += 2;
        cout << "Thread 1 " << endl;
        cout << compteurPair << endl;
    }
}

/*void incrementAtomic() {
    for(int i =0; i <= 500; i++)
    {
        compteurAtomic++;
        cout << compteur << endl;
    }
}*/

void incrementPairMutex(string threadName) {
    for(int i = 0; i <= 500; i++)
    {
        unique_lock<mutex> lck(m);
        cond_var.wait(lck, []{return compteur%2 == 0 ;});
        cout << threadName << endl;
        cout << compteur << endl;
        compteur++;
        lck.unlock();
        cond_var.notify_all();
    }
}

void incrementImpairMutex(string threadName) {
    for(int i = 0; i < 500; i++)
    {
        unique_lock<mutex> lck(m);
        cond_var.wait(lck, []{return compteur%2 == 1 ;});
        cout << threadName << endl;
        cout << compteur << endl;
        compteur++;
        lck.unlock();
        cond_var.notify_all();
    }
}

int main() {

    /*thread T1(incrementPair);
    thread T2(incrementImpair);
    T1.join(); T2.join();*/

    //Ne fonctionne pas
    /*compteurAtomic.store(2);
    thread T3(incrementAtomic);
    thread T4(incrementAtomic);
    T3.join(); T4.join();*/

    thread T5(incrementPairMutex, "Thread 5");
    thread T6(incrementImpairMutex, "Thread 6");
    T5.join(); T6.join();
    return 0;
}