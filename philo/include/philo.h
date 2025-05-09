/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:36:18 by vviterbo          #+#    #+#             */
/*   Updated: 2025/05/05 17:42:40 by vviterbo         ###   ########.fr       */
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
	pthread_mutex_t	state_lock;
	long			time_death;
	pthread_mutex_t	time_death_lock;
	struct s_shared	*shared;
	int				*param;
	int				meals;
}	t_philo;

typedef struct s_shared
{
	int				*forks;
	pthread_mutex_t	*lock;
	pthread_mutex_t	print_lock;
	long			start_time;
	pthread_mutex_t	start_time_lock;
	bool			terminate;
	pthread_mutex_t	terminate_lock;
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

//philo
int		*parse_args(int argc, char *argv[]);
int		spawn_threads(t_philo **philo);
t_philo	**init_philo(int *args);

//start_simu
void	philo_start(t_philo *philo);
int		init_clock(t_philo *philo);

//run_simu
void	*life(void *param);
void	philo_get_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);

//end_simu
int		checkphilo(t_philo **philo);
void	philo_finish(t_philo **philo, pthread_t *threads);
void	join_free_destroy(t_philo **philo, pthread_t *threads,
			int num_of_philo);
void	free_philos(t_philo **philo, pthread_t *threads, int num_of_philo);

//time_utils
int		gettime(t_philo *philo);
void	set_start_time(t_philo *philo, long start_time);
long	get_start_time(t_philo *philo);
int		monitored_sleep(t_philo *philo, t_philostate state);
//state_utils
int		set_state(t_philo *philo, int state);
int		get_state(t_philo *philo);
long	get_tod(t_philo *philo);
void	reset_tod(t_philo *philo);

//mutex_utils
void	safe_print(t_philo *philo, char *message);
bool	forks_avail(t_philo *philo);
void	change_fork(t_philo *philo, int i, int newval);
bool	get_terminate_status(t_philo *philo);
void	set_terminate_status(t_philo *philo, bool new_value);

#endif