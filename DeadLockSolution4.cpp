#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>

using namespace std;
//For simplicity, entire code is put in single file
//It will avoid the deadlock seen in DeadLockProducer.
//DeadLockSolution4 - Deadlock avoidance by using C++17 - std::scoped_lock() -  RAII and lock in one go.
class DeadLockSolution4
{
   public:

       void thread_func();
       void displayFromThread1(const string& sThreadName, const int& iCounter);
       void displayFromThread2(const string& sThreadName, const int& iCounter);

   private:

        std::mutex mutex1;
        std::mutex mutex2;
};
void DeadLockSolution4::displayFromThread1(const string& sThreadName, const int& iCounter)
{
   //1. Lock mutex1 first then mutex2 - by using C++17 std::scoped_lock()
   //It also provides a convenient RAII-style mechanism
   //It will avoid deadlock seen in DeadLockProducer
   std::scoped_lock<std::mutex, std::mutex>slock(mutex1, mutex2);
   cout<< sThreadName << " : " << iCounter <<endl;
}
void DeadLockSolution4::displayFromThread2(const string& sThreadName, const int& iCounter)
{
    //2. Lock mutex1 first then mutex2 - by using C++17 std::scoped_lock()
   //It also provides a convenient RAII-style mechanism
   //It will avoid deadlock seen in DeadLockProducer
   std::scoped_lock<std::mutex, std::mutex>slock(mutex1, mutex2);
   cout<< sThreadName << " : " << iCounter <<endl;
}
void DeadLockSolution4::thread_func()
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
    DeadLockSolution4 ds1;
    thread th1(&DeadLockSolution4::thread_func, &ds1 );

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
