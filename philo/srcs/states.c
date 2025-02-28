/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:51:54 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/28 19:34:35 by vviterbo         ###   ########.fr       */
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
	int	next;
	int	offset;

	i = 0;
	offset = 0;
	if (philo->param[NUM_OF_PHILO] < 2)
		return ;
	while (true)
	{
		next = (i + offset + 1) % philo->param[NUM_OF_PHILO];
		while (philo->shared->forks[i] || philo->shared->forks[next])
		{
		}
		change_fork(philo, i + offset, i + offset + 1);
		pthread_mutex_lock(&philo->philos[i + offset + 1]->state_lock);
		philo->philos[i + offset + 1]->state = HAS_FORK;
		safe_print(philo->philos[i + offset + 1]);
		pthread_mutex_unlock(&philo->philos[i + offset + 1]->state_lock);
		usleep(10000);
		i = (i + 2) % philo->param[NUM_OF_PHILO];
		if (i == 0)
			offset = (philo->param[NUM_OF_PHILO] % 2 == 0) * (offset == 0);
		if (philo->state == TERMINATE)
			return ;
	}
}

void	philo_eat(t_philo *philo)
{
	bool	has_fork;

	has_fork = false;
	while (!has_fork && gettime() < philo->time_death)
	{
		pthread_mutex_lock(&philo->state_lock);
		has_fork = philo->state == HAS_FORK;
		pthread_mutex_unlock(&philo->state_lock);
	}
	if (gettime() >= philo->time_death)
	{
		if (philo->state == HAS_FORK)
			change_fork(philo, philo->id - 1, 0);
		pthread_mutex_lock(&philo->state_lock);
		philo->state = DEAD;
		pthread_mutex_unlock(&philo->state_lock);
		safe_print(philo);
		return ;
	}
	pthread_mutex_lock(&philo->state_lock);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->state_lock);
	safe_print(philo);
	philo->time_death = gettime() + philo->param[TIME_TO_DIE];
	usleep(1000 * philo->param[TIME_TO_EAT]);
	change_fork(philo, philo->id - 1, 0);
	philo->meals++;
	return ;
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_lock);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->state_lock);
	safe_print(philo);
	usleep(1000 * philo->param[TIME_TO_SLEEP]);
	pthread_mutex_lock(&philo->state_lock);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->state_lock);
	safe_print(philo);
	return ;
}
