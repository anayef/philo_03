/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:31:41 by anayef            #+#    #+#             */
/*   Updated: 2023/11/26 10:36:48 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	grab_a_fork(t_philo *philo, int loc)
{
	int	finish;

	pthread_mutex_lock(philo->fork[loc]);
	pthread_mutex_lock(philo->finish_lock);
	finish = *philo->finish;
	pthread_mutex_unlock(philo->finish_lock);
	if (finish)
	{
		pthread_mutex_unlock(philo->fork[loc]);
		return (0);
	}
	if (perform_action(philo, FORK) == 0)
		return (0);
	return (1);
}

int	grab_two_forks(t_philo *philo)
{
	int	first;
	int	second;

	if (philo->id % 2 == 0)
	{
		first = RIGHT;
		second = LEFT;
	}
	else
	{
		first = LEFT;
		second = RIGHT;
	}
	if (!grab_a_fork(philo, first))
		return (0);
	if (!grab_a_fork(philo, second))
	{
		pthread_mutex_unlock(philo->fork[first]);
		return (0);
	}
	return (1);
}

int	drop_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->fork[LEFT]))
		return (0);
	if (pthread_mutex_unlock(philo->fork[RIGHT]))
		return (0);
	if (philo->meal_count == philo->args.meals_n)
	{
		pthread_mutex_lock(&philo->sated_lock);
		philo->sated = 1;
		pthread_mutex_unlock(&philo->sated_lock);
	}
	return (1);
}
