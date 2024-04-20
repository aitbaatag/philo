#include "philo.h"
void lock(pthread_mutex_t lock)
{
    if (pthread_mutex_lock(&lock) != 0)
        return (1, write (2, "mutex_lock\n", 12));
}
void unlock(pthread_mutex_t lock)
{
    if (pthread_mutex_unlock(&lock) != 0)
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