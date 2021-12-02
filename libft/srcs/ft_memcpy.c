/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:41:00 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/08 12:11:51 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, int n)
{
	unsigned char		*s1;
	const unsigned char	*s2;
	int					i;

	i = 0;
	if ((!dst && !src) || n <= 0)
		return (0);
	s1 = dst;
	s2 = src;
	while (n-- > 0)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dst);
}
