/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:50:44 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/10 18:57:32 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*ft_del_pipe(t_builtin *node) // If we are at the end of our big node and the last cmd starts with | or ; we skip it and return the first cmd of the next big node (Or 0 if we are done). If everything is normal we just return the cmd from node
{
	t_builtin *t;

	if (!node->cmd || !node->cmd->next)
	{
		if (!node->cmd->next && ft_strchr("|;", node->cmd->str[0]))
		{
			if (node->cmd->id)
				return (node->cmd);
			t = node->next;
			if (t)
				return (t->cmd);
			else
				return (0);
		}
		return (node->cmd);
	}
	if (ft_strchr("|;", node->cmd->str[0]))
		return (node->cmd->next->next);
	return (node->cmd);
}

static void	ft_open(int	*t1, int *fd) // Initialize the fds and save them into t1
{
	fd[0] = STDIN;
	fd[1] = STDOUT;
	t1[0] = dup(STDIN);
	t1[1] = dup(STDOUT);
}

static void	ft_end(int *t1, int *fd) // Close the fds and save the temps fds into IN and OUT
{
	ft_close(fd[0]);
	ft_close(fd[1]);
	dup2(t1[0], STDIN);
	dup2(t1[1], STDOUT);
	g_ms->pip[0] = dup(STDIN);
	g_ms->pip[1] = dup(STDOUT);
}

int	ft_exe2(t_builtin *node, t_list **venv, int *fd) // Recursively start the builtin utilities for each node while checking for redirections
{
	int	i;
	
	if (!node || !node->cmd || !node->cmd->str)
		return (EXIT_SUCCESS);
	if (node->next)
	{
		i = ft_exe2(node->next, venv, fd);
		if (i == ERROR)
			return (i);
	}
	if (ft_strncmp(node->cmd->str, ">", 1))
		i = ft_redirection1(node, 'T', fd);
	else if (ft_strncmp(node->cmd->str, ">>", 2))
		i = ft_redirection1(node, 'A', fd);
	else if (ft_strncmp(node->cmd->str, "<", 1))
		i = ft_redirection2(node);
	else if (ft_strncmp(node->cmd->str, "<<", 2))
		i = ft_redirection3(node, fd);
	else 
		i = ft_builtin(node, venv);
	return (i);
}

int	ft_exe(t_builtin *node, t_list **venv) // Initialize everything so we have each node being a command and argument, and redirection are the start of the node
{
	int	fd[2];
	int	t1[2];
	int	i;
	t_list	*list;
	t_builtin	*node2;
	if (!node || !node->cmd || !node->cmd->str)
		return (EXIT_SUCCESS);
	ft_open(t1, fd);
	list = ft_del_pipe(node);
	if (!(list))
		return (REDIRECTION_ERROR);
	node2 = ft_build_and_save(list);
	if (!ft_strchr("><", node2->cmd->str[0]))
	ft_builtin_split(node2, "><");
	ft_remove_space(node2);
	g_ms->pip[0] = dup(STDIN);
	g_ms->pip[1] = dup(STDOUT);
	i = ft_exe2(node2, venv, fd);
	ft_end(t1, fd);
	ft_freebuilt(&node2);
	return (i);
}
