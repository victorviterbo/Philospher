/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prev_power.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:47:56 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/23 16:18:41 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

double	ft_prev_power(double n, int base_size);

double	ft_prev_power(double n, int base_size)
{
	double	sign;
	double	prev_power;

	prev_power = 1.0;
	sign = -2 * (n < 0) + 1;
	if (n < 0)
		n *= -1;
	while (n >= base_size)
	{
		prev_power *= base_size;
		n /= base_size;
	}
	return (sign * prev_power);
}
