#include "philo.h"

void  *monitoring(void *data)
{
	
}
void *start_routine(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	while (data->philo->num_eat)
	{
		lock(data->philo->right_fork);
		printf_status(data, data->philo->id, "has taken a fork");
		lock(data->philo->left_fork);
		printf_status(data, data->philo->id, "has taken a fork");
	}
}
int	philosopher_thread(t_data *data)
{
	int i;

	i = 0;
	if(pthread_create(&data->philo[i].thread_id, NULL, monitoring, (void *)data) != 0)
			return (0);
	while (i < data->num_philo)
	{
		data->philo[i].start_time = get_current_time();
		if(pthread_create(&data->philo[i].thread_id, NULL, start_routine, (void *)data) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(&data->philo[i].thread_id, NULL);
		i++;
	}
	return NULL;
}