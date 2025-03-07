/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:36:18 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/06 10:03:31 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef enum e_philostate
{
	THINKING,
	SLEEPING,
	EATING,
	HAS_FORK,
	DEAD,
	FED
}	t_philostate;

typedef enum e_arguments
{
	NUM_OF_PHILO,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUM_MEALS
}	t_arguments;

typedef struct s_philo
{
	int				id;
	int				state;
	int				time_death;
	bool			terminate;
	struct s_shared	*shared;
	int				*param;
	int				meals;
	struct s_philo	**philos;
}	t_philo;

typedef struct s_shared
{
	int				*forks;
	pthread_mutex_t	*lock;
	pthread_mutex_t	print_lock;
	int				start_time;
}	t_shared;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		ft_isint(char *str);
char	*ft_itoa(int n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *str);
double	ft_prev_power(double n, int base_size);
int		ft_number_len(long long n, int base_size);
int		ft_iswhitespace_eq(int c);
char	*ft_strchr(const char *s, int c);
void	ft_free_array(void **array, int size);
size_t	ft_arrlen(char **array);

int		*parse_args(int argc, char *argv[]);
int		spawn_threads(t_philo **philo);
t_philo	**init_philo(int *args);

void	*life(void *param);
void	distribute_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);

int		checkphilo(t_philo **philo);
void	safe_print(t_philo *philo);
void	philo_finish(t_philo **philo, pthread_t *threads);
void	free_n_destroy(t_philo **philo, int num_of_philo);
void	change_fork(t_philo *philo, int i, int newval);

int		gettime(t_philo *philo);
int		monitored_sleep(t_philo *philo, t_philostate state);
void	philo_start(t_philo *philo);

#endif