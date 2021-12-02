/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:09:54 by mdaillet          #+#    #+#             */
/*   Updated: 2021/09/16 13:43:02 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_process(int c, t_pff pff, va_list arguments)
{
	int	i;

	i = 0;
	if (c == 'c')
		i = ft_char(va_arg(arguments, int), pff);
	else if (c == 's')
		i = ft_str(va_arg(arguments, char *), pff);
	else if (c == 'p')
		i = ft_ptr(va_arg(arguments, unsigned long long), pff);
	else if (c == 'd' || c == 'i')
		i = ft_int(va_arg(arguments, int), pff);
	else if (c == 'u')
		i = i + ft_uint((unsigned int)va_arg(arguments, unsigned int),
				pff);
	else if (c == 'x')
		i = i + ft_hexadecimal(va_arg(arguments, unsigned int), 1, pff);
	else if (c == 'X')
		i = i + ft_hexadecimal(va_arg(arguments, unsigned int), 0, pff);
	else if (c == '%')
		i = i + ft_pourcent(pff);
	return (i);
}
