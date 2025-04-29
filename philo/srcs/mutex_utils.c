/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:05:30 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/29 16:34:23 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(t_philo *philo);
void	change_fork(t_philo *philo, int i, int newval);
bool	get_terminate_status(t_philo *philo);
void	set_terminate_status(t_philo *philo, bool new_value);
bool	forks_avail(t_philo *philo);

void	safe_print(t_philo *philo)
{
	if (get_terminate_status(philo))
		return ;
	pthread_mutex_lock(&philo->shared->print_lock);
	if (philo->state == HAS_FORK)
		printf("%i: Philo %i\t has taken a fork\n", gettime(philo), philo->id);
	else if (philo->state == EATING)
		printf("%i: Philo %i\t has started eating\n", gettime(philo), philo->id);
	else if (philo->state == THINKING)
		printf("%i: Philo %i\t has started thinking\n",
			gettime(philo), philo->id);
	else if (philo->state == SLEEPING)
		printf("%i: Philo %i\t has started sleeping\n",
			gettime(philo), philo->id);
	pthread_mutex_unlock(&philo->shared->print_lock);
	return ;
}

void	change_fork(t_philo *philo, int i, int newval)
{
	int	next;

	next = (i + 1) % philo->param[NUM_OF_PHILO];
	pthread_mutex_lock(&philo->shared->lock[i]);
	philo->shared->forks[i] = newval;
	pthread_mutex_unlock(&philo->shared->lock[i]);
	pthread_mutex_lock(&philo->shared->lock[next]);
	philo->shared->forks[next] = newval;
	pthread_mutex_unlock(&philo->shared->lock[next]);
}

bool	get_terminate_status(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(&philo->shared->terminate_lock);
	status = philo->shared->terminate;
	pthread_mutex_unlock(&philo->shared->terminate_lock);
	return (status);
}

void	set_terminate_status(t_philo *philo, bool new_value)
{
	pthread_mutex_lock(&philo->shared->terminate_lock);
	philo->shared->terminate = new_value;
	pthread_mutex_unlock(&philo->shared->terminate_lock);
}

bool	forks_avail(t_philo *philo)
{
	bool	avail;
	int		next;

	next = philo->id % philo->param[NUM_OF_PHILO];
	pthread_mutex_lock(&philo->shared->lock[philo->id - 1]);
	avail = (philo->shared->forks[philo->id - 1] == 0);
	pthread_mutex_unlock(&philo->shared->lock[philo->id - 1]);
	if (avail == false)
		return (avail);
	pthread_mutex_lock(&philo->shared->lock[next]);
	avail = (avail && philo->shared->forks[next] == 0);
	pthread_mutex_unlock(&philo->shared->lock[next]);
	return (avail);
}
