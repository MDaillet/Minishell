/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:28:31 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/08 12:12:55 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_builtin	*ft_build_and_save2(t_list *list) // Create a node named Builtin and save the list of token in the t_list cmd
{
	t_builtin	*rtn;

	if (!list)
		return (0);
	if (!ft_malloc(&rtn, sizeof(t_builtin)))
		return (0);
	rtn->cmd = (list);
	rtn->next = 0;
	rtn->pre = 0;
	return (rtn);
}

t_builtin	*ft_build_and_save(t_list *list) // Create a node named Builtin and save the list of token in the t_list cmd
{
	t_builtin	*rtn;

	if (!list)
		return (0);
	if (!ft_malloc(&rtn, sizeof(t_builtin)))
		return (0);
	rtn->cmd = ft_list_save(list);
	rtn->next = 0;
	rtn->pre = 0;
	return (rtn);
}

void	ft_freebuilt(t_builtin **node)
{
	t_builtin	*t1;

	if (node == 0 || (*node) == 0)
		return ;
	while (*node)
	{
		if ((*node)->next)
			t1 = (*node)->next;
		else
			t1 = 0;
		if ((*node)->cmd)
			ft_freelist(&((*node)->cmd));
		ft_free(*node);
		(*node) = t1;
	}
}
