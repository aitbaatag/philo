#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

typedef struct s_philo_data t_data;
/*
** Error messages
*/
# define NUM_ARGS "ERROR: The number of argments must be 4 or 5"
# define ARG1 "ERROR: There is a mistake in number of philosophers"
# define ARG2 "ERROR: There is a mistake in time to die"
# define ARG3 "ERROR: There is a mistake in time to eat"
		
# define ARG4 "ERROR: There is a mistake in time to sleep"
# define ARG5 "ERROR: There is a mistake in number of times each \
philosopher must eat"

/*
** Help message
*/
# define HELP "The number of argments must be 4 or 5:\n\
- arg1 number of philosophers\n\
- arg2 time to die\n\
- arg3 time to eat\n\
- arg4 time to sleep\n\
- arg5 number of times each philosopher must eat (optional)"
/*
** Routines messages
*/
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIED "died ☠️"

typedef struct  s_philosophers	
{
	int				id;
	int				full;
	size_t				meals_counter;
	size_t			last_meal_time;
	int num_eat;
	int eating;
	size_t		start_time;
	pthread_mutex_t	*	write;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t lock;
	t_data *data;
}		t_philo;

typedef struct s_philo_data
{
	int					num_philo;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				num_of_times_eat;
	size_t		start_time;
	int				dead;
	int finished;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philo;
	pthread_mutex_t *forks;
}		t_data;
int		parsing(int argc, char *argv[], t_data *p_data);
int		ft_atoi(const char *str);
int	philo_init(t_data *data);
void    init_fork(t_data *p_data);
int	philosopher_thread(t_data *data);
int lock(pthread_mutex_t *lock);
int unlock(pthread_mutex_t *lock);
size_t	get_current_time(void);
int	ft_usleep(size_t milliseconds);
int check_dead(t_philo *philo, t_data *data);
void error_exit(char *str);
void *start_routine(void *arg);
int	philosopher_thread(t_data *data);
void	print_status(t_philo *data, int pid, char *string);
void init_mutex(t_data *data);
#endif