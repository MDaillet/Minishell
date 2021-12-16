/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:00:49 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/15 17:32:02 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handler(int sig) // Handling signals in the maim process 
{
	g_ms->sig = sig;
	if (sig == SIGQUIT)
		signal(SIGQUIT, ft_handler);
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		ft_free(g_ms->input);
		ft_read_init(&g_ms->len, &g_ms->pos);
		ft_prompt();
		signal(SIGINT, ft_handler);
	}
}

void	ft_signal(void) // Receiving signals in the main process
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
}

void	ft_handler_pip(int sig) // Handling signals in the piping and forking process
{
	if (sig == SIGQUIT)
	{
		kill(g_ms->pid, SIGQUIT);
		signal(SIGQUIT, ft_handler);
	}
	if (sig == SIGINT)
	{
		kill(g_ms->pid, SIGINT);
		write(1, "\n", 1);
		signal(SIGINT, ft_handler);
	}
}

void	ft_signal_pip(void) // Receiving signals in the piping and forking process
{
	signal(SIGINT, ft_handler_pip);
	signal(SIGQUIT, ft_handler_pip);
}

void	ft_exit_checker(int i) // The CRL-D bash behavior of exiting
{
	t_list	*t;
	if (i == 4)
	{
		if (g_ms->input)
		{
			if (!*g_ms->input)
			{
				g_ms->history_count++;
				while (g_ms->history_count--)
				{
					t = g_ms->first->next;
					ft_listdelone(&g_ms->first);
					g_ms->first = t;
				}
				ft_freelist(&g_ms->venv);
				ft_free(g_ms->input);
				ft_putstr_fd("Exit", 2);
				exit(0);
			}
		}
	}
}
