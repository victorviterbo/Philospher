/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:51:54 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/26 18:46:15 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life(void *param);
int		gettime(void);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	safe_print(t_philo *philo);

void	*life(void *param)
{
	t_philo	*philo;

	philo = param;
	philo->time_death = gettime() + philo->param[TIME_TO_DIE];
	while (gettime() < philo->time_death)
	{
		philo_eat(philo);
		if (philo->param[NUM_MEALS] && philo->meals == philo->param[NUM_MEALS])
		{
			philo->state = FED;
			return (philo);
		}
		philo_sleep(philo);
	}
	philo->state = DEAD;
	safe_print(philo);
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	int		fleft;
	int		fright;

	fleft = philo->id;
	fright = (philo->id + 1) % philo->param[NUM_OF_PHILO];
	while (philo->state != EATING && gettime() < philo->time_death)
	{
		pthread_mutex_lock(&philo->forks->lock);
		if (philo->forks->forklist[fleft] && philo->forks->forklist[fright] && fright != fleft)
		{
			philo->forks->forklist[fleft] = false;
			philo->forks->forklist[fright] = false;
			philo->state = EATING;
		}
		pthread_mutex_unlock(&philo->forks->lock);
	}
	if (gettime() >= philo->time_death)
	{
		philo->state = DEAD;
		exit (EXIT_FAILURE) ;
	}
	safe_print(philo);
	philo->time_death = gettime() + philo->param[TIME_TO_DIE];
	usleep(1000 * philo->param[TIME_TO_EAT]);
	pthread_mutex_lock(&philo->forks->lock);
	philo->forks->forklist[fleft] = true;
	philo->forks->forklist[fright] = true;
	pthread_mutex_unlock(&philo->forks->lock);
	philo->meals++;
	return ;
}

void	philo_sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	safe_print(philo);
	usleep(1000 * philo->param[TIME_TO_SLEEP]);
	philo->state = THINKING;
	safe_print(philo);
	return ;
}

int	gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((int)(tv.tv_sec + tv.tv_usec / 1000));
}

void	safe_print(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks->lock);
	if (philo->state == EATING)
	{
		printf("%i: Philo %i\t has taken a fork\n", gettime(), philo->id + 1);
		printf("%i: Philo %i\t has started eating\n", gettime(), philo->id + 1);
	}
	else if (philo->state == THINKING)
		printf("%i: Philo %i\t has started thinking\n", gettime(), philo->id + 1);
	else if (philo->state == SLEEPING)
		printf("%i: Philo %i\t has started sleeping\n", gettime(), philo->id + 1);
	else if (philo->state == DEAD)
		printf("%i: Philo %i\t died\n", gettime(), philo->id + 1);
	pthread_mutex_unlock(&philo->forks->lock);
	return ;
}
