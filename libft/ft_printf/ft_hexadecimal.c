/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 00:54:53 by mdaillet          #+#    #+#             */
/*   Updated: 2021/09/16 13:39:39 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_print_hexa(char *nb, t_pff pff)
{
	int		i;
	size_t	nb_len;

	i = 0;
	nb_len = ft_strlen(nb);
	if (pff.dot >= 0)
		i = i + ft_width(pff.dot - 1, nb_len - 1, 1);
	i = i + ft_putstrl(nb, nb_len);
	return (i);
}

static int	ft_process_hexa(char *nb, t_pff pff)
{
	int		i;

	i = 0;
	if (pff.minus == 1)
		i = i + ft_print_hexa(nb, pff);
	if (pff.dot >= 0 && (size_t)pff.dot < ft_strlen(nb))
		pff.dot = ft_strlen(nb);
	if (pff.dot >= 0)
	{
		pff.width = pff.width - pff.dot;
		i = i + ft_width(pff.width, 0, 0);
	}
	else
		i = i + ft_width(pff.width, ft_strlen(nb), pff.zero);
	if (pff.minus == 0)
		i = i + ft_print_hexa(nb, pff);
	return (i);
}

int	ft_hexadecimal(unsigned int ui, int lower, t_pff pff)
{
	char	*nb;
	int		i;

	i = 0;
	ui = (unsigned int)(4294967295 + 1 + ui);
	if (pff.dot == 0 && ui == 0)
	{
		i = i + ft_width(pff.width, 0, 0);
		return (i);
	}
	nb = ft_put_base((unsigned long long)ui, 16);
	if (lower == 1)
		nb = ft_strlow(nb);
	i = i + ft_process_hexa(nb, pff);
	free(nb);
	return (i);
}
