/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:09:26 by anayef            #+#    #+#             */
/*   Updated: 2023/11/26 11:06:37 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*fill_args(int argc, char **args)
{
	t_args	*data;

	data = malloc(sizeof(t_args));
	data->t0 = get_time();
	data->philo_n = ft_atoi(args[1]);
	data->die_t = ft_atoi(args[2]);
	data->eat_t = ft_atoi(args[3]);
	data->sleep_t = ft_atoi(args[4]);
	data->meals_n = -1;
	if (argc == 6)
		data->meals_n = ft_atoi(args[5]);
	return (data);
}

static void	fill_philo_args(t_philo *philo, t_table *table)
{
	philo->args.t0 = table->args->t0;
	philo->args.meals_n = table->args->meals_n;
	philo->args.sleep_t = table->args->sleep_t;
	philo->args.die_t = table->args->die_t;
	philo->args.eat_t = table->args->eat_t;
	philo->args.philo_n = table->args->philo_n;
}

static int	populate_philo(t_table *table, int i)
{
	table->philos[i] = malloc(sizeof(t_philo));
	if (!table->philos[i])
		return (0);
	table->philos[i]->id = i + 1;
	table->philos[i]->meal_count = 0;
	table->philos[i]->time_to_die = 0;
	table->philos[i]->last_meal_t = get_time();
	table->philos[i]->sated = 0;
	table->philos[i]->finish = &table->finish;
	table->philos[i]->finish_lock = &table->finish_lock;
	table->philos[i]->write_lock = &table->write_lock;
	fill_philo_args(table->philos[i], table);
	pthread_mutex_init(&table->philos[i]->sated_lock, NULL);
	pthread_mutex_init(&table->philos[i]->last_meal_lock, NULL);
	table->philos[i]->fork[LEFT] = &table->forks[i];
	table->philos[i]->fork[RIGHT] = &table->forks[(i + 1) % \
		table->args->philo_n];
	return (1);
}

int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * (table->args->philo_n));
	if (!table->philos)
		return (0);
	i = -1;
	while (++i < table->args->philo_n)
		populate_philo(table, i);
	return (1);
}

int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->args->philo_n);
	if (!table->forks)
		return (0);
	i = -1;
	while (++i < table->args->philo_n)
		pthread_mutex_init(&table->forks[i], NULL);
	return (1);
}
