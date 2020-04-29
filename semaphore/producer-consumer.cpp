#include <iostream>
#include <thread>
#include <semaphore.h>

sem_t empty;
sem_t full;
sem_t mutex;

int current_in = 0 ;
int current_out = 0;
int sem_value = 0;

using namespace std;

#define NUM_TOTAL_BUFFERS 5
#define DATA_LENGTH 20
int buffer[NUM_TOTAL_BUFFERS];

void producer()
{

    for(int i = 0 ; i<DATA_LENGTH; i++)
    {
        sem_wait(&empty);
        // lock the critical section and unock it
        sem_wait(&mutex);

        buffer[current_in] = current_in;

        sem_getvalue(&empty,&sem_value);
        cout<<"producer empty sem_value = "<<sem_value<<endl;
        cout<<"producer: in buffer = "<<buffer[current_in]<<endl;

        current_in = (current_in + 1) % NUM_TOTAL_BUFFERS;

        sem_post(&mutex);
        sem_post(&full);

    }
}

void consumer()
{

    for(int i =0; i < DATA_LENGTH; i++)
    {
        sem_wait(&full);

        // lock the critical section
        sem_wait(&mutex);

        cout<<"consumer value in buffer = "<<buffer[current_out]<<endl;

        current_out = (current_out + 1) % NUM_TOTAL_BUFFERS;

        // unlock the critical section
        sem_post(&mutex);

        sem_post(&empty);

    }

}

int main()
{
    // mutex : lock and unlock
    // Semaphore : signalling mechanism , thread which has key can enter Critical Section
    // api documentaion : read man page , man pages are the best place to learn
    // here last argument denotes no of keys , if key = 1 it's also called binary semaphore


    // Need for locking mutex
    sem_init(&mutex,0, 1);

    sem_init(&empty, 0, NUM_TOTAL_BUFFERS);
    sem_init(&full, 0, 0); // initally full will be zero to block consumer


#if 0
    // for single producer - consumer
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
#endif

#if 1

    std::thread t1[3];
    std::thread t2[3];

    // Launch a group of threads

    for (int i = 0; i < 3; ++i) {
        t1[i] = std::thread(producer);
    }

    for (int i = 0; i < 3; ++i) {
        t2[i] = std::thread(consumer);
    }


    for(int i =0; i< 3; i++)
        t1[i].join();

   for(int i =0; i< 3; i++)
      t2[i].join();

#endif

   // destrory the semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}
