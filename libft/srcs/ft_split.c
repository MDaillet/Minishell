/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:46:17 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/09 16:21:40 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*free_malloc(char **dest, int i)
{
	while (i >= 0)
		free(dest[i--]);
	free(dest);
	return (0);
}

static char	**do_malloc(void)
{
	char	**tmp;

	tmp = (char **)malloc(sizeof(char *) * (3));
	if (!tmp)
		return (0);
	return (tmp);
}

char	**ft_split(char const *s, char c)
{
	char		**tmp;
	size_t		i;

	tmp = do_malloc();
	if (!tmp)
		return (0);
	i = 0;
	while (s[i] != c)
		i++;
	tmp[0] = ft_strdup2(s, i);
	if (!tmp[0])
		return (free_malloc(tmp, 1));
	tmp[1] = ft_substr(s, i + 1, ft_strlen(s) - i);
	if (!tmp[1])
		return (free_malloc(tmp, --i));
	return (tmp);
}
