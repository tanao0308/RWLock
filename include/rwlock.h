#ifndef RWLOCK_H
#define RWLOCK_H

#include<mutex>
#include<condition_variable>
using namespace std;

class RWLock
{
public:
    RWLock();
    void lock_read();
    void unlock_read();
    void lock_write();
    void unlock_write();
private:
    mutex mtx;
	int reader_count;
    bool writing;
    condition_variable cond_read;
    condition_variable cond_write;

    bool can_read();
    bool can_write();
};

#endif
