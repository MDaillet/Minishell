/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:26:20 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/01 18:52:30 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute(t_list *venv)
{
	t_builtin *nodes;
	t_list	*list;
	char	*separators;

	separators = "|;";
	list = ft_tokenize(g_ms->input);
	if (list == 0)
		return ;
	nodes = ft_build_and_save(list);
	ft_free(g_ms->input);
	ft_freelist(&list);
	ft_add_space(nodes);
	ft_builtin_split(nodes, separators);
	ft_remove_space(nodes);
	ft_manager(&venv, nodes);
	ft_freebuilt(&nodes);
}

void	ft_loop(t_list *venv)
{
	int ret;

	while (1)
	{
		ft_prompt();
		ft_signal();
		ft_term_init();
		ft_read();
		ft_reset();
		if (g_ms->input)
		{
			ret = ft_strlen(g_ms->input);
			if (!ret)
				ft_free(g_ms->input);
			else if (ft_check_input(g_ms->input) == SUCCESS)
				ft_execute(venv);
		}
	}
}

void	ft_init_all(void)
{
	g_ms->sig = -1;
	g_ms->pid = -1;
	g_ms->history = ft_listnew(0, 0);
	g_ms->history->pre = g_ms->history;
	g_ms->history->next = g_ms->history;
	g_ms->first = g_ms->history;
	g_ms->pip[0] = dup(0);
	g_ms->pip[1] = dup(1);
}

int main(int ac, char **av, char **env)
{
	t_list *venv;
	t_ms ms;
	
	g_ms = &ms;
	(void)ac;
	(void)av;
	venv = ft_init_env(env);
	g_ms->venv = venv;
	ft_init_all();
	ft_loop(venv);
	ft_freelist(&venv);
	ft_freelist(&g_ms->first);
	return (g_ms->status);
}
