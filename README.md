# Philosophers
42 project introduction to multithreading

This project introduces to threads and mutexes usage in C to solve the dining philosopher problem.

To be functional , it must avoid deadlocks (or potential deadlocks) and dataraces , philosophers should also avoid dying.

N philosophers correspond to N threads and each thread has access to two forks (one on the left and one on the right).
In this project, forks are represented by a mutex for each fork.

usage : 

make
./philo [NUMBER_OF_PHILOSOPHERS] [TIME TO DIE] [TIME TO EAT] [TIME TO SLEEP] (optional)[NUMBER_OF_MEALS]

if [NUMBER_OF_MEALS] is unspecified, the philosophers will eat forever unless one of them dies by starvation
