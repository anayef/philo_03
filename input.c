/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:28:59 by anayef            #+#    #+#             */
/*   Updated: 2023/11/26 09:04:26 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_ifnum(char **argv)
{
	int	i;
	int	j;

	j = 1;
	while (argv[j])
	{
		i = 0;
		if (argv[j][i] == '\0')
			return (0);
		if (ft_issign(argv[j][i]))
			i++;
		while (argv[j][i] && ft_isdigit(argv[j][i]))
			i++;
		if (argv[j][i] != '\0' && !ft_isdigit(argv[j][i]))
			return (0);
		j++;
	}
	return (1);
}

int	philo_check(char **argv)
{
	int	num_philo;

	if (!argv[1])
		return (0);
	num_philo = ft_atoi(argv[1]);
	if (num_philo < 1)
		return (0);
	return (1);
}

int	time_check(char **argv)
{
	int	i;

	i = 2;
	while (i < 5)
	{
		if (!argv[i] || ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	correct_input(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (!check_ifnum(argv))
		return (2);
	if (!philo_check(argv))
		return (3);
	if (!time_check(argv))
		return (4);
	return (0);
}

int	handle_error_msg(int error_code)
{
	if (error_code == 1)
		printf("Invalid number of arguments.\n");
	else if (error_code == 2)
		printf("Arguments are not in the correct format.\n");
	else if (error_code == 3)
		printf("Invalid number of philosophers.\n");
	else if (error_code == 4)
		printf("Timestamp can't be a negative value or null.\n");
	else
		printf("error\n");
	return (error_code);
}
