/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:46:12 by mdaillet          #+#    #+#             */
/*   Updated: 2021/09/16 13:40:37 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_pffdot(const char *param, int start, t_pff *pff, va_list arguments)
{
	int	i;

	i = start;
	i++;
	if (param[i] == '*')
	{
		pff->dot = va_arg(arguments, int);
		i++;
	}
	else
	{
		pff->dot = 0;
		while (ft_isdigit(param[i]))
			pff->dot = (pff->dot * 10) + (param[i++] - '0');
	}
	return (i);
}

t_pff	ft_pffwidth(va_list arguments, t_pff pff)
{
	pff.star = 1;
	pff.width = va_arg(arguments, int);
	if (pff.width < 0)
	{
		pff.minus = 1;
		pff.width = pff.width * (-1);
		pff.zero = 0;
	}
	return (pff);
}

t_pff	ft_pffdigit(char c, t_pff pff)
{
	if (pff.star == 1)
		pff.width = 0;
	pff.width = (pff.width * 10) + (c - '0');
	return (pff);
}

t_pff	ft_pffminus(t_pff pff)
{
	pff.minus = 1;
	pff.zero = 0;
	return (pff);
}
