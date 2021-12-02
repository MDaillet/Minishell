/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:32:02 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/07 16:18:27 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_putchr(int c) // Custom putchar to work with tputs
{
	write(1, &c, 1);
	return (0);
}

void	ft_left(int *pos) // Move the cursor to the left. Will never be called if we are already at the leftiest position
{
	char *s;

	s = tgetstr("le", NULL);
	tputs(s, 1, ft_putchr);
	(*pos) -= 1;
}

void    ft_right(int *pos) // Same but to the right. Will never be called if we are already at the rightiest position
{
	char *s;

	s = tgetstr("nd", NULL);
    tputs(s, 1, ft_putchr);
    (*pos) += 1;
}

void	ft_up(int *pos, int *len) // Call the history list to get the previous input
{
	int	length;
	char *s;
	
	s = tgetstr("dl", NULL);
	length = ft_strlen(g_ms->history->str);
	if (!g_ms->history)
		return ;
	tputs(s, 1, ft_putchr);
	ft_prompt();
	ft_putstr_fd(g_ms->history->str, 1);
	ft_free(g_ms->input);

	g_ms->input = ft_strdup2(g_ms->history->str, length);
	g_ms->history = g_ms->history->next;
	(*len) = length;
	(*pos) = length;
}

void	ft_down(int *pos, int *len) // Same but for down movement.
{
	int	length;
	char *s;
	
	s = tgetstr("dl", NULL);
	length = ft_strlen(g_ms->history->str);
	if (!g_ms->history)
		return ;
	tputs(s, 1, ft_putchr);
	ft_prompt();
	ft_putstr_fd(g_ms->history->pre->str, 1);
	free(g_ms->input);
	g_ms->input = ft_strdup2(g_ms->history->str, length);
	g_ms->history = g_ms->history->pre;
	(*len) = length;
	(*pos) = length;
}
