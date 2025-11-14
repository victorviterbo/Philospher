# Philosophers - Dining Philosophers Problem

A solution to the classic Dining Philosophers problem, focusing on concurrency and synchronization. It demonstrates how to prevent deadlocks and race conditions using threads and mutexes.

## 🍝 Problem Description
- N philosophers sit at a round table with a bowl of spaghetti
- Forks are placed between each philosopher (N forks total)
- Philosophers alternate between eating, sleeping and thinking
- A Philosopher will eat for [time_to_eat] then sleep for [time_to_sleep]. Once he wakes up he will think until he starts eating again.
- A Philosopher needs to start eating at most [time_to_die] after the beggining of it's last meal.
- A philosopher needs to have the fork to its left and to its right available to eat
- If a number of meal is specified, the simulation stops when all Philosophers have eaten that number of meals
- Keep Philosophers alive !

## 🔧 Technical Implementation
- Thread creation and management (`pthread`)
- Mutexes for shared resource protection (forks, print etc.)
- Timestamped logging of philosopher states
- Event detection (death, [number_of_meals] reached etc.) and simulation termination

## 🚀 Usage
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (optional)[number_of_meals]

The details of the project requirement are described in Philosopher.pdf
