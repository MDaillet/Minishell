/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:47:04 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/09 21:44:11 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_errorsyntax(char c)
{
	char *s;

	ft_putstr_fd("Minishell : syntax error near unexpected token \'", 2);
	if (c)
	{
		if (c == '<' || c == '>')
			s = ft_strdup2("newline", 7);
		else
			s = ft_strdup2(&c, 1);
		ft_putstr_fd(s, 2);
		ft_free(s);
	}
	ft_putstr_fd("\'\n", 2);
}

void	ft_error2(char *name, char *msg)
{
	ft_putstr_fd("Minishell : ", 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" : ", 2);
	}
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
}

void	ft_error(char *str)
{
	ft_error2(0, str);
	exit(EXIT_FAILURE);
}
