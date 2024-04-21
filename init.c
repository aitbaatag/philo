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
		data->philo[i].dead = 1;
		data->philo[i].meals_counter = 0;
		data->philo[i].write_lock = &data->write_lock;
		data->philo[i].dead_lock = &data->dead_lock;
		data->philo[i].meal_lock = &data->meal_lock;
		data->philo[i].right_fork = &forks[i];
		if (i == 0)
			data->philo[i].left_fork = &forks[data->num_philo - 1];
		else
			data->philo[i].left_fork = &forks[i - 1];
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