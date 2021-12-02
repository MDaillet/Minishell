/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_q.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:39:25 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/05 18:27:10 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_remove_q2(char **s) // If str is empty and is just "" or '' we skip and save this shit
{
	if (ft_strncmp(*s, "\"\"", 2) || ft_strncmp(*s, "\'\'", 2))
	{
		ft_free(*s);
		*s = ft_strdup2("", 1);
		return (1);
	}
	return (0);
}

void	ft_remove_q(t_list *list) // Remove the quotes from the strings contained in the list we have
{
	int	t;
	int	n;
	char	c;

	t = 0;
	while (list)
	{
		n = 0;
		while (list->str && list->str[n])
		{
			if (ft_remove_q2(&(list->str)))
				break;
			else if (ft_strchr("\'\"", list->str[n]))
			{
				c = list->str[n];
				list->str = ft_del_one_char(&list->str, 1 + n);
				t = ft_strchr(&list->str[n], c) - list->str;
				list->str = ft_del_one_char(&list->str, 1 + t);
				n = t;
			}
			else
				n += 1;
		}
		list = list->next;
	}
}
