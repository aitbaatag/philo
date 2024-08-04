/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:20:28 by kait-baa          #+#    #+#             */
/*   Updated: 2024/08/04 23:32:32 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_it(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->philo[i].lock);
		i++;
	}
	free(data->philo);
	free(data->forks);
}

int	main(int argc, char *argv[])
{
	t_data	p_data;

	if (parsing(argc, argv, &p_data) != 0)
		return (1);
	if (philo_init(&p_data) != 0)
		return (1);
	if (philosopher_thread(&p_data) != 0)
		return (1);
	free_it(&p_data);
	return (0);
}
