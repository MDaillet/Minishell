/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:24:16 by mdaillet          #+#    #+#             */
/*   Updated: 2021/09/16 13:37:11 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_put_ptr(char *ptr, t_pff pff)
{
	int		i;

	i = 0;
	i = i + ft_putstrl("0x", 2);
	if (pff.dot >= 0)
	{
		i = i + ft_width(pff.dot, ft_strlen(ptr), 1);
		i = i + ft_putstrl(ptr, pff.dot);
	}
	else
		i = i + ft_putstrl(ptr, ft_strlen(ptr));
	return (i);
}

static int	ft_nullcheck(t_pff pff)
{
	int		i;

	i = 0;
	if (pff.minus == 0)
	{
		i = i + ft_width(pff.width - 2, 0, 0);
		i = i + ft_putstrl("0x", 2);
	}
	else
	{
		i = i + ft_putstrl("0x", 2);
		i = i + ft_width(pff.width - 2, 0, 0);
	}
	return (i);
}

int	ft_ptr(unsigned long long nb, t_pff pff)
{
	char	*ptr;
	int		i;

	i = 0;
	if (nb == 0 && pff.dot == 0)
	{
		i = i + ft_nullcheck(pff);
		return (i);
	}
	ptr = ft_put_base(nb, 16);
	ptr = ft_strlow(ptr);
	if ((size_t)pff.dot < ft_strlen(ptr))
		pff.dot = ft_strlen(ptr);
	if (pff.minus == 1)
		i = i + ft_put_ptr(ptr, pff);
	i = i + ft_width(pff.width, ft_strlen(ptr) + 2, 0);
	if (pff.minus == 0)
		i += ft_put_ptr(ptr, pff);
	free(ptr);
	return (i);
}
