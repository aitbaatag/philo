/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:18:28 by kait-baa          #+#    #+#             */
/*   Updated: 2024/08/03 17:11:35 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize(t_data *data, int i)
{
	data->philo[i].data = data;
	data->philo[i].id = i + 1;
	data->philo[i].eating = 0;
	data->philo[i].meals_counter = 0;
	data->philo[i].num_eat = data->num_of_times_eat;
	data->philo[i].right_fork = &data->forks[i];
	data->philo[i].last_meal_time = get_current_time();
}

int	philo_init(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->philo || !data->forks)
	{
		perror("Failed to allocate memory for philos or forks");
		return (1);
	}
	init_mutex(data);
	data->dead = 0;
	data->finished = 0;
	while (i < data->num_philo)
	{
		initialize(data, i);
		if (i == 0)
			data->philo[i].left_fork = &data->forks[data->num_philo - 1];
		else
			data->philo[i].left_fork = &data->forks[i - 1];
		pthread_mutex_init(&data->philo[i].lock, NULL);
		i++;
	}
	data->start_time = get_current_time();
	return (0);
}

void	init_fork(t_data *p_data)
{
	int	i;

	i = 0;
	while (p_data->num_philo > i)
	{
		pthread_mutex_init(&p_data->forks[i], NULL);
		i++;
	}
}

void	init_mutex(t_data *data)
{
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	init_fork(data);
}
