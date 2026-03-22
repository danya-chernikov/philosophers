*This project has been created as part of the 42 curriculum by dchernik.*

# Philosophers

## Description

**Philosophers** is a 42 project focused on concurrent programming in C. Its goal is to introduce the practical use of threads and mutexes through the classical **Dining Philosophers** problem.

In this simulation, several philosophers sit around a circular table. There is one fork between each pair of philosophers, and each philosopher must take both adjacent forks to eat. During the simulation, philosophers alternate between **eating**, **sleeping**, and **thinking**.

The program stops when:

- a philosopher dies, or
- every philosopher has eaten at least the required number of times, if the optional argument is provided.

The main objective of the project is not only to make the simulation work, but to do so correctly under concurrency constraints: without data races, without deadlocks, with consistent logging, and with proper resource management.

## Instructions

### Compilation

Use the provided Makefile:

```bash
make
```

Useful Makefile rules:

```bash
make
make clean
make fclean
make re
```

### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

- `number_of_philosophers`
  Number of philosophers, and also the number of forks.

- `time_to_die`
  Time in milliseconds. If a philosopher does not start eating within this time since the beginning of the simulation or since the start of the last meal, that philosopher dies.

- `time_to_eat`
  Time in milliseconds spent eating.

- `time_to_sleep`
  Time in milliseconds spent sleeping.

- `number_of_times_each_philosopher_must_eat`
  Optional argument. If all philosophers eat at least this many times, the simulation stops.

### Examples

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
```

## Output Format

The program prints state changes in the following format:

```text
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

Where:

- `timestamp_in_ms` is the number of milliseconds since the start of the simulation.
- `X` is the philosopher number.

## Features and Technical Decisions

This implementation uses:

- one thread per philosopher
- one additional monitor thread
- one mutex per fork
- additional mutexes to protect shared state

### Main Structures

The project is organized around two main structures:

- `t_rules`
  Stores common simulation parameters and shared synchronization objects.

- `t_philo`
  Stores the state of a single philosopher.

### Synchronization Strategy

The program uses several mutexes:

- **fork mutexes**
  Protect access to forks so that the same fork cannot be taken by two philosophers at the same time.

- **print mutex**
  Ensures that log lines are printed atomically and never overlap.

- **stop mutex**
  Protects the simulation stop flag.

- **meal mutex**
  Protects per-philosopher meal data such as the last meal time and the number of meals eaten.

- **full mutex**
  Protects the shared `full_count`, that is, the number of philosophers who have already reached the required number of meals.

### Deadlock Prevention

To reduce the risk of deadlock, philosophers do not all take forks in the same order:

- even philosophers take forks in one order
- odd philosophers take forks in the opposite order

Additionally, even-numbered philosophers start with a very small delay to reduce initial contention.

### Monitoring

A dedicated monitor thread repeatedly checks whether a philosopher has died.

The optional stopping condition based on `number_of_times_each_philosopher_must_eat` is handled through a protected shared counter. When the last philosopher reaches the required meal count, the simulation stop flag is set.

### Special Case: One Philosopher

If there is only one philosopher, that philosopher can only take one fork and can never eat, because eating requires two forks. In that case, the philosopher eventually dies after `time_to_die`.

## Project Structure

```text
philo/
├── actions.c
├── cleanup.c
├── ft_aux.c
├── init.c
├── init2.c
├── main.c
├── Makefile
├── monitor.c
├── parse.c
├── philo.h
├── routine.c
├── start.c
├── state.c
└── time.c
```

## File Roles

- `main.c`
  Entry point, initialization, thread start, join, and cleanup.

- `parse.c`
  Argument count and argument format validation.

- `init.c`, `init2.c`
  Structure initialization, memory allocation, and mutex initialization.

- `start.c`
  Thread creation for philosophers and the monitor.

- `routine.c`
  Main philosopher routine and the one-philosopher case.

- `actions.c`
  Fork locking, eating logic, and full-state updates.

- `monitor.c`
  Death detection.

- `state.c`
  Stop flag access and synchronized status printing.

- `time.c`
  Time utilities and controlled sleeping.

- `cleanup.c`
  Thread joining, mutex destruction, and memory release.

- `ft_aux.c`
  Small helper functions used by the project.

## Design Notes

### Why `smart_sleep` is used

A long single `usleep()` would make threads react too slowly to the stop condition. Instead, sleeping is split into small chunks so the thread can regularly check whether the simulation should stop.

### Why there is a common `start_ms`

All threads wait for a common start time so that:

- the simulation begins in a coordinated way
- timestamps are consistent
- the initial death timer is measured correctly from the same reference point

### Why the stop flag is protected

The stop flag is shared between multiple threads:

- the monitor may set it
- philosophers may read it

Accessing it without synchronization would create a data race.

## Error Handling

The program checks and handles errors for:

- invalid arguments
- memory allocation failure
- mutex initialization failure
- thread creation failure
- thread joining failure

If initialization fails, already allocated resources are released properly.

## Testing

### Basic Tests

```bash
./philo 1 800 200 200
./philo 2 800 200 200
./philo 5 800 200 200
./philo 5 800 200 200 7
```

### Edge Cases

```bash
./philo 4 310 200 100
./philo 4 210 100 100
./philo 200 800 200 200
./philo 5 60 100 100
```

## Resources

### Books

The following books were especially useful for understanding systems programming, UNIX process and thread behavior, and POSIX synchronization:

1. **Linux System Programming, Second Edition** — Robert Love
2. **Advanced Programming in the UNIX Environment, Third Edition** — W. Richard Stevens and Stephen A. Rago
3. **Pthreads Programming** — Dick Buttlar, Jacqueline Farrell, Bradford Nichols

### Additional Topics

- POSIX threads
- mutex synchronization
- deadlock prevention
- race condition detection
- Valgrind and Helgrind usage

### AI Usage Declaration

AI was **not** used to implement the project itself.

It was used only as a supporting tool for:

- discussing theoretical questions related to threads, mutexes, and synchronization
- reviewing some design decisions during debugging
- clarifying edge cases and testing ideas
- correcting grammar in some commit messages and documentation text

## Author

- **dchernik** — 42 student
