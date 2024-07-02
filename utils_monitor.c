#include "philo.h"
int lock(pthread_mutex_t *lock)
{
    if (pthread_mutex_lock(lock) != 0)
        return (1, write (2, "mutex_lock\n", 12));
}
int unlock(pthread_mutex_t *lock)
{
    if (pthread_mutex_unlock(lock) != 0)
        return (1, write (2, "mutex_lock\n", 12));
}
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void check_dead(t_philo *philo, t_data *data)
{
	size_t current_time;
	
	current_time = get_current_time();
    pthread_mutex_lock(&philo->lock);
	if (current_time - philo->last_meal_time >= data->time_to_die && philo->eating == 0)
		*philo->data->dead = 0;
	if (philo->meals_counter == philo->data->num_of_times_eat) {
            philo->data->finished++;
            philo->meals_counter++;
        }
    pthread_mutex_unlock(&philo->lock);
}
void	print_status(t_data *data, int pid, char *string)
{
  pthread_mutex_lock(&data->write_lock);
  printf("%lld %d %s", ft_time_in_ms() - data->philo->last_meal_time, pid, string);
}