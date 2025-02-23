/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:36:02 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/23 16:28:56 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*parse_args(int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	int		*args;
	//int		*philo;
	//int		*forks;

	args = parse_args(argc, argv);
	if (!args)
		return (EXIT_FAILURE);
	return (args[0]);
}

int	*parse_args(int argc, char *argv[])
{
	int	*args;
	int	i;

	if (argc != 5 && argc != 6)
	{
		write(2, "ERROR: Wrong number of arguments, exiting...\n", 46);
		return (NULL);
	}
	args = ft_calloc(argc, sizeof(int));
	if (!args)
	{
		write(2, "ERROR: memory allocation failed, exiting...\n", 45);
		return (NULL);
	}
	i = 1;
	while (i < argc)
	{
		if (!ft_isint(argv[i]))
		{
			write(2, "ERROR: Arguments should be int, exiting...\n", 44);
			return (NULL);
		}
		args[i] = ft_atoi(argv[i]);
		i++;
	}
	return (args);
}
