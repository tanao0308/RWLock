#include<mutex>
#include<condition_variable>
#include "rwlock.h"
using namespace std;

RWLock::RWLock(): reader_count(0), writing(0) {}

void RWLock::lock_read()
{
    unique_lock<mutex> lock(mtx);
    while(!can_read())
        cond_read.wait(lock);//参数是什么

    reader_count++;
}

void RWLock::unlock_read()
{
    unique_lock<mutex> lock(mtx);

    reader_count--;
    if(reader_count == 0)
        cond_write.notify_one();
}

void RWLock::lock_write()
{
    unique_lock<mutex> lock(mtx);
    while(!can_write())
        cond_write.wait(lock);

    writing = 1;
}

void RWLock::unlock_write()
{
    unique_lock<mutex> lock(mtx);
    
    writing = 0;
    cond_read.notify_all();
    cond_write.notify_one();
}

bool RWLock::can_read()
{
    return writing == 0;
}

bool RWLock::can_write()
{
    return reader_count == 0 && writing == 0;
}
