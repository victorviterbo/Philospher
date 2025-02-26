/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:07:59 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/24 11:57:30 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_arrlen(char **array);

size_t	ft_arrlen(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return (0);
	while (*(array + i))
		i++;
	return (i);
}
