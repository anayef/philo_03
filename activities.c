/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:20:16 by anayef            #+#    #+#             */
/*   Updated: 2023/11/26 10:36:57 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_philo(t_philo *philo)
{
	if (grab_two_forks(philo) == 0)
		return (0);
	perform_action(philo, EAT);
	pthread_mutex_lock(&philo->sated_lock);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->sated_lock);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal_t = get_time();
	pthread_mutex_unlock(&philo->last_meal_lock);
	pass_a_time(philo->args.eat_t);
	if (drop_forks(philo) == 0)
		return (0);
	return (1);
}

int	thinking_philo(t_philo *philo)
{
	int	finish;

	pthread_mutex_lock(philo->finish_lock);
	finish = *philo->finish;
	pthread_mutex_unlock(philo->finish_lock);
	if (finish)
		return (0);
	if (perform_action(philo, THINK) == 0)
		return (0);
	return (1);
}

int	sleeping_philo(t_philo *philo)
{
	int	finish;

	pthread_mutex_lock(philo->finish_lock);
	finish = *philo->finish;
	pthread_mutex_unlock(philo->finish_lock);
	if (finish)
		return (0);
	if (perform_action(philo, SLEEP) == 0)
		return (0);
	pass_a_time(philo->args.sleep_t);
	return (1);
}

int	dead_philo(t_table *table)
{
	int		i;
	long	since_last_meal_t;

	i = -1;
	while (++i < table->args->philo_n)
	{
		pthread_mutex_lock(&table->philos[i]->last_meal_lock);
		since_last_meal_t = time_diff(table->philos[i]->last_meal_t);
		pthread_mutex_unlock(&table->philos[i]->last_meal_lock);
		if (since_last_meal_t >= table->args->die_t)
		{
			pthread_mutex_lock(&table->finish_lock);
			table->finish = 1;
			pthread_mutex_unlock(&table->finish_lock);
			perform_action(table->philos[i], DIED);
			return (1);
		}
	}
	return (0);
}

int	perform_action(t_philo *philo, char *status)
{
	long	now_t;

	pthread_mutex_lock(philo->write_lock);
	now_t = time_diff(philo->args.t0);
	printf("%ld %d %s\n", now_t, philo->id, status);
	pthread_mutex_unlock(philo->write_lock);
	return (1);
}
