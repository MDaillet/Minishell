/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:40:21 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/08 10:59:44 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_malloc(void *target, int size)
{
	void		**pt;

	pt = (void **)target;
	*pt = malloc(size);
	if (*pt == NULLPTR)
		return (FALSE);
	return (1);
}

void	*ft_calloc(size_t v, size_t size)
{
	void	*p;
	unsigned char *c;
	size_t	i;

	i = 0;
	p = (void *)malloc(v * size);
	if (!p)
		ft_error("Error allocation memory");
	c = p;
	while (i++ < v * size)
		*c++ = 0;
	return (p);
}

char	*ft_strdup2(const char *s, int len)
{
	char *rtn;

	if (!(ft_malloc(&rtn, sizeof(char) * (len + 1))))
		return (0);
	ft_memcpy(rtn, s, len);
	rtn[len] = 0;
	return (rtn);
}
