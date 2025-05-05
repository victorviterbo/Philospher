/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:53:02 by vviterbo          #+#    #+#             */
/*   Updated: 2025/05/05 17:58:39 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_start(t_philo *philo);
int		init_clock(t_philo *philo);

void	philo_start(t_philo *philo)
{
	init_clock(philo);
	while (gettime(philo) < 0)
		usleep(100);
	reset_tod(philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	else if (philo->param[NUM_OF_PHILO] % 2
		&& philo->id == philo->param[NUM_OF_PHILO]
		&& philo->param[NUM_OF_PHILO] > 1)
	{
		usleep(500);
		monitored_sleep(philo, EATING);
	}
}

int	init_clock(t_philo *philo)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	if (philo->id != 1 && get_start_time(philo) == 0)
		return (-1);
	else if (philo->id != 1)
		return (0);
	set_start_time(philo, (long)(tv.tv_sec * 1000 + tv.tv_usec / 1000) + 1000);
	return (0);
}
