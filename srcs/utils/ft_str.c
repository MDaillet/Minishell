/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:09:35 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/09 15:54:40 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isnum(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ERROR);
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] != 0)
		return (ERROR);
	return (SUCCESS);
}

int	ft_strncmpms(const char *c1, const char *c2, int n)
{
	int	i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)c1;
	s2 = (unsigned char *)c2;
	i = 0;
	n = ft_strlen(c2);
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strncmpms2(const char *c1, const char *c2, size_t n)
{
	size_t	i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)c1;
	s2 = (unsigned char *)c2;
	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	if (i < n)
	{
		if (s1[i] != '\0')
			return (1);
		if (s2[i] != '\0')
			return (-1);
	}
	return (0);
}

char	*ft_strchr1(const char *s, char c)
{
	while (*s != c)
	{
		if (*s == 0)
			return (0);
		s++;
	}
	return ((char *)s);
}
