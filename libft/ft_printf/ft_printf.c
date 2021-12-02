/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 18:33:25 by mdaillet          #+#    #+#             */
/*   Updated: 2021/09/16 13:43:45 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_pff	ft_init_pff(void)
{
	t_pff		pff;

	pff.dot = -1;
	pff.minus = 0;
	pff.star = 0;
	pff.type = 0;
	pff.width = 0;
	pff.zero = 0;
	return (pff);
}

int	ft_pff_parse(const char *param, int j, t_pff *pff,
		va_list arguments)
{
	while (param[j])
	{
		if (!ft_isdigit(param[j]) && !ft_intypelist(param[j])
			&& !ft_inflaglist(param[j]))
			break ;
		if (param[j] == '0' && pff->width == 0 && pff->minus == 0)
			pff->zero = 1;
		if (param[j] == '.')
			j = ft_pffdot(param, j, pff, arguments);
		if (param[j] == '-')
			*pff = ft_pffminus(*pff);
		if (param[j] == '*')
			*pff = ft_pffwidth(arguments, *pff);
		if (ft_isdigit(param[j]))
			*pff = ft_pffdigit(param[j], *pff);
		if (ft_intypelist(param[j]))
		{
			pff->type = param[j];
			break ;
		}
		j++;
	}
	return (j);
}

int	ft_process_param(const char *param, va_list arguments,
		int j, int i)
{
	t_pff		pff;

	while (1)
	{
		pff = ft_init_pff();
		if (!param[j])
			break ;
		else if (param[j] == '%' && param[j + 1])
		{
			if (param[j + 1] == ' ')
			{
				i = i + ft_putstrl(" ", 1);
				j++;
			}
			j = ft_pff_parse(param, ++j, &pff, arguments);
			if (ft_intypelist(param[j]))
				i += ft_process((char)pff.type, pff, arguments);
			else if (param[j])
				i += ft_putchar(param[j]);
		}
		else if (param[j] != '%')
			i += ft_putchar(param[j]);
		j++;
	}
	return (i);
}

int	ft_printf(const char *input, ...)
{
	const char	*param;
	va_list		arguments;
	int			total;
	int			j;
	int			i;

	param = ft_strdup(input);
	total = 0;
	j = 0;
	i = 0;
	va_start(arguments, input);
	total += ft_process_param(param, arguments, j, i);
	va_end(arguments);
	free((char *)param);
	return (total);
}
