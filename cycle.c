/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:27:24 by anayef            #+#    #+#             */
/*   Updated: 2023/11/26 10:38:49 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	done_eating(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->args->philo_n)
	{
		pthread_mutex_lock(&table->philos[i]->sated_lock);
		if (table->philos[i]->meal_count != table->args->meals_n)
		{
			pthread_mutex_unlock(&table->philos[i]->sated_lock);
			return (0);
		}
		pthread_mutex_unlock(&table->philos[i]->sated_lock);
		i++;
	}
	pthread_mutex_lock(&table->finish_lock);
	table->finish = 1;
	pthread_mutex_unlock(&table->finish_lock);
	return (1);
}

void	*reap(void *table_ptr)
{
	t_table	*table;
	int		finish;

	table = (t_table *)table_ptr;
	pthread_mutex_lock(&table->finish_lock);
	finish = table->finish;
	pthread_mutex_unlock(&table->finish_lock);
	if (finish)
		return (NULL);
	while (done_eating(table) == 0)
	{
		if (dead_philo(table) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static int	cycle_execute(t_philo *philo)
{
	if (eating_philo(philo) == 0)
		return (0);
	if (sleeping_philo(philo) == 0)
		return (0);
	if (thinking_philo(philo) == 0)
		return (0);
	return (1);
}

static int	is_meal_over(t_philo *philo)
{
	int	finish;
	int	sated;

	pthread_mutex_lock(philo->finish_lock);
	finish = *philo->finish;
	pthread_mutex_unlock(philo->finish_lock);
	if (finish)
		return (1);
	pthread_mutex_lock(&philo->sated_lock);
	sated = philo->sated;
	pthread_mutex_unlock(&philo->sated_lock);
	if (sated)
		return (1);
	return (0);
}

void	*cycle(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->args.philo_n == 1)
	{
		perform_action(philo, FORK);
		usleep(philo->args.die_t * 1000);
		return (NULL);
	}
	while (!is_meal_over(philo))
		cycle_execute(philo);
	return (NULL);
}
