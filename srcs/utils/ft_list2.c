/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:52:10 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/09 12:08:07 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_listadd_back(t_list **list, t_list **new) // Add new jus behind list
{
	if ((*new) == 0)
		return ;
	if ((*list) == 0)
	{
		(*list) = (*new);
		(*list)->pre = 0;
		(*list)->next = 0;
	}
	else
	{
		if ((*list)->next)
			(*list)->next->pre = (*new);
		(*new)->pre = (*list);
		(*new)->next = (*list)->next;
		(*list)->next = (*new);
	}
}

t_list	*ft_gotofirst(t_list *list) // Travels to the first node of that chain
{
	t_list	*t;

	if (!list)
		return (ft_listnew(ft_strdup2("", 0), 0));
	t = list;
	while (t && t->pre)
		t = t->pre;
	return (t);
}

void	ft_listdelone(t_list **list) // Remove that list
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
	(*list)->str = 0;
	(*list)->id = 0;
	(*list)->next = 0;
	(*list)->pre = 0;
	ft_free(*list);
	(*list) = 0;
}

char	**ft_ltoa(t_list *list) // Transform a linked chain into an array of strings
{
	char	**rtn;
	int	count;
	int	i;
	t_list	*t;

	i = 0;
	t = list;
	count = 0;
	while (t)
	{
		t = t->next;
		count++;
	}
	if(!(ft_malloc(&rtn, sizeof(char *) * (count + 1))))
		return (0);
	while (i < count)
	{
		rtn[i] = ft_strdup2(list->str, ft_strlen(list->str));
		list = list->next;
		i++;
	}
	rtn[i] = 0;
	return (rtn);
}

char	**ft_venvtoa(t_list *venv)
{
	int	i;
	int	count;
	char	**rtn;
	char	*tmp;
	
	count = ft_lstcount(venv);
	i = 0;
	if (!(ft_malloc(&rtn, sizeof(char *) * (1 + count))))
		return (0);
	while (i < count)
	{
		tmp = ft_strjoin(venv->id, "=");
		rtn[i] = ft_strjoin(tmp, venv->str);
		ft_free(tmp);
		venv = venv->next;
		i++;
	}
	rtn[i] = 0;
	return (rtn);
}
