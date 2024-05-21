/*
Q: 为什么不用lock_guard代替unique_lock?
A: condition_variable需要在wait时手动释放锁，而lock_guard没有这个功能
*/
#include<mutex>
#include<condition_variable>
#include "rwlock.h"
using namespace std;

RWLock::RWLock(): reader_count(0), writing(0) {}

void RWLock::lock_read()
{
	// mutex是互斥量，也叫互斥锁
	// unique_lock是锁管理器
    unique_lock<mutex> lock(mtx);
    while(!can_read())
        cond_read.wait(lock);
	// cond_read.wait()等待时会自动释放互斥锁，并在唤醒后重新获得该锁。

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
