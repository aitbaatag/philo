/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:20:37 by kait-baa          #+#    #+#             */
/*   Updated: 2024/08/05 05:27:57 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	check_dead(t_philo *philo, t_data *data)
{
	size_t	current_time;

	pthread_mutex_lock(&philo->lock);
	current_time = get_current_time();
	if (current_time - philo->last_meal_time > data->time_to_die \
		&& philo->eating == 0)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->dead = 1;
		pthread_mutex_unlock(&data->dead_lock);
		print_status(philo, philo->id, DIED);
		pthread_mutex_unlock(&philo->lock);
		return (0);
	}
	if (philo->meals_counter == data->num_of_times_eat)
	{
		pthread_mutex_lock(&data->meal_lock);
		data->finished++;
		philo->meals_counter++;
		pthread_mutex_unlock(&data->meal_lock);
	}
	pthread_mutex_unlock(&philo->lock);
	return (1);
}

void	print_status(t_philo *philo, int pid, char *string)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	pthread_mutex_lock(&philo->data->write_lock);
	if (philo->data->dead == 0 || string[0] == 'd')
		printf("%lu %d %s\n", get_current_time() - \
			philo->data->start_time, pid, string);
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_unlock(&philo->data->write_lock);
}
