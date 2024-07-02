#include "philo.h"
void	philo_init(t_data *data, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	forks = malloc(data->num_philo * sizeof(pthread_mutex_t));
	if (fork == NULL)
		error_exit("error malloc");
	data->philo = malloc(data->num_philo * sizeof(t_philo));
	if (data->philo == NULL)
		error_exit("error malloc");
	while (i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_counter = 0;
		data->philo[i].full = 0;
		data->dead = 0;
		data->philo->eating = 0;
		data->philo->meals_counter = 0;
		data->finished = 0;
		data->philo[i].num_eat = data->num_of_times_eat;
		data->philo[i].meals_counter = 0;
		data->philo[i].right_fork = &forks[i];
		if (i == 0)
			data->philo[i].left_fork = &forks[data->num_philo - 1];
		else
			data->philo[i].left_fork = &forks[i - 1];
		pthread_mutex_init(&data->philo[i].lock, NULL);
		i++;
	}
}
void    init_fork(t_data *p_data)
{
	int i;

	i = 0;
	while (p_data->num_philo > i)
	{
		if(pthread_mutex_init(&p_data->fork->forks[i], NULL) != 0)
			error_exit("mutex init has failed\n");
		i++;
	}
}
void init_mutex(t_data *data)
{
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	init_fork(data);
}