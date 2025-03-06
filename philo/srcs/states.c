/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:51:54 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/06 10:00:47 by vviterbo         ###   ########.fr       */
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
	if (philo->id == 1)
		if (gettime(philo) != -1)
			return (NULL);
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
	if (philo->state == DEAD)
		return (NULL);
	while (philo->state != FED && philo->state != DEAD && !philo->terminate)
	{
		philo_eat(philo);
		if (philo->state == FED || philo->state == DEAD || philo->terminate)
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
	while ((philo->shared->forks[philo->id - 1]
			|| philo->shared->forks[next])
		&& gettime(philo) <= philo->time_death)
		usleep(50);
	if (philo->time_death < gettime(philo))
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
	if (philo->state == DEAD)
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
	if (philo->state == DEAD)
		return ;
	philo->state = THINKING;
	safe_print(philo);
	if (philo->param[NUM_OF_PHILO] % 2)
		monitored_sleep(philo, THINKING);
	if (philo->time_death < gettime(philo))
		philo->state = DEAD;
	return ;
}
