/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:26:44 by mdaillet          #+#    #+#             */
/*   Updated: 2021/09/16 13:40:15 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_str_int(char *str, t_pff pff)
{
	int	i;

	i = 0;
	if (pff.dot >= 0)
	{
		if (pff.zero == 0)
			i = i + ft_width(pff.dot, ft_strlen(str), 0);
		else if (pff.zero == 1)
			i = i + ft_width(pff.dot, ft_strlen(str), 0);
		i = i + ft_putstrl(str, pff.dot);
	}
	else
		i = i + ft_putstrl(str, ft_strlen(str));
	return (i);
}

int	ft_str(char *str, t_pff pff)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	if (pff.dot >= 0 && (size_t)pff.dot > ft_strlen(str))
		pff.dot = ft_strlen(str);
	if (pff.minus == 1)
		i = i + ft_str_int(str, pff);
	if (pff.dot >= 0 && pff.zero == 0)
		i = i + ft_width(pff.width, pff.dot, 0);
	else if (pff.dot >= 0 && pff.zero == 1)
		i = i + ft_width(pff.width, pff.dot, 1);
	else if (pff.zero == 0)
		i = i + ft_width(pff.width, ft_strlen(str), 0);
	else
		i = i + ft_width(pff.width, ft_strlen(str), 1);
	if (pff.minus == 0)
		i = i + ft_str_int(str, pff);
	return (i);
}
