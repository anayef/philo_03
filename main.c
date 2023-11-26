/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:32:32 by anayef            #+#    #+#             */
/*   Updated: 2023/11/26 01:33:37 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*set_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	table->args = fill_args(argc, argv);
	if (init_forks(table) == 0)
		err_hndl("Error Setting Forks.\n", table);
	if (init_philos(table) == 0)
		err_hndl("Error Setting Philosophers.\n", table);
	table->finish = 0;
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->finish_lock, NULL);
	return (table);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		input_status;

	if (argc < 2)
	{
		printf("Invalid Arguments.\n");
		return (1);
	}
	input_status = correct_input(argc, argv);
	if (input_status != 0)
	{
		handle_error_msg(input_status);
		return (1);
	}
	table = set_table(argc, argv);
	if (!table)
		return (1);
	if (thread_create(table) == 0 || table_destroy(table) == 0)
		return (1);
	free_table(table);
	return (0);
}
