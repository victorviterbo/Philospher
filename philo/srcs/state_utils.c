/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:16:18 by vviterbo          #+#    #+#             */
/*   Updated: 2025/05/05 17:46:22 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		set_state(t_philo *philo, int state);
int		get_state(t_philo *philo);
void	set_tod(t_philo *philo, int state);
long	get_tod(t_philo *philo);

int	get_state(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&philo->state_lock);
	state = philo->state;
	pthread_mutex_unlock(&philo->state_lock);
	return (state);
}

int	set_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->state_lock);
	philo->state = state;
	pthread_mutex_unlock(&philo->state_lock);
	return (state);
}

void	reset_tod(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_death_lock);
	philo->time_death = (long)gettime(philo) + philo->param[TIME_TO_DIE];
	pthread_mutex_unlock(&philo->time_death_lock);
}

long	get_tod(t_philo *philo)
{
	long	tod;

	pthread_mutex_lock(&philo->time_death_lock);
	tod = philo->time_death;
	pthread_mutex_unlock(&philo->time_death_lock);
	return (tod);
}
