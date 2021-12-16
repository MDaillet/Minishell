/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:04:47 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/15 16:21:31 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lstcount(t_list	*list)
{
	int	count;
	t_list	*t;

	count = 0;
	t = list;
	while (t)
	{
		t = t->next;
		count++;
	}
	return (count);
}

void	ft_listdelone2(t_list **list) // Remove that list
{
	if (list == 0 || (*list) == 0)
		return ;
	if ((*list)->next)
		(*list)->next->pre = (*list)->pre;
	if ((*list)->pre)
		(*list)->pre->next = (*list)->next;
	if ((*list)->id)
		ft_free((*list)->id);
	if ((*list)->str)
		ft_free((*list)->str);
	(*list)->next = 0;
	(*list)->pre = 0;
	(*list)->str = 0;
	(*list)->id = 0;
	(*list) = 0;
	ft_free(*list);
}

void	ft_freehistory(t_list **list) // We go through the list of nodes to remove them one by one
{
	t_list	*t;

	if (!list || !(*list))
		return ;
	t = (*list);
	while (list && (*list))
	{
		t = t->next;
		ft_listdelone2(list);
		*list = t;
	}
	*list = 0;
}
