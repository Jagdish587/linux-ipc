#include <iostream>
#include <thread>
#include <semaphore.h>

sem_t even;
sem_t odd;

int global_counter = 0;

using namespace std;
#define MAX_NUM 50


void evenNumGenerator()
{

    for(int i = 0 ; i<= MAX_NUM; i++)
    {
        sem_wait(&even);
        cout<<"evenNumgenerator = "<<global_counter<<endl;
        global_counter =  global_counter + 1;
        sem_post(&odd);

    }
}

void oddNumGenerator()
{

    for(int i =0; i < MAX_NUM; i++)
    {
        sem_wait(&odd);
        cout<<"oddNumGenerator = "<<global_counter<<endl;
        global_counter =  global_counter + 1;
        sem_post(&even);

    }

}

int main()
{
    // mutex : lock and unlock
    // Semaphore : signalling mechanism , thread which has key can enter Critical Section
    // api documentaion : read man page , man pages are the best place to learn
    // here last argument denotes no of keys , if key = 1 it's also called binary semaphore

    sem_init(&even, 0, 1);
    sem_init(&odd, 0, 0); // initally odd will be zero to block consumer

    // for single producer - consumer
    std::thread t1(evenNumGenerator);
    std::thread t2(oddNumGenerator);

    t1.join();
    t2.join();

   // destroy the semaphores
    sem_destroy(&even);
    sem_destroy(&odd);

    return 0;
}
