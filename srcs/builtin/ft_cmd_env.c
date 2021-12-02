/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:58:45 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/06 09:30:23 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_show_env(t_list *venv, char *name)
{
	while (venv)
	{
		if (name)
			ft_putstr_fd(name, 1);
		if (venv->str)
		{
			ft_putstr_fd(venv->id, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(venv->str, 1);
			ft_putstr_fd("\n", 1);
		}
		venv = venv->next;
	}
}

void	ft_show_env2(t_list *l, char *s)
{
	while (l)
	{
		if (s)
			ft_putstr_fd(s, 1);
		ft_putstr_fd(l->id, 1);
		if (l->str)
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			ft_putstr_fd(l->str, 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		l = l->next;
	}
}

int	ft_cmd_env(t_builtin *node, t_list *venv)
{
	if (!node)
		return (ERROR);
	if (node->cmd->next)
	{
		printf("No argument needed");
		return (ERROR);
	}
	ft_show_env(venv, 0);
	return (SUCCESS);
}
