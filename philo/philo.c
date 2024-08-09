/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:20:32 by kait-baa          #+#    #+#             */
/*   Updated: 2024/08/09 14:54:47 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo, pthread_mutex_t *first_fork, \
	pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	if (check_death_status(philo))
	{
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	print_status(philo, philo->id, "has taken a fork");
	if (philo->data->num_philo == 1)
	{
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	pthread_mutex_lock(second_fork);
	if (check_death_status(philo))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (0);
	}
	print_status(philo, philo->id, "has taken a fork");
	return (1);
}

void	eat_sleep_think(t_philo *philo, pthread_mutex_t *first_fork, \
	pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(&philo->lock);
	print_status(philo, philo->id, EAT);
	philo->last_meal_time = get_current_time();
	philo->eating = 1;
	pthread_mutex_unlock(&philo->lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->lock);
	philo->meals_counter++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	if (check_death_status(philo))
		return ;
	print_status(philo, philo->id, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
	if (check_death_status(philo))
		return ;
	print_status(philo, philo->id, THINK);
}

void	perform_philosopher_actions(t_philo *philo, \
	pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	if (take_forks(philo, first_fork, second_fork))
	{
		eat_sleep_think(philo, first_fork, second_fork);
	}
}

void	*start_routine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		second_fork = philo->right_fork;
		first_fork = philo->left_fork;
	}
	if (philo->id % 2 == 0)
		usleep(500);
	while (true)
	{
		if (check_death_status(philo))
			break ;
		perform_philosopher_actions(philo, first_fork, second_fork);
		usleep(500);
	}
	return (NULL);
}

int	philosopher_thread(t_data *data)
{
	int			i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, \
				start_routine, (void *)&data->philo[i]) != 0)
			return (1);
		i++;
	}
	monitoring(data);
	i = -1;
	while (++i < data->num_philo)
		pthread_join(data->philo[i].thread_id, NULL);
	return (0);
}
