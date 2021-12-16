/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:39:08 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/14 18:07:53 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_envlist(char c) // A venv value is either a digit either an alpha either a _
{
	if (c == '_' || ft_isdigit(c) || ft_isalpha(c))
		return (SUCCESS);
	return (ERROR);
}

char	*ft_getvenv(t_list *venv, const char *var, int len) // Runs through the list and give the str in the node named after the var
{
	t_list *tmp;
	char *rtn;

	rtn = 0;
	tmp = venv;
	if (ft_strncmp("?", (char *)var, len))
		return (ft_itoa(g_ms->status));
	while (tmp)
	{
		if (ft_strncmp(tmp->id, (char *)var, len))
		{
			if (tmp->str)
				rtn = ft_strdup2(tmp->str, ft_strlen(tmp->str));
			break ;
		}
		tmp = tmp->next;
	}
	return (rtn);
}

int	ft_add_venv(t_list **venv, char *var, char *val) // Add a new venv and its value to the venv list;
{
	t_list *t;
	int	i;

	i = 0;
	if (!var || var[0] == 0 || var[0] == '%' || (var[0] >= '0' && var[0] <= '9'))
		return (ERROR);
	while (var[i])
	{
		if (ft_envlist(var[i]))
			return (ERROR);
		i++;
	}
	ft_rem_env(venv, var);
	t = ft_listnew(val, var);
	ft_listadd_tail(venv, &t);
	return (SUCCESS);
}

void	ft_rem_env(t_list **venv, char *var) // Remove the var venv from the venv list
{
	t_list	*t1;
	t_list	*t2;
	t_list	*t3;

	t1 = *venv;
	while (t1)
	{
		t2 = t1->next;
		if (ft_strncmp(t1->id, var, ft_strlen(var)))
			ft_listdelone(&t1);
		else
			t3 = t1;
		t1 = t2;
	}
	while (t3->pre)
		t3 = t3->pre;
	*venv = t3;
}

t_list *ft_init_env(char **env) // Creates a list of venv with id as their name and str as their value
{
	int	i;
	char	**strenv;
	t_list	*list;
	t_list	*temp;

	list = 0;
	i = 0;
	while (env[i])
	{
		strenv = ft_split(env[i], '=');
		if (!strenv)
			ft_error("malloc failed");
		if (!strenv[1])
			strenv[1] = ft_strdup2("", 0);
		temp = ft_listnew(strenv[1], strenv[0]);
		ft_listadd_tail(&list, &temp);
		ft_free(strenv);
		i++;
	}
	return (list);
}
