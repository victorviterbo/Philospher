/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:36:02 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/29 16:31:03 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		*parse_args(int argc, char *argv[]);
int		spawn_threads(t_philo **philo);
t_philo	**init_philo(int *args);
void	*init_forks(t_philo **philo);

int	main(int argc, char *argv[])
{
	int			*param;
	t_philo		**philo;

	param = parse_args(argc, argv);
	if (!param)
		return (EXIT_FAILURE);
	philo = init_philo(param);
	init_forks(philo);
	if (!philo)
		return (free(param), EXIT_FAILURE);
	spawn_threads(philo);
	return (0);
}

int	*parse_args(int argc, char *argv[])
{
	int	*args;

	if (argc != 5 && argc != 6)
	{
		write(2, "ERROR: Wrong number of arguments, exiting...\n", 46);
		return (NULL);
	}
	args = ft_calloc(5, sizeof(int));
	if (!args)
	{
		write(2, "ERROR: memory allocation failed, exiting...\n", 45);
		return (NULL);
	}
	argc = 1;
	while (argv[argc])
	{
		if (!ft_isint(argv[argc]) || ft_atoi(argv[argc]) <= 0)
		{
			write(2, "ERROR: Wrong argument, exiting...\n", 35);
			return (NULL);
		}
		args[argc - 1] = ft_atoi(argv[argc]);
		argc++;
	}
	return (args);
}

int	spawn_threads(t_philo **philo)
{
	pthread_t		*threads;
	int				i;

	threads = ft_calloc(philo[0]->param[NUM_OF_PHILO], sizeof(pthread_t));
	if (!threads)
	{
		printf("ERROR: memory alloc failed, exiting...\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < philo[0]->param[NUM_OF_PHILO])
	{
		if (pthread_create(&threads[i], NULL, &life, (void *)philo[i]) != 0)
		{
			printf("ERROR: could not create thread %i\n", i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	philo_finish(philo, threads);
	return (0);
}

t_philo	**init_philo(int *args)
{
	int		i;
	t_philo	**philo;

	i = 0;
	philo = ft_calloc(args[NUM_OF_PHILO], sizeof(t_philo *));
	if (!philo)
		return (NULL);
	while (i < args[NUM_OF_PHILO])
	{
		philo[i] = ft_calloc(1, sizeof(t_philo));
		if (!philo[i])
			return (ft_free_array((void **)philo, i), NULL);
		philo[i]->param = args;
		philo[i]->id = i + 1;
		i++;
	}
	return (philo);
}

void	*init_forks(t_philo **philo)
{
	int			i;
	t_shared	*shared;

	i = 0;
	shared = ft_calloc(1, sizeof(t_shared));
	if (!shared)
		return (free(philo), NULL);
	shared->forks = ft_calloc(philo[0]->param[NUM_OF_PHILO], sizeof(int));
	if (!shared->forks)
		return (free(shared), free(philo), NULL);
	shared->terminate = false;
	i = 0;
	pthread_mutex_init(&shared->terminate_lock, NULL);
	pthread_mutex_init(&shared->print_lock, NULL);
	shared->lock = ft_calloc(philo[0]->param[NUM_OF_PHILO],
			sizeof(pthread_mutex_t));
	shared->start_time = 0;
	while (i < philo[0]->param[NUM_OF_PHILO])
	{
		philo[i]->shared = shared;
		pthread_mutex_init(&shared->lock[i], NULL);
		i++;
	}
	return (NULL);
}
