/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:01:19 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/07 20:02:30 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(void *s)
{
	if (s)
	{
		free(s);
		s = 0;
	}
}

void	ft_freen(char **s, int n)
{
	while (n--)
	{
		if (s[n])
			ft_free(s[n]);
	}
	ft_free(s);
}

int	ft_strlen2(char **av)
{
	int	i;

	if (!av)
		return (0);
	i = 0;
	while (av[i])
		i++;
	return (i);
}
