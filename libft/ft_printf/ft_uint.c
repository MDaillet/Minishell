/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:36:31 by mdaillet          #+#    #+#             */
/*   Updated: 2021/09/16 13:38:43 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_print_uint(char *nb, t_pff pff)
{
	int			i;

	i = 0;
	if (pff.dot >= 0)
		i = i + ft_width(pff.dot - 1, ft_strlen(nb) - 1, 1);
	i = i + ft_putstrl(nb, ft_strlen(nb));
	return (i);
}

static int	ft_process_uint(char *nb, t_pff pff)
{
	int			i;

	i = 0;
	if (pff.minus == 1)
		i = i + ft_print_uint(nb, pff);
	if (pff.dot >= 0 && (size_t)pff.dot < ft_strlen(nb))
		pff.dot = ft_strlen(nb);
	if (pff.dot >= 0)
	{
		pff.width -= pff.dot;
		i = i + ft_width(pff.width, 0, 0);
	}
	else
		i = i + ft_width(pff.width, ft_strlen(nb), pff.zero);
	if (pff.minus == 0)
		i = i + ft_print_uint(nb, pff);
	return (i);
}

int	ft_uint(unsigned int n, t_pff pff)
{
	char		*nb;
	int			i;

	i = 0;
	n = (unsigned int)(n + 1 + 4294967295);
	if (pff.dot == 0 && n == 0)
	{
		i = i + ft_width(pff.width, 0, 0);
		return (i);
	}
	nb = ft_uitoa(n);
	i = i + ft_process_uint(nb, pff);
	free(nb);
	return (i);
}
