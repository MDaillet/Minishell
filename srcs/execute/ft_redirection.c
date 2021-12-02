/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:08:00 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/01 11:09:01 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_redi(t_builtin	*node, int n) // If redi without enough argument its an error
{
	t_list	*t;

	t = node->cmd;
	while (n--)
	{
		if (t->next)
			t = t->next;
		else
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_redirection1(t_builtin *node, char c, int *fd) // > or >> Redirection wich will trunc or append smthg in a file opened here and save with dup2. If problem with the destination file, the right error is called
{
	int	ret;
	t_list	*list;

	ret = 0;
	list = node->cmd;
	if (!list->next || !list->next->next)
	{
		g_ms->status = INVALID_ARG;
		ft_errorsyntax('>');
		return (INVALID_ARG);
	}
	list = list->next->next; // next->next because of spaces beetween node <3
	if (c == 'T')
		ret = open(list->str, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else if (c == 'A')
		ret = open(list->str, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (ret < 0)
	{
		ft_error2(list->str, "No such file or directory");
		return (ERROR);
	}
	dup2(ret, fd[1]);
	ft_close(ret);
	fd[1] = ret;
	return (SUCCESS);
}

int	ft_redirection2(t_builtin *node) // Reads from the arg in the next node and save it in the global
{
	int	ret;
	t_list	*list;

	ret = 0;
	if (ft_check_redi(node, 2) == ERROR)
	{
		ft_errorsyntax('<');
		return (ERROR);
	}
	list = node->cmd->next->next;
	ret = open(list->str,  O_RDONLY, S_IRWXU);
	if (ret < 0)
	{
		 ft_error2(list->str, "No such file or directory");
		 return (ERROR);
	}
	dup2(ret, g_ms->pip[0]);
	ft_close(ret);
	return (SUCCESS);
}

int ft_redirection3(t_builtin *node, int *fd) // When use << cmd, the terminal will print newlines where you will be able enter arguments as much as you want, until you write the cmd name again called "etiquette". It will write the new arguments in the pipe g_ms->pip
{
	t_list *list;
	char *s;

	if (pipe(g_ms->pip) < 0)
		ft_error("<< Redirection  : pipe error");
	if (ft_check_redi(node, 2) == ERROR)
		return (ERROR);
	list = node->cmd->next->next;
	while (get_next_line(fd[0], &s) >= 0)
	{
		if (ft_strncmp(s, list->str, ft_strlen(list->str)))
		{
			ft_close(g_ms->pip[1]);
			ft_free(s);
			return (SUCCESS);
		}
		ft_putstr_fd(s, g_ms->pip[1]);
		ft_putstr_fd("\n", g_ms->pip[1]);
		ft_free(s);
	}
	return (SUCCESS);
}
