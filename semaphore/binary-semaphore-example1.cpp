#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

sem_t mutex;

void mythread_funcA()
{
    // this decrements the counter , also called P - verlagen , means to decrease
    sem_wait(&mutex);

    cout<<"inside thread mythread_funcA  "<<this_thread::get_id()<<endl;

    // This increments the semaphore value , also called V - verhogen , means to increase in dutch
    sem_post(&mutex);
}



int main()
{
    // Mutex : lock and unlock
    // Semaphore : signalling mechanism , thread which has key can enter Critical Section
    // api documentaion : read man page , man pages are the best place to learn
    // here last argument denotes no of keys , if key = 1 it's also called binary semaphore
    sem_init(&mutex, 0, 1);

    thread t1(mythread_funcA);
    thread t2(mythread_funcA);


    t1.join();
    t2.join();

    sem_destroy(&mutex);

    return 0;
}
