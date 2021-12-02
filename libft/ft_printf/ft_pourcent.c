/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pourcent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:20:22 by mdaillet          #+#    #+#             */
/*   Updated: 2021/09/16 13:03:36 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_pourcent(t_pff pff)
{
	int	i;

	i = 0;
	if (pff.minus == 1)
		i = i + ft_putstrl("%", 1);
	i = i + ft_width(pff.width, 1, pff.zero);
	if (pff.minus == 0)
		i = i + ft_putstrl("%", 1);
	return (i);
}
