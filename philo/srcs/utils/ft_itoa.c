/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:49:54 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/23 16:16:40 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char			*ft_itoa(int n);
static size_t	handle_neg(long *number, char *number_str);

char	*ft_itoa(int n)
{
	char	*number_str;
	size_t	magnitude;
	size_t	i;
	long	number;

	number = n;
	number_str = ft_calloc((ft_number_len(number, 10) + 1),
			sizeof(char));
	if (!number_str)
		return (NULL);
	i = handle_neg(&number, number_str);
	magnitude = ft_prev_power((double)number, 10.0);
	while (magnitude)
	{
		number_str[i] = number / magnitude + '0';
		number %= magnitude;
		magnitude /= 10;
		i++;
	}
	number_str[i] = '\0';
	return (number_str);
}

static size_t	handle_neg(long *number, char *number_str)
{
	if (*number < 0)
	{
		*(number_str) = '-';
		*number = -(*number);
		return (1);
	}
	else
		return (0);
}
