/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:53:34 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/05 11:20:12 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		checkphilo(t_philo **philo);
void	safe_print(t_philo *philo, int time, t_philostate state);
void	philo_finish(t_philo **philo, pthread_t *threads);
void	change_fork(t_philo *philo, int i, int newval);

int	checkphilo(t_philo **philo)
{
	int		i;
	bool	all_fed;

	i = 1;
	all_fed = true;
	while (i < philo[0]->param[NUM_OF_PHILO] + 1)
	{
		if (philo[i]->state == DEAD)
			return (DEAD);
		else if (philo[i]->state != FED)
			all_fed = false;
		i++;
	}
	return (all_fed * FED);
}

void	safe_print(t_philo *philo, int time, t_philostate state)
{
	pthread_mutex_lock(&philo->shared->print_lock);
	if (state == HAS_FORK)
		printf("%i: Philo %i\t has taken a fork\n", time, philo->id);
	else if (state == EATING)
		printf("%i: Philo %i\t has started eating\n", time, philo->id);
	else if (state == THINKING)
		printf("%i: Philo %i\t has started thinking\n", time, philo->id);
	else if (state == SLEEPING)
		printf("%i: Philo %i\t has started sleeping\n", time, philo->id);
	else if (state == DEAD)
		printf("%i: Philo %i\t died\n", time, philo->id);
	pthread_mutex_unlock(&philo->shared->print_lock);
	return ;
}

void	philo_finish(t_philo **philo, pthread_t *threads)
{
	int	num_of_philo;
	int	i;

	num_of_philo = philo[0]->param[NUM_OF_PHILO];
	while (!checkphilo(philo))
	{
	}
	philo[0]->state = TERMINATE;
	i = 0;
	while (i < num_of_philo + 1)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("ERROR: could not join thread %i\n", i);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < num_of_philo + 1)
	{
		pthread_mutex_destroy(&philo[0]->state_lock);
		if (i < num_of_philo)
			pthread_mutex_destroy(&philo[0]->shared->lock[i]);
		i++;
	}
	free(philo[0]->shared->forks);
	free(philo[0]->shared);
	free(philo[0]->param);
	pthread_mutex_destroy(&philo[0]->shared->print_lock);
	ft_free_array((void **)philo, num_of_philo + 1);
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
