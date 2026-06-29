*This project has been created as part of the 42 curriculum by aamhamdi.*

# Philosophers

## Description

This project is an implementation of the classic **Dining Philosophers** problem, used as a hands-on introduction to concurrency in C: creating threads/processes, and coordinating shared resources without data races or deadlocks.

A given number of philosophers sit around a round table with one fork between each pair of neighbors. Each philosopher endlessly cycles through eating, sleeping, and thinking, but eating requires holding **both** the fork on their left and the fork on their right. A philosopher who goes too long without eating starves and dies — the goal is to keep every philosopher fed indefinitely (or for a required number of meals) without ever letting one starve, and without two philosophers using the same fork at the same time.

Two programs are provided:

- **`philo`** (mandatory) — each philosopher is a **thread**; each fork's state is protected by a **mutex**.
- **`philo_b`** (bonus) — each philosopher is a **process**; the pool of forks is modeled as a **counting semaphore** rather than per-fork state.

### Synchronization design

**Mandatory (`philo`)**: every philosopher always locks its own fork first, then its right-hand neighbor's fork. To avoid the classic "everyone grabs their first fork at once and waits forever for the second" deadlock that this naive lock order can otherwise produce, odd-numbered philosophers begin with a short (10ms) delay before their first attempt, de-synchronizing the table just enough that the cycle doesn't lock in step. A separate monitoring loop (running in the main thread, alongside the detached philosopher threads) polls every philosopher's last-meal timestamp roughly once per millisecond and prints the death message as soon as any philosopher exceeds `time_to_die` — independent of whatever an individual philosopher's thread happens to be doing.

**Bonus (`philo_b`)**: all forks are represented by a single semaphore initialized to `number_of_philosophers`; eating means acquiring it twice (`sem_wait` ×2) and eating ends with releasing it twice (`sem_post` ×2) — there's no per-fork identity, just a shared count, matching "all forks in the middle of the table." Output is serialized through a second semaphore so log lines never interleave. Each philosopher process watches its own starvation deadline while it eats/sleeps and exits itself if it has gone too long since its last meal; the main process never acts as a philosopher and simply waits for all children.

Both programs special-case a single philosopher: with only one fork available, that philosopher can never pick up a second one, so the expected outcome is "takes one fork, then dies" — verified directly (see below).

## Instructions

### Compilation

```bash
make          # builds ./philo   (mandatory)
make bonus    # builds ./philo_b (bonus)
make clean    # removes object files
make fclean   # removes object files and both binaries
make re       # fclean + all
```

Built with `cc -Wall -Wextra -Werror`. Mandatory sources live in `srcs/`, bonus sources in `philo_bonus/`.

### Running

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
./philo_b number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

All time arguments are in milliseconds. The optional last argument stops the simulation once every philosopher has eaten at least that many times; if omitted, the simulation runs until a philosopher dies.

#### Examples (actual output)

A single philosopher always dies — there's only one fork on the table, never enough for a meal:

```bash
$ ./philo 1 800 200 200
18 1 has taken a fork
801 1 died
```

Four philosophers with comfortable timing, capped at 3 meals each, finish cleanly with no deaths:

```bash
$ ./philo 4 410 200 200 3
0 2 has taken a fork
0 2 has taken a fork
0 2 is eating
0 4 has taken a fork
0 4 has taken a fork
0 4 is eating
...
1000 1 is eating
```

Death timing was checked across repeated single-philosopher runs — the reported death consistently landed 1–2ms after the configured `time_to_die`, comfortably inside the 10ms requirement:

```bash
$ ./philo 1 300 50 50
11 1 has taken a fork
301 1 died
```

## Resources

- [POSIX Threads Programming (LLNL tutorial)](https://hpc-tutorials.llnl.gov/posix/) — general background on `pthread_create`/`pthread_mutex_*`.
- `man pthread_mutex_lock`, `man pthread_create`, `man sem_open`, `man gettimeofday` — primary reference material while implementing synchronization and timing.
- Dijkstra's original "Dining Philosophers" problem statement, and general background on deadlock/starvation avoidance strategies for it.
- 42's own Norm documentation, for the coding-style constraints the project must follow.

**AI usage:** AI assistance was used in a limited, advisory role — mainly to reason through *why* a naive "always lock own fork, then neighbor's fork" approach can deadlock for an even or odd number of philosophers, and to sanity-check the odd/even staggered-start idea as a practical mitigation before implementing and testing it. No synchronization code was generated wholesale and pasted in; the mutex/semaphore logic, the monitoring loop, and the single-philosopher edge case were written and tested by hand, with AI used only to pressure-test the reasoning behind the chosen approach.
