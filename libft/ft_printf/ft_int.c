/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 08:39:36 by mdaillet          #+#    #+#             */
/*   Updated: 2021/09/16 13:39:04 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_print_int(char *nb, int n_save, t_pff pff)
{
	int			i;

	i = 0;
	if (n_save != -2147483648 && n_save < 0 && pff.dot >= 0)
		ft_putchar('-');
	if (pff.dot >= 0)
		i = i + ft_width(pff.dot - 1, ft_strlen(nb) - 1, 1);
	i += ft_putstrl(nb, ft_strlen(nb));
	return (i);
}

static int	ft_process_int(char *nb, int n_save, t_pff pff)
{
	int			i;

	i = 0;
	if (pff.minus == 1)
		i = i + ft_print_int(nb, n_save, pff);
	if (pff.dot >= 0 && (size_t)pff.dot < ft_strlen(nb))
		pff.dot = ft_strlen(nb);
	if (pff.dot >= 0)
	{
		pff.width -= pff.dot;
		i += ft_width(pff.width, 0, 0);
	}
	else
		i += ft_width(pff.width, ft_strlen(nb), pff.zero);
	if (pff.minus == 0)
		i += ft_print_int(nb, n_save, pff);
	return (i);
}

int	ft_int(int n, t_pff pff)
{
	char		*nb;
	int			n_save;
	int			i;

	n_save = n;
	i = 0;
	if (pff.dot == 0 && n == 0)
	{
		i += ft_width(pff.width, 0, 0);
		return (i);
	}
	if (n != -2147483648 && n < 0 && (pff.dot >= 0 || pff.zero == 1))
	{
		if (pff.zero == 1 && pff.dot == -1)
			ft_putstrl("-", 1);
		n *= -1;
		pff.zero = 1;
		pff.width--;
		i++;
	}
	nb = ft_itoa(n);
	i += ft_process_int(nb, n_save, pff);
	free(nb);
	return (i);
}
