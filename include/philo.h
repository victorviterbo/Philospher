/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:36:18 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/23 16:22:00 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef enum e_philostate
{
	SLEEPING,
	EATING,
	THINKING
}	t_philostate;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		ft_isint(char *str);
char	*ft_itoa(int n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *str);
double	ft_prev_power(double n, int base_size);
int		ft_number_len(long long n, int base_size);
int		ft_iswhitespace_eq(int c);
char	*ft_strchr(const char *s, int c);

#endif