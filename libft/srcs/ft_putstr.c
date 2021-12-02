/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 20:06:35 by mdaillet          #+#    #+#             */
/*   Updated: 2021/01/07 20:08:32 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == 0)
	{
		my_putstr("(null)");
		return ;
	}
	while (str[i] != '\0')
	{
		my_putchar(str[i]);
		i = i + 1;
	}
}
