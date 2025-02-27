/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:36:18 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/27 17:19:54 by vviterbo         ###   ########.fr       */
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
	FORK,
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
	struct s_forks	*forks;
	pthread_mutex_t	lock;
	int				*param;
	int				meals;
	pthread_t		thread;
}	t_philo;


typedef struct s_forks
{
	bool			*forklist;
	pthread_mutex_t	lock;
}	t_forks;

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
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);

int		checkphilo(t_philo **philo);
int		gettime(void);
void	safe_print(t_philo *philo);

#endif