/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:19:47 by vviterbo          #+#    #+#             */
/*   Updated: 2025/05/05 18:00:15 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		gettime(t_philo *philo);
int		monitored_sleep(t_philo *philo, t_philostate state);

int	gettime(t_philo *philo)
{
	struct timeval	tv;
	long			time;
	long			start_time;

	start_time = get_start_time(philo);
	if (start_time == 0)
		return (-1);
	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	time = (int)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return ((int)(time - get_start_time(philo)));
}

long	get_start_time(t_philo *philo)
{
	long	start_time;

	pthread_mutex_lock(&philo->shared->start_time_lock);
	start_time = philo->shared->start_time;
	pthread_mutex_unlock(&philo->shared->start_time_lock);
	return (start_time);
}

void	set_start_time(t_philo *philo, long start_time)
{
	pthread_mutex_lock(&philo->shared->start_time_lock);
	philo->shared->start_time = start_time;
	pthread_mutex_unlock(&philo->shared->start_time_lock);
	return ;
}

int	monitored_sleep(t_philo *philo, t_philostate state)
{
	if (get_terminate_status(philo))
		return (-1);
	if (state == EATING)
	{
		if (gettime(philo) + philo->param[TIME_TO_EAT] < get_tod(philo))
			return (usleep(1000 * philo->param[TIME_TO_EAT]));
		else if (get_tod(philo) - gettime(philo) > 0)
		{
			usleep(1000 * (get_tod(philo) - gettime(philo)));
			return (set_state(philo, DEAD));
		}
	}
	else if (state == SLEEPING)
	{
		if (gettime(philo) + philo->param[TIME_TO_SLEEP] < get_tod(philo))
			return (usleep(1000 * philo->param[TIME_TO_SLEEP]));
		else if (get_tod(philo) - gettime(philo) > 0)
		{
			usleep(1000 * (get_tod(philo) - gettime(philo)));
			return (set_state(philo, DEAD));
		}
	}
	else if (state == THINKING)
		return (usleep(500 * (get_tod(philo) - gettime(philo))));
	return (1);
}
