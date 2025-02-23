/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:36:18 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/23 11:48:16 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_philostate
{
	SLEEPING,
	EATING,
	THINKING
}	t_philostate;

void			*ft_calloc(size_t count, size_t size);
int				ft_atoi(const char *str);
int				ft_isint(char *str);

#endif