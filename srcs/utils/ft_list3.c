/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:04:47 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/06 10:39:18 by mdaillet         ###   ########.fr       */
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
