#include<iostream>
#include<thread>
#include "rwlock.h"
using namespace std;

RWLock rwlock;

void reader(int id)
{
    rwlock.lock_read();

    cout<<id<<" is reading from file..."<<endl;
    this_thread::sleep_for(chrono::milliseconds(rand()%1000));

    rwlock.unlock_read();
}

void writer(int id)
{
    rwlock.lock_write();

    cout<<id<<" is writing into file..."<<endl;
    this_thread::sleep_for(chrono::milliseconds(rand()%1500));

    rwlock.unlock_write();
}

int main()
{
    srand(time(NULL));
    thread readers[5];
    thread writers[5];

    for(int i=0;i<5;++i)
        readers[i] = thread(reader, i);

    for(int i=0;i<5;++i)
        writers[i] = thread(writer, i);

    for(int i=0;i<5;++i)
        readers[i].join();

    for(int i=0;i<5;++i)
        writers[i].join();

    return 0;
}
