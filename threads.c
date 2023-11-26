/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:33:23 by anayef            #+#    #+#             */
/*   Updated: 2023/11/26 11:03:46 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pass_a_time(long time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
	}
}

int	thread_join(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args->philo_n)
		if (pthread_join(table->philos[i]->thread_id, NULL))
			return (0);
	if (pthread_join(table->reaper, NULL))
		return (0);
	return (1);
}

int	thread_create(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args->philo_n)
	{
		if (pthread_create(&table->philos[i]->thread_id,
				NULL, cycle, table->philos[i]))
			return (0);
		usleep(1000);
	}
	if (pthread_create(&table->reaper, NULL, reap, table))
		return (0);
	if (thread_join(table) == 0)
		return (0);
	return (1);
}

int	table_destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args->philo_n)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i]->sated_lock);
		free(table->philos[i]);
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->finish_lock);
	return (1);
}
