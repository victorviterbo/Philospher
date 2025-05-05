/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:56:03 by vviterbo          #+#    #+#             */
/*   Updated: 2025/05/05 17:39:38 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		checkphilo(t_philo **philo);
void	philo_finish(t_philo **philo, pthread_t *threads);
void	join_free_destroy(t_philo **philo, pthread_t *threads,
			int num_of_philo);
void	free_philos(t_philo **philo, pthread_t *threads, int num_of_philo);

int	checkphilo(t_philo **philo)
{
	int		i;
	bool	all_fed;

	i = 0;
	all_fed = true;
	while (i < philo[0]->param[NUM_OF_PHILO])
	{
		if (get_state(philo[i]) == DEAD
			|| get_tod(philo[i]) < gettime(philo[0]))
			return (philo[i]->id);
		else if (get_state(philo[i]) != FED)
			all_fed = false;
		i++;
	}
	return (-all_fed * FED);
}

void	philo_finish(t_philo **philo, pthread_t *threads)
{
	int	num_of_philo;
	int	dead;

	num_of_philo = philo[0]->param[NUM_OF_PHILO];
	dead = checkphilo(philo);
	while (dead == 0)
	{
		dead = checkphilo(philo);
		usleep(1000);
	}
	set_terminate_status(philo[0], true);
	if (dead > 0)
	{
		pthread_mutex_lock(&philo[dead - 1]->shared->print_lock);
		printf("%i:\tPhilo %i\tdied\n", gettime(philo[dead - 1]), dead);
		pthread_mutex_unlock(&philo[dead - 1]->shared->print_lock);
	}
	join_free_destroy(philo, threads, num_of_philo);
}

void	join_free_destroy(t_philo **philo, pthread_t *threads,
			int num_of_philo)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("ERROR: could not join thread %i\n", i);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < num_of_philo)
	{
		pthread_mutex_destroy(&philo[0]->shared->lock[i]);
		pthread_mutex_destroy(&philo[i]->state_lock);
		i++;
	}
	pthread_mutex_destroy(&philo[0]->shared->print_lock);
	pthread_mutex_destroy(&philo[0]->shared->terminate_lock);
	pthread_mutex_destroy(&philo[0]->shared->start_time_lock);
	free_philos(philo, threads, num_of_philo);
}

void	free_philos(t_philo **philo, pthread_t *threads, int num_of_philo)
{
	free(philo[0]->shared->forks);
	free(philo[0]->shared->lock);
	free(philo[0]->shared);
	free(philo[0]->param);
	ft_free_array((void **)philo, num_of_philo);
	free(threads);
	return ;
}
