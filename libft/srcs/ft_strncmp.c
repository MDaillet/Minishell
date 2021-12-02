/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:48:30 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/08 19:46:06 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;
	unsigned char	*c1;
	unsigned char	*c2;

	if (n == 0 || !s1 || !s2)
		return (0);
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	i = 0;
	if ((int)ft_strlen(s1) != n)
		return (0);
	while (i < n)
	{
		if (c1[i] != c2[i])
			return (0);
		i++;
	}
	return (1);
}
