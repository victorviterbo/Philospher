/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:51:54 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/29 16:47:06 by vviterbo         ###   ########.fr       */
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
	philo_start(philo);
	if (philo->state == DEAD)
	{
		safe_print(philo);
		return (NULL);
	}
	while (philo->state != FED && philo->state != DEAD && !get_terminate_status(philo))
	{
		philo_eat(philo);
		if (philo->state == FED || philo->state == DEAD || get_terminate_status(philo))
			break ;
		philo_sleep(philo);
	}
	if (philo->state == DEAD)
		safe_print(philo);
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	int	next;

	next = philo->id % (philo->param[NUM_OF_PHILO]);
	if (next == philo->id - 1)
	{
		usleep(1000 * (philo->time_death - gettime(philo)));
		philo->state = DEAD;
		return ;
	}
	while (!forks_avail(philo) && gettime(philo) <= philo->time_death)
		usleep(50);
	if (get_terminate_status(philo) || philo->time_death < gettime(philo))
	{
		philo->state = DEAD;
		return ;
	}
	change_fork(philo, philo->id - 1, philo->id);
	philo->state = HAS_FORK;
	safe_print(philo);
	philo->state = EATING;
	safe_print(philo);
	philo->time_death = gettime(philo) + philo->param[TIME_TO_DIE];
	monitored_sleep(philo, EATING);
	change_fork(philo, philo->id - 1, 0);
	if (philo->state == DEAD || get_terminate_status(philo))
		return ;
	philo->meals++;
	if (philo->param[NUM_MEALS] && philo->meals == philo->param[NUM_MEALS])
		philo->state = FED;
	return ;
}

void	philo_sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	safe_print(philo);
	monitored_sleep(philo, SLEEPING);
	if (philo->state == DEAD || get_terminate_status(philo))
		return ;
	philo->state = THINKING;
	safe_print(philo);
	if (philo->param[NUM_OF_PHILO] % 2)
		monitored_sleep(philo, THINKING);
	return ;
}
