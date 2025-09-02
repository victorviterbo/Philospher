/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorviterbo <victorviterbo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:53:34 by vviterbo          #+#    #+#             */
/*   Updated: 2025/09/02 09:39:58 by victorviter      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		checkphilo(t_philo **philo);
void	philo_finish(t_philo **philo, pthread_t *threads);
void	join_free_destroy(t_philo **philo, pthread_t *threads,
			int num_of_philo);
void	change_fork(t_philo *philo, int i, int newval);

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
	i = 0;
	while (i < philo[0]->param[NUM_OF_PHILO])
	{
		set_terminate_status(philo[i], true);
		i++;
	}
	if (dead > 0)
	{
		pthread_mutex_lock(&philo[dead - 1]->shared->print_lock);
		printf("%i:\tPhilo %i\tdied\n", gettime(philo[dead - 1]), dead);
		pthread_mutex_unlock(&philo[dead - 1]->shared->print_lock);
	}
	join_free_destroy(philo, threads, num_of_philo);
}

int	checkphilo(t_philo **philo)
{
	int		i;
	bool	all_fed;

	i = 0;
	all_fed = true;
	while (i < philo[0]->param[NUM_OF_PHILO])
	{
		if (philo[i]->state == DEAD || philo[i]->time_death < gettime(philo[0]))
			return (philo[i]->id);
		else if (philo[i]->state != FED)
			all_fed = false;
		i++;
	}
	return (-all_fed * FED);
}

void	join_free_destroy(t_philo **philo, pthread_t *threads, int num_of_philo)
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
		i++;
	}
	pthread_mutex_destroy(&philo[0]->shared->print_lock);
	pthread_mutex_destroy(&philo[0]->shared->terminate_lock);
	pthread_mutex_destroy(&philo[0]->shared->start_time_lock);
	free(philo[0]->shared->forks);
	free(philo[0]->shared->lock);
	free(philo[0]->shared);
	free(philo[0]->param);
	ft_free_array((void **)philo, num_of_philo);
	free(threads);
}
