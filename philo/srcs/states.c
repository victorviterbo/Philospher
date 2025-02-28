/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:51:54 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/28 13:09:44 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life(void *param);
void	distribute_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);

void	*life(void *param)
{
	t_philo	*philo;

	philo = param;
	if (philo->id == 0)
	{
		distribute_forks(philo);
		return (NULL);
	}
	philo->time_death = gettime() + philo->param[TIME_TO_DIE];
	while (gettime() < philo->time_death)
	{
		philo_eat(philo);
		if (philo->param[NUM_MEALS] && philo->meals == philo->param[NUM_MEALS])
		{
			philo->state = FED;
			return (NULL);
		}
		if (philo->state == DEAD)
			return (NULL);
		philo_sleep(philo);
	}
	philo->state = DEAD;
	safe_print(philo);
	return (NULL);
}

void	distribute_forks(t_philo *philo)
{
	int	i;
	int	offset;

	i = 0;
	offset = 0;
	if (philo->param[NUM_OF_PHILO] < 2)
		return ;
	while (true)
	{
		while (philo->forks->flist[(i + offset)]
			|| philo->forks->flist[(i + 1 + offset) % philo->param[NUM_OF_PHILO]])
		{
		}
		pthread_mutex_lock(&philo->forks->lock);
		philo->forks->flist[i + offset] = i + 1 + offset;
		philo->forks->flist[(i + 1 + offset)
			% philo->param[NUM_OF_PHILO]] = i + 1 + offset;
		pthread_mutex_unlock(&philo->forks->lock);
		i = (i + 2) % philo->param[NUM_OF_PHILO];
		if (i == 0)
			offset = (philo->param[NUM_OF_PHILO] % 2 == 0) * (offset == 0);
		if (philo->state == TERMINATE)
			return ;
	}
}

void	philo_eat(t_philo *philo)
{
	int		fleft;
	int		fright;

	fleft = (philo->id - 1) ;
	fright = (philo->id) % philo->param[NUM_OF_PHILO];
	while (philo->state != EATING && gettime() < philo->time_death)
	{
		if (philo->forks->flist[fleft] == philo->id
			&& philo->forks->flist[fright] == philo->id)
			philo->state = EATING;
	}
	if (gettime() >= philo->time_death)
	{
		philo->state = DEAD;
		safe_print(philo);
		return ;
	}
	safe_print(philo);
	philo->time_death = gettime() + philo->param[TIME_TO_DIE];
	usleep(1000 * philo->param[TIME_TO_EAT]);
	pthread_mutex_lock(&philo->forks->lock);
	philo->forks->flist[fleft] = 0;
	philo->forks->flist[fright] = 0;
	pthread_mutex_unlock(&philo->forks->lock);
	philo->meals++;
	return ;
}

void	philo_sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	safe_print(philo);
	usleep(1000 * philo->param[TIME_TO_SLEEP]);
	philo->state = THINKING;
	safe_print(philo);
	return ;
}
