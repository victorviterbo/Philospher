/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:19:47 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/29 16:42:04 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		gettime(t_philo *philo);
int		init_clock(t_philo *philo);
int		monitored_sleep(t_philo *philo, t_philostate state);
void	philo_start(t_philo *philo);

int	gettime(t_philo *philo)
{
	struct timeval	tv;
	long			time;

	if (philo->shared->start_time == 0)
		return (-1);
	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	time = (int)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return ((int)(time - philo->shared->start_time));
}

int	init_clock(t_philo *philo)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	if (philo->id != 1 && philo->shared->start_time == 0)
		return (-1);
	else if (philo->id != 1)
		return (0);
	philo->shared->start_time = (long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	philo->shared->start_time += 2000;
	return (0);
}

int	monitored_sleep(t_philo *philo, t_philostate state)
{
	if (get_terminate_status(philo))
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
		return (usleep(500 * (philo->time_death - gettime(philo))));
	return (1);
}

void	philo_start(t_philo *philo)
{
	init_clock(philo);
	while (gettime(philo) < 0)
		usleep(100);
	philo->time_death = gettime(philo) + philo->param[TIME_TO_DIE];
	if (philo->id % 2 == 0)
		usleep(500);
	else if (philo->param[NUM_OF_PHILO] % 2
		&& philo->id == philo->param[NUM_OF_PHILO]
		&& philo->param[NUM_OF_PHILO] > 1)
	{
		usleep(500);
		monitored_sleep(philo, EATING);
	}
}
