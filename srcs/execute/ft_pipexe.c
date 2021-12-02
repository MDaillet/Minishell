/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipexe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 17:06:14 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/09 17:21:19 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_piping(int in, int out) // Save STDIN in in and STDOUT in out and then close them properly
{
	if (in != -1)
	{
		if (dup2(in, STDIN) == -1)
			ft_error("Piping in : dup2 error");
		if (in > 0)
			close(in);
	}
	if (out != -1)
	{
		if (dup2(out, STDOUT) == -1)
			ft_error("Piping out : dup2 error");
		if (out == 0 || out > 1)
			close(out);
	}
}

static void	ft_start_piping(int	**fd, int order) // If first node, we link the out only, if last node, we link the read only, if neither, we link both read and write entries // PIP[0] --> read PIP[1] --> write
{
	int	i;

	i = ft_pip_size(fd);
	if (order == 0)
		ft_piping(-1, fd[order][1]);
	else if (order == i)
		ft_piping(fd[order - 1][0], -1);
	else
		ft_piping(fd[order - 1][0], fd[order][1]);
}
		

int	ft_pipexe(t_builtin *node, t_list **venv, int **fd, int order) // Fork and call the piping function for the child, and the parent function that will wait for the child to finish. Child process will be calling the exe function to execute the command in a new builtin
{
	int	i;

	g_ms->pid = fork();
	ft_signal_pip();
	if (g_ms->pid < 0)
		ft_error("Forking failed");
	if (g_ms->pid == 0)
	{
		g_ms->pip[0] = dup(STDIN);
		g_ms->pip[1] = dup(STDOUT);
		ft_start_piping(fd, order);
		ft_close_child(fd, order - 1, order);
		exit(ft_exe(node, venv));
	}
	else
	{
		ft_close_parent(fd, order);
		ft_parent(&i, g_ms->pid);
	}
	return (ft_check_status(i));
}
