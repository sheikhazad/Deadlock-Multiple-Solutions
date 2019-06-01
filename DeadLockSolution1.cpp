
#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>

using namespace std;
//For simplicity, entire code is put in single file
//It will avoid the deadlock seen in DeadLockProducer.
//DeadLockSolution1 - Deadlock avoidance by following locking hierarchy manually
class DeadLockSolution1
{
   public:

       void thread_func();
       void displayFromThread1(const string& sThreadName, const int& iCounter);
       void displayFromThread2(const string& sThreadName, const int& iCounter);

   private:

        std::mutex mutex1;
        std::mutex mutex2;
};
void DeadLockSolution1::displayFromThread1(const string& sThreadName, const int& iCounter)
{
   //1. Lock mutex1 first then mutex2 - Follow locking hierarchy in increasing order manually
   //It will avoid deadlock seen in DeadLockProducer
   lock_guard<mutex> lg1(mutex1);
   lock_guard<mutex> lg2(mutex2);
   cout<< sThreadName << " : " << iCounter <<endl;
}
void DeadLockSolution1::displayFromThread2(const string& sThreadName, const int& iCounter)
{
    //2. Lock mutex1 first then mutex2 - Follow locking hierarchy in increasing order manually
   //It will avoid deadlock seen in DeadLockProducer
   lock_guard<mutex> lg1(mutex1);
   lock_guard<mutex> lg2(mutex2);
   cout<< sThreadName << " : " << iCounter <<endl;
}
void DeadLockSolution1::thread_func()
{
    cout<< "In thread 2: " << endl;
    int i=0;
    while( i<=100 )
    {
        displayFromThread2("Thread-2", i);
        ++i;
    }

}
int main(int argc, char** argv)
{
    DeadLockSolution1 ds1;
    thread th1(&DeadLockSolution1::thread_func, &ds1 );

    cout<< "In main thread: " << endl;
    int i=200;
    while( i<=300 )
    {
        ds1.displayFromThread1("Thread-1", i);
        ++i;
    }

    th1.join();

    return EXIT_SUCCESS;
}
