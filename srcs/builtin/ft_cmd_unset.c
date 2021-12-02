/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:20:51 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/09 16:31:39 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cmd_unset(t_builtin *node, t_list **venv)
{
	t_list *l;

	if (ft_check_redi(node, 1) == ERROR)
		return (ERROR);
	if (!ft_strncmpms(node->cmd->next->str, " ", 1))
		return (ERROR);
	l = node->cmd->next->next;
	while (l)
	{
		if (!ft_strncmpms(l->str, " ", 1))
			ft_rem_env(venv, l->str);
		l = l->next;
	}
	return (SUCCESS);
}
