/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:36:02 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/23 11:54:28 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int		*args;
	int		*philo;
	int		*forks;
	size_t	i;

	args = parse_args(argc, argv);
	if (!args)
		return (1);
		write(2, "ERROR: Wrong number of arguments, exiting...\n", 46);
	i = 0;
	while (argv[i])
	philo = ft_calloc()
}

int	*parse_args(int argc, char *argv[])
{
	int		*args;
	size_t	i;

	if (argc != 5 && argc != 6)
	{
		write(2, "ERROR: Wrong number of arguments, exiting...\n", 46);
		return (NULL);
	}
	args = ft_calloc(argc, sizeof(int));
	if (!args)
	i = 0;
	while (i < argc)
	{
		if (!ft_isint(argv[i]))
		{
			write(2, "ERROR: Arguments should be int, exiting...\n", 46);
			return (NULL);
		}
		args[i] = ft_atoi(argv[i]);
	}
}