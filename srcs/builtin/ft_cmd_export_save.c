/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:12:27 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/06 14:58:41 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_switch(t_list *t1, t_list *t2) // Switch the id and str beetween t1 and t2
{
	char *t;

	t = t1->str;
	t1->str = t2->str;
	t2->str = t;
	t = t1->id;
	t1->id = t2->id;
	t2->id = t;
}

static void	ft_append_env(t_list *list, char **t)
{
	char	*cut;
	char	*plus;
	char	*old;

	if (t[0][ft_strlen(t[0]) - 1] != '+')
		return ;
	cut = ft_del_one_char(&t[0], ft_strlen(t[0]));
	old = ft_getvenv(list, cut, ft_strlen(cut));
	plus = t[1];
	t[0] = cut;
	t[1] = ft_strjoin(old, plus);
	free(plus);
	free(old);
}

static int	ft_show_sorted_env(t_list *venv) // Sort the venv and print it
{
	int	i;
	t_list	*save;
	t_list	*t1;
	t_list	*t2;
	
	i = 0;
	save = ft_list_save(venv);
	while (i < ft_lstcount(save))
	{
		t1 = save;
		t2 = t1->next;
		while (t2)
		{
			if (ft_strncmpms2(t1->id, t2->id, ft_strlen(t1->id)) > 0)
				ft_switch(t1, t2);
			t1 = t1->next;
			t2 = t2->next;
		}
		i++;
	}
	ft_show_env2(save, "declare -x");
	ft_freelist(&save);
	return (SUCCESS);
}

char	**ft_equal_mana(char *s) // Split the cmd after export in a double array to have the variable name and its value in tmp[0] and tmp[1]
{
	char	**tmp;
	char	*subs;

	tmp = (char **)malloc(sizeof(char *) * 3);
	if (!tmp)
		ft_error("Allocation memory error");
	subs = ft_strchr(s, '=');
	if (subs)
	{
		tmp[0] = ft_strdup2(s, subs - s);
		tmp[1] = ft_strdup2(subs + 1, ft_strlen(subs + 1));
		if (!tmp[0] || !tmp[1])
			ft_error("Allocation memory error");
	}
	else
	{
		tmp[0] = ft_strdup2(s, ft_strlen(s));
		if (!tmp[0])
			ft_error("Allocation memory error");
		tmp[1] = 0;
	}
	tmp[2] = 0;
	return (tmp);
}

int	ft_cmd_export(t_builtin *node, t_list **venv) // Adds a new env variable to venv
{
	t_list	*order;
	char	**t;
	int	ret;

	if (!node->cmd->next)
		return (ft_show_sorted_env(*venv));
	if (!ft_strncmp(node->cmd->next->str, " ", 1))
		return (ERROR);
	order = node->cmd->next->next;
	if (!order || !order->str)
		return (ERROR);
	t = ft_equal_mana(order->str);
	ft_append_env(*venv, t);
	ret = ft_add_venv(venv, t[0], t[1]);
	if (ret == ERROR)
	{
		ft_error2(order->str, "not a valid identifier");
		ft_freen(t, 2);
	}
	else
		ft_free(t);
	return (ret);
}
