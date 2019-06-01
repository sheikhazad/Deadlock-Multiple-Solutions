
#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>

using namespace std;
//For simplicity, entire code is put in single file
class DeadLockProducer
{
   public:

       void thread_func();
       void displayFromThread1(const string& sThreadName, const int& iCounter);
       void displayFromThread2(const string& sThreadName, const int& iCounter);

   private:

        std::mutex mutex1;
        std::mutex mutex2;
};
void DeadLockProducer::displayFromThread1(const string& sThreadName, const int& iCounter)
{
   //1. Lock mutex1 first then mutex2
   //It will cause deadlock
   lock_guard<mutex> lg1(mutex1);
   lock_guard<mutex> lg2(mutex2);
   cout<< sThreadName << " : " << iCounter <<endl;
}
void DeadLockProducer::displayFromThread2(const string& sThreadName, const int& iCounter)
{
    //2. Lock mutex2 first then mutex1
    //It will cause deadlock
   lock_guard<mutex> lg2(mutex2);
   lock_guard<mutex> lg1(mutex1);
   cout<< sThreadName << " : " << iCounter <<endl;
}
void DeadLockProducer::thread_func()
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
    DeadLockProducer dlp;
    thread th1(&DeadLockProducer::thread_func, &dlp );

    cout<< "In main thread: " << endl;
    int i=200;
    while( i<=300 )
    {
        dlp.displayFromThread1("Thread-1", i);
        ++i;
    }

    th1.join();

    return EXIT_SUCCESS;
}
