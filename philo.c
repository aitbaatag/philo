/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:20:32 by kait-baa          #+#    #+#             */
/*   Updated: 2024/08/03 01:56:13 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *data)
{
	t_data	*philo;
	int		i;

	philo = (t_data *)data;
	while (true)
	{
		pthread_mutex_lock(&philo->dead_lock);
		if (philo->dead == 1)
		{
			pthread_mutex_unlock(&philo->dead_lock);
			break ;
		}
		if (philo->finished >= philo->num_philo)
		{
			philo->dead = 1;
			pthread_mutex_unlock(&philo->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->dead_lock);
		i = -1;
		while (++i < philo->num_philo)
			if (check_dead(&philo->philo[i], philo) == 0)
				break ;
	}
	return ((void *)0);
}

void	perform_philosopher_actions(t_philo *philo, pthread_mutex_t *first_fork \
		, pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	print_status(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_status(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->lock);
	print_status(philo, philo->id, EAT);
	philo->last_meal_time = get_current_time();
	philo->eating = 1;
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->lock);
	philo->meals_counter++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	print_status(philo, philo->id, SLEEP);
	ft_usleep(philo->data->time_to_sleep);
	print_status(philo, philo->id, THINK);
}

int	check_death_status(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->dead_lock) > 1)
		return (2);
	if (philo->data->dead == 1)
	{
		if (pthread_mutex_unlock(&philo->data->dead_lock))
			return (2);
		else
			return (1);
	}
	if (pthread_mutex_unlock(&philo->data->dead_lock) > 0)
		return (2);
	return (0);
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
	while (true)
	{
		if (check_death_status(philo))
			break ;
		perform_philosopher_actions(philo, first_fork, second_fork);
	}
	return (NULL);
}

int	philosopher_thread(t_data *data)
{
	int			i;
	pthread_t	id_toring;

	i = 0;
	if (pthread_create(&id_toring, NULL, monitoring, (void *)data) != 0)
		return (1);
	data->start_time = get_current_time();
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, \
				start_routine, (void *)&data->philo[i]) != 0)
			return (1);
		ft_usleep(1);
		i++;
	}
	i = -1;
	if (data->num_philo != 1)
	{
		while (++i < data->num_philo)
			pthread_join(data->philo[i].thread_id, NULL);
	}
	pthread_detach(id_toring);
	return (0);
}
