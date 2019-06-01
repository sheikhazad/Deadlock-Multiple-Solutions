#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>

using namespace std;
//For simplicity, entire code is put in single file
//It will avoid the deadlock seen in DeadLockProducer.
//DeadLockSolution3 - Deadlock avoidance by using std::lock() and std::unique_lock
class DeadLockSolution3
{
   public:

       void thread_func();
       void displayFromThread1(const string& sThreadName, const int& iCounter);
       void displayFromThread2(const string& sThreadName, const int& iCounter);

   private:

        std::mutex mutex1;
        std::mutex mutex2;
};
void DeadLockSolution3::displayFromThread1(const string& sThreadName, const int& iCounter)
{
   //RAII - Defer locking mutexes
   unique_lock<mutex> ul1(mutex1, std::defer_lock);
   unique_lock<mutex> ul2(mutex2, std::defer_lock);

   //2. Lock ul1 (not mutex1) first then ul2(not mutex2) - by using standard library
   //It will avoid deadlock seen in DeadLockProducer
   std::lock(ul1, ul2);
   cout<< sThreadName << " : " << iCounter <<endl;
}
void DeadLockSolution3::displayFromThread2(const string& sThreadName, const int& iCounter)
{
    //RAII - Defer locking mutexes
   unique_lock<mutex> ul1(mutex1, std::defer_lock);
   unique_lock<mutex> ul2(mutex2, std::defer_lock);

   //2. Lock ul1 (not mutex1) first then ul2(not mutex2) - by using standard library
   //It will avoid deadlock seen in DeadLockProducer
   std::lock(ul1, ul2);
   cout<< sThreadName << " : " << iCounter <<endl;
}
void DeadLockSolution3::thread_func()
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
    DeadLockSolution3 ds3;
    thread th1(&DeadLockSolution3::thread_func, &ds3 );

    cout<< "In main thread: " << endl;
    int i=200;
    while( i<=300 )
    {
        ds3.displayFromThread1("Thread-1", i);
        ++i;
    }

    th1.join();

    return EXIT_SUCCESS;
}
