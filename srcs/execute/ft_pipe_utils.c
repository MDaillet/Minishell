/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:14:07 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/02 11:48:55 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pip_size(int **pipe) // Calculate how many pipe there is (one pipe is an array with 2 entrys, one in one out, fd[0] fd[1]; Here we have multiple pipes stocked in fd, do we have fd[0][0] fd[0][1] then fd[1][0] fd[1][1]...
{
	int	i;

	i = 0;
	if (!pipe)
		return (0);
	while (pipe[i])
		i++;
	return (i);
}

int	ft_pip_count(t_builtin *node) // Check for how many Pipe are the beginings of our big nodes
{
	int	i;
	t_builtin	*t;

	i = 0;
	t = node;
	if (t)
	{
		while (t->next && t->next->cmd->str[0] == '|')
		{
			i++;
			t = t->next;
		}
	}
	return (i);
}

int	**ft_pip_init(int size) // Initialize our pip variable and start piping
{
	int	i;
	int	**pipfd;

	i = 0;
	pipfd = (int **)malloc(sizeof(int *) * (size + 1));
	if (!pipfd)
		return (0);
	while (i < size)
	{
		pipfd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(pipfd[i]) == -1 || !pipfd[i])
			return (ft_pip_free(&pipfd, i));
		i++;
	}
	pipfd[i] = 0;
	return (pipfd);
}

int	**ft_pip_free(int ***pip, int size) // Free the mallocated pip variable
{
	int	i;

	i = 0;
	while (i < size)
	{
		free((*pip)[i]);
		i++;
	}
	free(*pip);
	return (0);
}

int	ft_check_status(int status)
{
	int	sig;
	if (status == CMD_NOT_FOUND)
		return (status);
	if (WIFEXITED(status)) // If the child ended normally return the child's exit code
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))// If the child has been terminated by a signal, returns this signal number + 128 ##
	{
		sig = WTERMSIG(status);
		return (sig + 128);
	}
	return (ERROR);
}
