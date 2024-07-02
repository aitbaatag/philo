#include "philo.h"

void  *monitoring(void *data)
{
	t_data *philo;

	philo = (t_data *)data;
	    while (philo->dead == 0) {
        pthread_mutex_lock(&philo->dead_lock);
        if (philo->finished >= philo->num_philo)
            philo->dead = 1;
        pthread_mutex_unlock(&philo->dead_lock);
    }
    return ((void *)0);
}
void *start_routine(void *arg)
{
	t_philo *data;

	data = (t_philo *)arg;
	if (data->id % 2 == 0)
		ft_usleep(1);
	while (data->data->dead == 0)
	{
		lock(data->right_fork);
		printf_status(data, data->id, "has taken a fork");
		lock(data->left_fork);
		printf_status(data, data->id, "has taken a fork");
		data->eating = 1;
		lock(&data->lock);
		data->last_meal_time = 	get_current_time();
		data->meals_counter++;
		unlock(&data->lock);
		printf_status(data, data->id, EAT);
		ft_usleep(data->data->time_to_eat);
		data->eating = 0;
		unlock(data->right_fork);
		unlock(data->left_fork);
		printf_status(data, data->id, SLEEP);
		ft_usleep(data->data->time_to_sleep);
		printf_status(data, data->id, THINK);
	}
}
int	philosopher_thread(t_data *data)
{
	int i;
	pthread_t	id_toring;

	i = 0;
	if(pthread_create(&id_toring, NULL, monitoring, (void *)data) != 0)
			return (0);
	while (i < data->num_philo)
	{
		data->philo[i].last_meal_time = get_current_time();
		if(pthread_create(&data->philo[i].thread_id, NULL, start_routine, (void *)&data->philo[i]) != 0)
			return (0);
		i++;
	}
	pthread_join(&id_toring, NULL);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(&data->philo[i].thread_id, NULL);
		i++;
	}
	return NULL;
}