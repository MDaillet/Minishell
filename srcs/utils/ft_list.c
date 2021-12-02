/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:38:53 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/10 17:44:12 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_listnew(char *str, char *id) //create a new list
{
	t_list	*rtn;

	if (!ft_malloc(&rtn, sizeof(t_list)))
		ft_error("Error allocation memory");
	rtn->str = str;
	rtn->id = id;
	rtn->rev_flag = 0;
	rtn->pre = 0;
	rtn->next = 0;
	return (rtn);
}

void	ft_listadd_front(t_list **list, t_list **new)  //add an existing entry just before list	
{
	if ((*new) == 0 && (*list) == 0)
		return ;
	if ((*list) != 0)
	{
			if (((*list)->pre))
				(*list)->pre->next = (*new);
			(*new)->pre = (*list)->pre;
			(*list)->pre = (*new);
			(*new)->next = (*list);
			(*list) = (*new);
	}
	else
	{
		(*new)->pre = (*new);
		(*new)->next = (*new);
		(*list) = (*new);
	}
}

void	ft_listadd_tail(t_list **list, t_list **new) //add an existing entry to the end of the symtab
{
	t_list *tmp;

	if ((*new) == 0)
		return ;
	if ((*list) != 0)
	{
		tmp = (*list);
		while (tmp && tmp->next)
			tmp = tmp->next;
		(*new)->pre = tmp;
		(*new)->next = tmp->next;
		tmp->next = (*new);
	}
	else
	{
		(*list) = (*new);
		(*list)->next = 0;
		(*list)->pre = 0;
		(*list)->str = (*new)->str;
		(*list)->id = (*new)->id;
		(*list)->rev_flag = (*new)->rev_flag;
	}
}

t_list *ft_list_save(t_list *list) // Save the entirety of the symtab and its content into rtn
{
	t_list	*rtn;
	t_list	*save;
	t_list	*new;

	save = list;
	rtn = 0;
	while (save)
	{
		new = 0;
		if (save->str)
			new = ft_listnew(ft_strdup2(save->str, ft_strlen(save->str)),
					ft_strdup2(save->id, ft_strlen(save->id)));
		else
			new = ft_listnew(0, ft_strdup2(save->id, ft_strlen(save->id)));
		if (!new)
			ft_error("Allocation memory problem");
		if (save->rev_flag)
			new->rev_flag = 1;
		ft_listadd_tail(&rtn, &new);
		save = save->next;
	}
	return (rtn);
}

void	ft_freelist(t_list **list) // We go through the list of nodes to remove them one by one
{
	t_list	*t;

	if (!list || !(*list))
		return ;
	t = (*list);
	while (list && (*list))
	{
		t = t->next;
		ft_listdelone(list);
		*list = t;
	}
	*list = 0;
}
