/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:26:59 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/01 17:07:49 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close_parent(int **fd, int order) // Close both entries for each line of the double entry array fd
{
	int	size;
	int	i;

	i = 0;
	size = ft_pip_size(fd);
	while (i < size && i <= order)
	{
		ft_close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i < order && i < size)
	{
		ft_close(fd[i][0]);
		i++;
	}
}

void	ft_close_child(int **fd, int in, int out) // Close the writing entry if we are in tje first node and the reading entry if we are in the last and both if neither of them
{
	int	size;
	int	i;

	i = 0;
	size = ft_pip_size(fd);
	while (size > i)
	{
		if (i == in)
			ft_close(fd[i][1]);
		else if (i == out)
			ft_close(fd[i][0]);
		else
		{
			ft_close(fd[i][0]);
			ft_close(fd[i][1]);
		}
		i++;
	}
}
