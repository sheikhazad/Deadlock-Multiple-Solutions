
#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>

using namespace std;
//For simplicity, entire code is put in single file
//It will avoid the deadlock seen in DeadLockProducer.
//DeadlockSolution2 - Deadlock avoidance by using std::lock() and std::lock_guard
class DeadlockSolution2
{
   public:

       void thread_func();
       void displayFromThread1(const string& sThreadName, const int& iCounter);
       void displayFromThread2(const string& sThreadName, const int& iCounter);

   private:

        std::mutex mutex1;
        std::mutex mutex2;
};
void DeadlockSolution2::displayFromThread1(const string& sThreadName, const int& iCounter)
{
   //1. Lock mutex1 first then mutex2 - by using standard library
   //It will avoid deadlock seen in DeadLockProducer
   std::lock(mutex1, mutex2);
   //RAII - Mutexes are already locked but adopt to the ownership of the mutex
   //so that when it goes out of scope unlock the mutex
   lock_guard<mutex> lg1(mutex1, std::adopt_lock);
   lock_guard<mutex> lg2(mutex2, std::adopt_lock);
   cout<< sThreadName << " : " << iCounter <<endl;
}
void DeadlockSolution2::displayFromThread2(const string& sThreadName, const int& iCounter)
{
    //2. Lock mutex1 first then mutex2 - by using standard library
   //It will avoid deadlock seen in DeadLockProducer
   std::lock(mutex1, mutex2);
   //RAII - Mutexes are already locked but adopt to the ownership of the mutex
   //so that when it goes out of scope unlock the mutex
   lock_guard<mutex> lg1(mutex1, std::adopt_lock);
   lock_guard<mutex> lg2(mutex2, std::adopt_lock);
   cout<< sThreadName << " : " << iCounter <<endl;
}
void DeadlockSolution2::thread_func()
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
    DeadlockSolution2 ds;
    thread th1(&DeadlockSolution2::thread_func, &ds );

    cout<< "In main thread: " << endl;
    int i=200;
    while( i<=300 )
    {
        ds.displayFromThread1("Thread-1", i);
        ++i;
    }

    th1.join();

    return EXIT_SUCCESS;
}
