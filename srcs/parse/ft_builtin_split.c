/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:09:59 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/10 21:22:51 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_space(t_builtin *node) // Add a blank node beetween every other node
{
	t_list	*t1;
	t_list	*t2;
	char	*s;

	if (!(node->cmd) || !node)
		return ;
	t1 = node->cmd;
	while (t1)
	{
		if (t1->str && !ft_strncmp(t1->str, " ", 1) && 
			t1->next && !ft_strncmp(t1->next->str, " ", 1))
		{
			s = ft_strdup2(" ", 1);
			t2 = ft_listnew(s, 0);
			ft_listadd_back(&t1, &t2);
		}
		t1 = t1->next;
	}
}

void	ft_remove_space(t_builtin *node) // Iterate through the command list and remove the last node if its just a space
{
	t_list	*t1;
	t_list	*t2;
	t_list	*first;

	if (!node->cmd || !node)
		return ;
	first = 0;
	t1 = node->cmd;
	while (t1)
	{
		t2 = t1->next;
		if (!(t1->next) && ft_strncmp(t1->str, " ", 1))
		{
			ft_listdelone(&t1);
			break ;
		}
		else
			first = t1;
		t1 = t2;
	}
	node->cmd = ft_gotofirst(first);
}

void	ft_remove_space2(t_builtin *node) // Iterate through the node and remove all the space nodes
{
	t_list	*t1;
	t_list	*t2;

	if (!node)
		return ;
	t1 = node->cmd;
	while (t1)
	{
		t2 = t1->next;
		if (ft_strncmp(t1->str, " ", 1))
			ft_listdelone(&t1);
		t1 = t2;
	}
}

void	ft_remove_space3(t_builtin *node) // Iterate through the command list and remove the 2 last nodes if its just a space and a null (ENV replacement)
{
	t_list	*t1;
	t_builtin *t2;

	if (!node->cmd || !node)
		return ;
	t2 = node;
	while (t2)
	{
		t1 = t2->cmd;
		while (t1->next)
			t1 = t1->next;
		if (t1 && t1->pre)
		{
			if (t1->str[0] == 0 && ft_strncmp(t1->pre->str, " ", 1))
			{
				t1 = t1->pre;
				ft_listdelone(&t1);
			}
		}
		t2 = t2->next;
	}
}

void	ft_builtin_split(t_builtin	*node, char *s) // Here we are simply splitting our big ass cmd list in our first node builtin to create multiple nodes, one by cmd separated by ; or |
{
	t_list	*tl;
	t_builtin	*tn;
	t_builtin	*new;
	
	if (!node->cmd || !node)
		return ;
	tn = node;
	tl = node->cmd;
	while (tl)
	{
		if (ft_strchr(s, *(tl->str)) && (tl->str))
		{
			new = ft_build_and_save2(tl);
			tn->next = new;
			new->pre = tn;
			if (tl->pre)
			{
				tl->pre->next = 0;
				tl->pre = 0;
			}
			tn = new;
		}
		tl = tl->next;
	}
}
