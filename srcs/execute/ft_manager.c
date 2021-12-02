/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:11:46 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/01 19:05:12 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_pipmanager(t_list **venv, t_builtin	**node)
{
	int	**pipfd;
	int	pipcount;
	int	order;

	order = 0;
	pipcount = ft_pip_count(*node);
	pipfd = ft_pip_init(pipcount);
	if (!pipfd)
		ft_error("Allocating memory problem");
	while (*node && order <= pipcount)
	{
		g_ms->status = ft_pipexe(*node, venv, pipfd, order);
		*node = (*node)->next;
		order++;
	}
	ft_pip_free(&pipfd, pipcount);
}

void	ft_manager(t_list **venv, t_builtin *node)
{
	g_ms->status = SUCCESS;
	while (node && node->cmd)
	{
		if (node->next && node->next->cmd->str &&
			node->next->cmd->str[0] == '|')
			ft_pipmanager(venv, &node);
		else if (node->cmd && node->cmd->str &&
			node->cmd->str[0] == ';' && !node->cmd->next)
			break ;
		else if (!node->cmd->str)
			break ;
		else
		{
			g_ms->status = ft_exe(node, venv);
			node = node->next;
		}
	}
}
