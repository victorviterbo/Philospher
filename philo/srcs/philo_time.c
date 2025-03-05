/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:19:47 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/05 12:17:23 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	gettime(void);
int	monitored_sleep(t_philo *philo);

int	gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((int)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

int	monitored_sleep(t_philo *philo)
{
	if (philo->state == EATING)
	{
		if (gettime() + philo->param[TIME_TO_EAT] < philo->time_death)
			return (usleep(1000 * philo->param[TIME_TO_EAT]));
		else
		{
			pthread_mutex_lock(&philo->state_lock);
			philo->state = DEAD;
			pthread_mutex_unlock(&philo->state_lock);
			return (usleep(1000 * philo->param[TIME_TO_EAT]));
		}
	}
	if (philo->state == SLEEPING)
	{
		if (gettime() + philo->param[TIME_TO_SLEEP] < philo->time_death)
			return (usleep(1000 * philo->param[TIME_TO_SLEEP]));
		else
		{
			pthread_mutex_lock(&philo->state_lock);
			philo->state = DEAD;
			pthread_mutex_unlock(&philo->state_lock);
			return (usleep(1000 * philo->param[TIME_TO_SLEEP]));
		}
	}
	return (1);
}
