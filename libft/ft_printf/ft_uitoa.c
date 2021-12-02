/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:13:51 by mdaillet          #+#    #+#             */
/*   Updated: 2021/09/16 13:41:02 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_size(long n)
{
	size_t	size;

	size = 0;
	if (n < 0)
	{
		size++;
		n = -n;
	}
	while (n >= 1)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static char	*ft_processuitoa(char *result, long nb, int size, int neg)
{
	if (nb != 0)
		result = malloc(sizeof(char) * (size + 1));
	else
		return (result = ft_strdup("0"));
	if (!result)
		return (0);
	neg = 0;
	if (nb < 0)
	{
		neg++;
		nb = -nb;
	}
	result[size] = '\0';
	while (--size)
	{
		result[size] = (nb % 10) + '0';
		nb /= 10;
	}
	if (neg == 1)
		result[0] = '-';
	else
		result[0] = (nb % 10) + '0';
	return (result);
}

char	*ft_uitoa(unsigned int n)
{
	char	*result;
	long	nb;
	int		neg;
	int		size;

	nb = n;
	size = ft_size(nb);
	result = 0;
	neg = 0;
	result = ft_processuitoa(result, nb, size, neg);
	if (!result)
		return (0);
	return (result);
}
