/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:27:41 by anayef            #+#    #+#             */
/*   Updated: 2023/11/26 01:31:38 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_err(char *err)
{
	printf("%s", err);
	return (1);
}

void	free_table(t_table *table)
{
	if (table->args != NULL)
		free(table->args);
	if (table->philos != NULL)
		free(table->philos);
	if (table->forks != NULL)
		free(table->forks);
	free(table);
}

void	err_hndl(char *err, t_table *table)
{
	free_table(table);
	printf("%s", err);
}
