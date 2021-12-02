/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:01:01 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/10 20:51:52 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cmd_echo(t_builtin *node) // The echo cmd
{
	t_list	*list;
	int	n_opt;

	n_opt = 0;
	list = node->cmd;
	if (list->next && ft_strncmp(list->next->str, " ", 1))
	{
		list = list->next->next;
		while (list->next && ft_strncmpms(list->str, "-", 1))
		{
			if (ft_strncmp(list->str, "-n", 2))
				n_opt = 1;
			list = list->next->next;
		}
		while (list)
		{
			if (list->next)
				if (list->next->str[0] == 0 && !list->next->next)
					break ;
			if (list->next && list->next->next)
				if (list->str[0] == 0 && list->rev_flag)
					list = list->next->next;
			ft_putstr_fd(list->str, 1);
			list = list->next;
		}
	}
	if (!n_opt)
		ft_putstr_fd("\n", 1);
	return (SUCCESS);
}
