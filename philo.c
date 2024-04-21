#include "philo.h"

int  monitoring(t_data *data)
{

}
void *start_routine(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	while (data->philo->dead)
	{
		check_dead(data->philo, data);
	}
}
int	philosopher_thread(t_data *data)
{
	int i;

	i = 0;
	data->philo->start_time = get_current_time();
	while (i < data->num_philo)
	{
		if(pthread_create(&data->philo[i].thread_id, NULL, start_routine, (void *)data) != 0)
			return (0);
		i++;
	}
	while (i < data->num_philo)
	{
		pthread_join(&data->philo[i].thread_id, NULL);
		i++;
	}
	return NULL;
}