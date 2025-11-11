# Philosophers - Dining Philosophers Problem

A solution to the classic Dining Philosophers problem, focusing on concurrency and synchronization. It demonstrates how to prevent deadlocks and race conditions using threads and mutexes.

## 🍝 Problem Description
- N philosophers sit at a round table with a bowl of spaghetti
- Forks are placed between each philosopher (N forks total)
- Philosophers alternate between thinking and eating
- A philosopher needs two forks to eat
- Must prevent deadlock and starvation

## 🔧 Technical Implementation
- Thread creation and management (`pthread`)
- Mutexes for shared resource protection (forks)
- Timestamped logging of philosopher states
- Death detection and simulation termination

## 🚀 Usage
make
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (optional)[number_of_meals]
