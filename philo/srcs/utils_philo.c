/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:53:34 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/28 16:34:20 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		checkphilo(t_philo **philo);
int		gettime(void);
void	safe_print(t_philo *philo);
void	philo_finish(t_philo **philo);

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

int	gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((int)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	safe_print(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_lock);
	if (philo->state == EATING)
	{
		printf("%i: Philo %i\t has taken a fork\n", gettime(), philo->id);
		printf("%i: Philo %i\t has started eating\n", gettime(), philo->id);
	}
	else if (philo->state == THINKING)
		printf("%i: Philo %i\t has started thinking\n", gettime(), philo->id);
	else if (philo->state == SLEEPING)
		printf("%i: Philo %i\t has started sleeping\n", gettime(), philo->id);
	else if (philo->state == DEAD)
		printf("%i: Philo %i\t died\n", gettime(), philo->id);
	pthread_mutex_unlock(&philo->print_lock);
	return ;
}

void	philo_finish(t_philo **philo)
{
	int	num_of_philo;

	num_of_philo = philo[0]->param[NUM_OF_PHILO];
	while (!checkphilo(philo))
	{
	}
	philo[0]->state = TERMINATE;
	free(philo[0]->forks->flist);
	pthread_mutex_destroy(&philo[0]->forks->lock);
	free(philo[0]->forks);
	free(philo[0]->param);
	pthread_mutex_destroy(&philo[0]->print_lock);
	ft_free_array((void **)philo, num_of_philo + 1);
}
