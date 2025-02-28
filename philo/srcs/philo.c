/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:36:02 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/28 12:48:26 by vviterbo         ###   ########.fr       */
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
	args = ft_calloc(6, sizeof(int));
	if (!args)
	{
		write(2, "ERROR: memory allocation failed, exiting...\n", 45);
		return (NULL);
	}
	argc = 1;
	while (argv[argc])
	{
		if (!ft_isint(argv[argc]) && ft_atoi(argv[argc]) <= 0)
		{
			write(2, "ERROR: Arguments should be int, exiting...\n", 44);
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

	threads = ft_calloc(philo[0]->param[NUM_OF_PHILO] + 1, sizeof(pthread_t));
	if (!threads)
	{
		printf("ERROR: memory allocation failed, exiting...\n");
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&philo[0]->forks->lock, NULL) != 0)
	{
		printf("ERROR: mutex init failed, exiting...\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < philo[0]->param[NUM_OF_PHILO] + 1)
	{
		if (pthread_create(&threads[i], NULL, &life, (void *)philo[i]) != 0)
		{
			printf("ERROR: could not create thread %i\n", i);
			return (EXIT_FAILURE);
		}
		if (pthread_detach(threads[i]) != 0)
		{
			printf("ERROR: could not detach thread %i\n", i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	while (!checkphilo(philo))
	{
	}
	philo[0]->state = TERMINATE;
	if (checkphilo(philo) == FED)
		printf("philo exited with all philos alive :)\n");
	else if (checkphilo(philo) == DEAD)
		printf("philo exited with at least one death :(\n");
	return (0);
}

t_philo	**init_philo(int *args)
{
	int		i;
	t_philo	**philo;

	i = 0;
	philo = ft_calloc(args[NUM_OF_PHILO] + 1, sizeof(t_philo *));
	if (!philo)
		return (NULL);
	while (i < args[NUM_OF_PHILO] + 1)
	{
		philo[i] = ft_calloc(1, sizeof(t_philo));
		if (!philo[i])
			return (ft_free_array((void **)philo, i), NULL);
		philo[i]->param = args;
		philo[i]->id = i;
		i++;
	}
	return (philo);
}

void	*init_forks(t_philo **philo)
{
	int				i;
	t_forks			*forks;
	pthread_mutex_t print_lock;

	i = 0;
	forks = ft_calloc(1, sizeof(t_forks));
	if (!forks)
		return (free(philo), NULL);
	forks->flist = ft_calloc(philo[0]->param[NUM_OF_PHILO], sizeof(int));
	if (!forks->flist)
		return (free(forks), free(philo), NULL);
	while (i < philo[0]->param[NUM_OF_PHILO])
	{
		forks->flist[i] = 0;
		i++;
	}
	i = 0;
	pthread_mutex_init(&print_lock, NULL);
	while (i < philo[0]->param[NUM_OF_PHILO] + 1)
	{
		philo[i]->forks = forks;
		philo[i]->print_lock = print_lock;
		i++;
	}
	return (NULL);
}
