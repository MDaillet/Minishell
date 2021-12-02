/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:15:35 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/23 15:42:34 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_backs(int *pos, int *len) // Remove one character from the propmt and the input str
{
	tputs(tgetstr("le", NULL), 1, ft_putchr);
	tputs(tgetstr("dm", NULL), 1, ft_putchr);
	tputs(tgetstr("dc", NULL), 1, ft_putchr);
	tputs(tgetstr("ed", NULL), 1, ft_putchr);
	g_ms->input = ft_del_one_char(&g_ms->input, *pos);
	(*pos) -= 1;
	(*len) -= 1;
}

void	ft_history_add(void) // Save the input line and add it into the history
{
	t_list *tmp;
	char *s;

	ft_putstr_fd("\n", 2);
	if (!g_ms->input)
		return ;
	s = ft_strdup2(g_ms->input, ft_strlen(g_ms->input));
	tmp = ft_listnew(s, 0);
	ft_listadd_front(&g_ms->first, &tmp);
	g_ms->history = tmp;
}

void	ft_prompt(void) // Print a prompt containing the current directory
{
	char *prompt;

	prompt = "\e[0;32mMinishell\e[0m";
	ft_putstr_fd(prompt, 2);
	ft_putstr_fd(" $> ", 2);
}

void	ft_term_init(void) // Terminal intialization (tgetent mandatory for the termios use)
{
	int ret;
	char *term_type;

	term_type = getenv("TERM");
	if (!term_type)
		term_type = "xterm";
	ret = tgetent(NULL, term_type);
	if (ret < 1)
		return ;
	tcgetattr(0, &g_ms->save);
	tcgetattr(0, &g_ms->term);
	g_ms->term.c_lflag &= ~ICANON;
	g_ms->term.c_lflag &= ~ECHO;
	g_ms->term.c_cc[VMIN] = 1;
	g_ms->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_ms->term);
}

void	ft_reset(void) // Reseting the terminal
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_ms->save);
}
