/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:46:12 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/23 11:47:48 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void			*ft_calloc(size_t count, size_t size);
int				ft_atoi(const char *str);
int				ft_isint(char *str);
static size_t	get_size(long n);
static bool		isin_intrange(char *str, bool isneg);

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*bptr;
	size_t			i;

	i = 0;
	if (!count || !size)
		return (malloc(0));
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	bptr = (unsigned char *)ptr;
	while (i < (count * size))
	{
		*(bptr + i) = '\0';
		i++;
	}
	return (ptr);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		number;

	i = 0;
	sign = 1;
	number = 0;
	while (ft_iswhitespace_eq(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		number = number * 10 + str[i] - '0';
		i++;
	}
	return (sign * number);
}

int	ft_isint(char *str)
{
	size_t	i;
	bool	isneg;

	i = 0;
	if (!str)
		return (0);
	isneg = (ft_strchr(str, '-') != NULL);
	while (ft_iswhitespace_eq(str[0]))
		str++;
	if (str[0] && (str[0] == '+' || str[0] == '-'))
		str++;
	if (!str[0])
		return (0);
	while (str[0] == '0')
		str++;
	while (str[i])
	{
		if (!ft_strchr("0123456789", str[i]))
			return (0);
		i++;
	}
	return (isin_intrange(str, isneg));
}

static bool	isin_intrange(char *str, bool isneg)
{
	char	*max;
	char	*min;

	if (ft_strlen(str) > get_size(INT_MAX))
		return (0);
	else if ((ft_strlen(str) == get_size(INT_MAX)) && isneg == false)
	{
		max = ft_itoa(INT_MAX);
		if (ft_memcmp(max, str, ft_strlen(str)) < 0)
			return (free(max), 0);
		free(max);
	}
	else if (ft_strlen(str) == get_size(INT_MAX) && isneg == true)
	{
		min = ft_itoa(INT_MIN);
		if (ft_memcmp(min + 1, str, ft_strlen(str)) < 0)
			return (free(min), 0);
		free(min);
	}
	return (1);
}

static size_t	get_size(long n)
{
	size_t	size;

	size = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}
