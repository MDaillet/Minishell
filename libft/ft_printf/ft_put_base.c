/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 01:25:59 by mdaillet          #+#    #+#             */
/*   Updated: 2021/09/16 13:41:23 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_process_base(unsigned long long n_save, int base, char *nb,
			int i)
{
	while (n_save != 0)
	{
		if ((n_save % base) < 10)
			nb[i - 1] = (n_save % base) + 48;
		else
			nb[i - 1] = (n_save % base) + 55;
		n_save = n_save / base;
		i--;
	}
	return (nb);
}

char	*ft_put_base(unsigned long long n, int base)
{
	char				*nb;
	unsigned long long	n_save;
	int					i;

	nb = 0;
	i = 0;
	n_save = n;
	if (n == 0)
		return (ft_strdup("0"));
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	nb = malloc(sizeof(char) * (i + 1));
	if (!nb)
		return (0);
	nb[i] = '\0';
	nb = ft_process_base(n_save, base, nb, i);
	return (nb);
}
