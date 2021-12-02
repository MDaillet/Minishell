/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:40:26 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/02 11:24:10 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parent(int *status, pid_t pid) // Wait for the child process to be done the right way
{
	waitpid(pid, status, WUNTRACED); // WUNTRACED means come back if a child is stuck
	while (!WIFEXITED(*status) && !WIFSIGNALED(*status)) // WIFEXITED returns true if the child ended normally, WIFESIGNALED returns true if the child has been terminated by a signal
		waitpid(pid, status, WUNTRACED);
}
