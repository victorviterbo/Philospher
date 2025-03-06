/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:19:47 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/06 10:12:15 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		gettime(t_philo *philo);
int		monitored_sleep(t_philo *philo, t_philostate state);
void	philo_start(t_philo *philo);

int	gettime(t_philo *philo)
{
	struct timeval	tv;
	int				time;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	if (philo->shared->start_time == 0)
	{
		if (philo->id != 1)
			return (-1);
		philo->shared->start_time = (int)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
		philo->shared->start_time += 2000;
		return (-1);
	}
	time = (int)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (time - philo->shared->start_time);
}

int	monitored_sleep(t_philo *philo, t_philostate state)
{
	if (philo->terminate)
		return (-1);
	if (state == EATING)
	{
		if (gettime(philo) + philo->param[TIME_TO_EAT] < philo->time_death)
			return (usleep(1000 * philo->param[TIME_TO_EAT]));
		else if (philo->time_death - gettime(philo) > 0)
		{
			philo->state = DEAD;
			return (usleep(philo->time_death - gettime(philo)));
		}
	}
	else if (state == SLEEPING)
	{
		if (gettime(philo) + philo->param[TIME_TO_SLEEP] < philo->time_death)
			return (usleep(1000 * philo->param[TIME_TO_SLEEP]));
		else if (philo->time_death - gettime(philo) > 0)
		{
			philo->state = DEAD;
			return (usleep(philo->time_death - gettime(philo)));
		}
	}
	else if (state == THINKING)
		return (usleep(1000 * (1 + 2 * philo->param[TIME_TO_EAT] - philo->param[TIME_TO_SLEEP])));
	return (1);
}

void	philo_start(t_philo *philo)
{
	if (philo->id == 1)
		if (gettime(philo) != -1)
			return ;
	while (gettime(philo) < 0)
		usleep(100);
	philo->time_death = gettime(philo) + philo->param[TIME_TO_DIE];
	if (philo->id % 2 == 0)
		usleep(500);
	else if (philo->param[NUM_OF_PHILO] % 2
		&& philo->id == philo->param[NUM_OF_PHILO])
	{
		usleep(500);
		monitored_sleep(philo, EATING);
	}
}
