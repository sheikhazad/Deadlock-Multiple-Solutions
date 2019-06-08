# Deadlock-Multiple-Solutions
This project shows how deadlock is produced and multiple possible solutions.

STEPS TO AVOID DEADLOCK:

i)   Avoid locking multiple mutexes but only 1 mutex if possible
ii)  After locking mutex, avoid calling user provided funtion (that can access/modify the resource without being locked)
iii) If you require to lock more than 1 mutex then try to user API/RAII provided by modern C++ (which are discussed in this project) 
iv)  If you can't use API/RAII mentioned in iii) above then lock the mutexes in the same order.

ENCLOSED FILES:

1. DeadLockProducer.cpp - Shows how deadlock is produced

DEADLOCK AVOIDANCE TECHNIQUES : 
1. DeadLockSolution1.cpp - Deadlock avoidance by following locking hierarchy manually
2. DeadLockSolution2.cpp - Deadlock avoidance by using std::lock() and std::lock_guard
3. DeadLockSolution2.cpp - Deadlock avoidance by using std::lock() and std::unique_lock
4. DeadLockSolution2.cpp - Deadlock avoidance by using C++17 - std::scoped_lock() -  RAII and lock in one go.
TEST RESULTS:
Test results for all cases are attached
