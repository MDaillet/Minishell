/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:49:13 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/16 12:04:48 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_trad(long long n)
{
	return ((int)(n % 256));
}

int	ft_cmd_exit(t_builtin *node) // Exit with the right code and returns an error if the exit code isnt num or if there is too much args
{
	t_list	*l;
	t_list	*t;
	int		i;

	/*while (node)
	{
		while (node->cmd)
		{
			printf("SIZE -> %ld", sizeof(node->cmd));
			printf("node->cmd = %s\n", node->cmd->str);
			node->cmd = node->cmd->next;
		}
		node = node->next;
	}
	*/
	g_ms->history_count++;
	while (g_ms->history_count--)
	{
		t = g_ms->first->next;
		ft_listdelone(&g_ms->first);
		g_ms->first = t;
	}
	ft_freelist(&g_ms->venv);
	l = node->cmd;
	if (!l->next)
	{
		ft_putstr_fd("exit", 2);
		ft_freebuilt(&node);
		exit(g_ms->status);
	}
	l = l->next;
	if (l->next && !l->next->next)
	{
		if (ft_isnum(l->next->str) == SUCCESS)
		{
			i = ft_trad(ft_atoi(l->next->str));
			ft_freebuilt(&node);
			exit(i);
		}
		else
		{
			ft_putstr_fd("minish: exit: ", 2);
			ft_putstr_fd(l->next->str, 2);
			ft_putstr_fd(", numeric argument required\n", 2);
		}
		ft_freebuilt(&node);
		exit(255);
	}
	else
		ft_putstr_fd("exit\nminish: exit : too many arguments\n", 2);
	ft_freebuilt(&node);
	return (EXIT_FAILURE);
}

int	ft_close(int fd) // Closing the file descriptor fd
{
	if (fd > 1)
		return (close(fd));
	return (1);
}
