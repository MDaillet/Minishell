/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:42:05 by mdaillet          #+#    #+#             */
/*   Updated: 2021/09/16 13:42:17 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putstrl(char *str, int n)
{
	int	i;

	i = 0;
	while (str[i] && i < n)
		ft_putchar(str[i++]);
	return (i);
}

char	*ft_strlow(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
	return (str);
}

int	ft_char(char c, t_pff pff)
{
	int	i;

	i = 0;
	if (pff.minus == 1)
		ft_putchar(c);
	i = ft_width(pff.width, 1, 0);
	if (pff.minus == 0)
		ft_putchar(c);
	return (i + 1);
}

int	ft_intypelist(int c)
{
	return ((c == 'c') || (c == 's') || (c == 'p') || (c == 'd') || (c == 'i')
		|| (c == 'u') || (c == 'x') || (c == 'X') || (c == '%'));
}

int	ft_inflaglist(int c)
{
	return ((c == '-') || (c == ' ') || (c == '0') || (c == '.') || (c == '*'));
}
