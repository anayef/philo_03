/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:12:38 by anayef            #+#    #+#             */
/*   Updated: 2023/11/26 01:31:38 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIED "died"

typedef struct s_args
{
	long	t0;
	int		philo_n;
	long	die_t;
	long	eat_t;
	long	sleep_t;
	int		meals_n;
}	t_args;

enum e_fork
{
	RIGHT,
	LEFT,
};

typedef struct s_philo
{
	int				id;
	int				meal_count;
	long			time_to_die;
	long			last_meal_t;
	int				sated;
	int				*finish;
	t_args			args;
	pthread_t		thread_id;
	pthread_mutex_t	*finish_lock;
	pthread_mutex_t	sated_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*fork[2];
}	t_philo;

typedef struct s_table
{
	int				finish;
	t_args			*args;
	t_philo			**philos;
	pthread_t		reaper;
	pthread_mutex_t	finish_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
}	t_table;

int		correct_input(int argc, char **argv);
int		ft_isdigit(char c);
int		ft_issign(char c);
int		ft_atoi(const char *str);
t_args	*fill_args(int argc, char **argv);
int		init_philos(t_table *table);
int		init_forks(t_table *table);
long	get_time(void);
long	time_diff(long time);
void	pass_a_time(long time);
int		drop_forks(t_philo *philo);
int		grab_two_forks(t_philo *philo);
int		eating_philo(t_philo *philo);
int		thinking_philo(t_philo *philo);
int		sleeping_philo(t_philo *philo);
int		dead_philo(t_table *table);
int		thread_create(t_table *table);
int		table_destroy(t_table *table);
void	*cycle(void *args);
void	*reap(void *table_ptr);
int		perform_action(t_philo *philo, char *status);
int		exit_err(char *err);
void	err_hndl(char *err, t_table *table);
int		handle_error_msg(int error_code);
void	free_table(t_table *table);

#endif
