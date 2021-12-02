/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 12:02:33 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/03 17:18:43 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	size;
	unsigned int	i;

	if (s == 0)
		return (0);
	size = (unsigned int)ft_strlen(s);
	i = 0;
	if (size < start)
		return (ft_strdup(""));
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (0);
	while (i < len && start + i < size)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
