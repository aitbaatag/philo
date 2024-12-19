<a name="readme-top"></a>
<div align="center">
  <!-- Logo -->
  <a href="https://github.com/aitbaatag/philo">
  <img src="readme_file/logo.png" alt="Logo" width="80" height="80">
  </a>

  <!-- Project Name -->
  <h1>Philosophers Project</h1>

Philosophers is a 42 school project designed around Edsger Dijkstra's famous dining philosophers problem. For this project, we must learn about concurrent programming. For the project's mandatory part, we must find a solution to the problem using only threads and mutexes. For the bonus part, we must create a second program that uses processes and semaphores.

This project has been archived in the state it was in at the time of evaluation.

---

:us: Read my articles in English about the concepts tackled in this project:
* [Threads, Mutexes and Concurrent Programming in C](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/)

:fr: Lire mes articles en français sur les concepts abordés dans ce projet :
* [Threads, mutex et programmation concurrente en C](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/)

---

## General Description

TThe idea behind this problem comes from a very popular problem called *the dining philosophers problem*. It goes as follows. A certain number of philosophers sit on a round table. Each philosophers has a fork/chopstick on their left and their right. There are as many forks as philosophers on the table, and every philosopher has a bowl of spaghetti in front of them. Philosophers do these tasks in the following order:

1) Grab fork from both their left and right sides (if they're available) 🍴
2) Start eating for ``X`` amount of time 🍝
3) Release both forks for other philosophers to use
4) Start sleeping for ``X`` amount of time 🌙
5) Start thinking until forks are available to eat again 💭

Additionally, if a philosopher doesn't fetch both forks quickly enough, they will die 💀

## My philo Program

We are asked to compile an executable called ``philo``, which will behave as follows:

```
usage: philo <philo_count> <die_time> <eat_time> <sleep_time> [<repeat_times>]
```

| Argument | Description | Details |
| :------: | :---------: | :-----: |
| ``philo_count`` | Number of philosophers | Larger than ``0`` |
| ``die_time`` | How often a philosopher must eat | At least ``0`` |
| ``eat_time`` | How long it takes for a philosopher to eat | At least ``0`` |
| ``sleep_time`` | How long it takes for a philosopher to sleep | At least ``0`` |
| ``repeat_times`` | Number of times every philosopher must eat before exiting | (optional arg) Larger than ``0`` |

Note: times are measured in milliseconds

## Mandatory Part - Threads and Mutexes

In the mandatory part, each philosopher is a thread and each fork is protected by a mutex. There is exactly one fork between each philosopher and a philosopher must take the forks to his immediate left and right in order to eat.

### Usage

Git clone the project and for the mandatory part:
```shell
cd philosophers/philo
```
To compile, use ```make``` or:

```shell
make BUILD=pretty
```

Run the program with the following arguments:

```shell
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]
```

The arguments must be integers between 0 and INT_MAX representing a time in milliseconds. For example:

```shell
/philo 4 800 200 200 5
```

If the arguments are valid, the program will output the actions of each philosopher until one of them dies or until all of them have eaten number_of_times_each_philo_must_eat, if specified.
