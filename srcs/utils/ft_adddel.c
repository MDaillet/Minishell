/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adddel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:10:19 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/05 13:41:04 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_del_one_char(char **str, int pos) // Remove one char at the position pos
{
	char *rtn;
	int	i;

	rtn = 0;
	i = ft_strlen((*str));
	if (i <= 0 || pos < 1)
		return (0);
	if (!(ft_malloc(&rtn, sizeof(char) * i)))
		return (0);
	if (pos >= 1)
		ft_memcpy(rtn, (*str), pos - 1);
	ft_memcpy(rtn + pos - 1, (*str) + pos, i - pos);
	ft_free((*str));
	(*str) = 0;
	rtn[i - 1] = 0;
	return (rtn);
}

char *ft_add_one_char(char **str, int pos, char c) // Add one char at the position pos
{
	char *rtn;
	int	i;
	int	ret;

	i = ft_strlen((*str));
	pos--;
	ret = ft_malloc(&rtn, sizeof(char) * (i + 2));
	if (!ret)
		return(0);
	if ((*str))
		ft_memcpy(rtn, (*str), pos);
	rtn[pos] = c;
	ft_memcpy(rtn + pos + 1, (*str) + pos, i - pos);	
	ft_free((*str));
	(*str) = 0;
	rtn[i + 1] = 0;
	return (rtn);
}
