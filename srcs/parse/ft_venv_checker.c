/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_venv_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:03:38 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/02 10:49:54 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_lenenv(char *s) // determine the lenght of the venv name
{
	int	i;

	i = 0;
	if (ft_isdigit((int)s[i]) || s[i] == '?')
	{
		if (s[i] == '?')
			return (-2);	
		return (-1);
	}
	while (s[i])
	{
		if (ft_envlist(s[i]) == ERROR || ft_strchr("\'\"><|;=?$ ", s[i]))
			return (i);
		i++;
	}
	return (i);
}

void	ft_skip_quotes(char *s, int *i) // skipping everything beetween the two simple quotes
{
	int j;

	j = 0;
	while (s[j] != '\'' && s[j])
		j++;
	if (s[j])
		*i = j;
	if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] != '\'' && s[*i])
			(*i)++;
	}
}

static char	*ft_strswap(t_list **list, char *old, char *new, int oldlen) //Change the old str so it includes the value of the venv called
{
	char *rtn;
	int	ret;
	int	newlen;

	ret = ft_malloc(&rtn, sizeof(char) * (ft_strlen((*list)->str) - oldlen
				+ ft_strlen(new))); //malloc for the right size of the new str
	if (!ret)
		return (0);
	newlen = ft_strlen(new);
	ft_memcpy(rtn, (*list)->str, old - (*list)->str);
	ft_memcpy(rtn + (old - (*list)->str), new, newlen);
	ft_memcpy(rtn + (old - (*list)->str) + newlen, old + oldlen + 1,
			ft_strlen(old + oldlen + 1));
	rtn[ft_strlen((*list)->str) - oldlen + newlen - 1] = 0;
	ft_free((*list)->str);
	ft_free(new);
	(*list)->str = rtn;
	(*list)->rev_flag = 1;
	return (rtn);
}

int	ft_replace_venv2(t_list *list, t_list *venv, int *i) // ' inhibit all characters so we skip them
{
	char *old;
	int	oldlen;
	char *new;
	
	ft_skip_quotes(list->str, i);
	old = ft_strchr(&(list->str[(*i)]), '$');
	if (old)
	{
		oldlen = ft_lenenv(old + 1); // +1 to remove the dollar sign
		if (oldlen == 0)
			return (ERROR);
		if (oldlen == -1)
			oldlen = 1;
		if (oldlen == -2)
		{
			new = ft_itoa(g_ms->status_prec);
			oldlen = 1;
		}
		else
			new = ft_getvenv(venv, old + 1, oldlen); // +1 to remove the dollar sign
		ft_strswap(&list, old, new, oldlen);
		return (SUCCESS);
	}
	else
		return (ERROR);
}

void	ft_replace_venv(t_list *list, t_list *venv) // The goal here is to replace the venv by their values when they are called by $
{
	int	i;

	while (list)
	{
		i = 0;
		while (list->str[i])
			if (ft_replace_venv2(list, venv, &i) == ERROR)
				break ;
		list = list->next;
	}
}
