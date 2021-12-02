/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:09:43 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/02 11:50:04 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_check_execfile(char *s) // Checks that the exe file is valid, and that we have the permission to use it
{
	struct stat stat_cmd;
	char	*cmd;

	if (!s)
		return (0);
	cmd = ft_strdup2(s, ft_strlen(s));
	if (!cmd)
		ft_error("Allocation memory error");
	if (stat(cmd, &stat_cmd) == -1)
		ft_error2(cmd, 0);
	else if (S_ISDIR(stat_cmd.st_mode))
		ft_error2(cmd, "is a directory");
	else if (!(S_IEXEC & stat_cmd.st_mode))
		ft_error2(cmd, "permission denied");
	else
		return (cmd);
	free(cmd);
	return (0);
}

static char	*ft_check_cmd(char *s) // Check if the cmd is in bin or usr/bin with the stat cmd
{
	struct stat	stat_cmd;
	char	*bin;
	char	*usrbin;

	if (!s)
		return (0);
	bin = ft_strjoin("/bin/", s);
	usrbin = ft_strjoin("/usr/bin/", s);
	if (!bin || !usrbin)
		ft_error("Allocation memory error");
	if (stat(bin, &stat_cmd) == -1)
	{
		free(bin);
		if (stat(usrbin, &stat_cmd) == -1)
		{
			free(usrbin);
			ft_error2(s, "command not found");
			g_ms->status = CMD_NOT_FOUND;
			return (0);
		}
		return (usrbin);
	}
	free(usrbin);
	return (bin);
}

static char **ft_modify(char **s) // Transform the str from node->cmd into a the Path we need if there is '~', and check if the paths are correct 
{
	char	*t;
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i][0] == '~')
		{
			t = ft_strjoin(getenv("HOME"), &s[i][1]);
			free(s[i]);
			s[i] = t;
		}
		i++;
	}
	t = s[0];
	if (ft_strchr1(t, '/'))
		s[0] = ft_check_execfile(t);
	else
		s[0] = ft_check_cmd(t);
	free(t);
	return (s);
}

static int	ft_init_execve(t_builtin *node, t_list *venv, char ***av,
		char ***cvenv) // Initialize  what we need to call the execve cmd, meaning, the fill path of the exefile, the arguments, and the venv as a **char
{
	char **tmp;

	ft_remove_space2(node);
	tmp = ft_ltoa(node->cmd);
	(*cvenv) = ft_venvtoa(venv);
	(*av) = ft_modify(tmp);
	ft_signal_pip();
	if (!(*av)[0])
		return (CMD_NOT_FOUND);
	return (SUCCESS);
}

int	ft_execve(t_builtin *node, t_list *venv)
{
	int	state;
	char	**av;
	char	**cvenv;

	state = ft_init_execve(node, venv, &av, &cvenv);
	if (state == SUCCESS)
	{
		g_ms->pid = fork();
		if (g_ms->pid < 0)
			ft_error("Forking error");
		else if (g_ms->pid == 0)
		{
			dup2(g_ms->pip[0], STDIN);
			if (execve(av[0], av, cvenv) < 0 && !g_ms->status)
				ft_error("Execve error");
		}
		else
		{
			dup2(g_ms->pip[1], STDOUT);
			ft_parent(&state, g_ms->pid);
		}
	}
	ft_freen(av, ft_strlen2(av));
	ft_freen(cvenv, ft_strlen2(cvenv));
	return (ft_check_status(state));
}
