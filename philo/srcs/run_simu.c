/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:54:54 by vviterbo          #+#    #+#             */
/*   Updated: 2025/05/05 17:40:36 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life(void *param);
void	philo_get_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);

void	*life(void *param)
{
	t_philo	*philo;

	philo = param;
	philo_start(philo);
	if (get_state(philo) == DEAD)
	{
		safe_print(philo, NULL);
		return (NULL);
	}
	while (get_state(philo) != FED && get_state(philo) != DEAD
		&& !get_terminate_status(philo))
	{
		philo_eat(philo);
		if (get_state(philo) == FED || get_state(philo) == DEAD
			|| get_terminate_status(philo))
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}

void	philo_get_forks(t_philo *philo)
{
	int	next;

	next = philo->id % (philo->param[NUM_OF_PHILO]);
	if (next == philo->id - 1)
	{
		usleep(1000 * (get_tod(philo) - gettime(philo)));
		set_state(philo, DEAD);
		return ;
	}
	while (!forks_avail(philo) && gettime(philo) <= get_tod(philo))
		usleep(50);
	if (get_terminate_status(philo) || get_tod(philo) < gettime(philo))
	{
		set_state(philo, DEAD);
		return ;
	}
	change_fork(philo, philo->id - 1, philo->id);
	set_state(philo, HAS_FORK);
	safe_print(philo, NULL);
}

void	philo_eat(t_philo *philo)
{
	philo_get_forks(philo);
	if (get_state(philo) == DEAD || get_terminate_status(philo))
		return ;
	set_state(philo, EATING);
	safe_print(philo, NULL);
	reset_tod(philo);
	monitored_sleep(philo, EATING);
	change_fork(philo, philo->id - 1, 0);
	if (get_state(philo) == DEAD || get_terminate_status(philo))
		return ;
	philo->meals++;
	if (philo->param[NUM_MEALS] && philo->meals == philo->param[NUM_MEALS])
		set_state(philo, FED);
	return ;
}

void	philo_sleep(t_philo *philo)
{
	set_state(philo, SLEEPING);
	safe_print(philo, NULL);
	monitored_sleep(philo, SLEEPING);
	if (get_state(philo) == DEAD || get_terminate_status(philo))
		return ;
	set_state(philo, THINKING);
	safe_print(philo, NULL);
	if (philo->param[NUM_OF_PHILO] % 2)
		monitored_sleep(philo, THINKING);
	return ;
}
