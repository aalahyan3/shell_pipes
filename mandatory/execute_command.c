/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:30:00 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/19 16:01:24 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	do_dup(t_ppx *ppx, int i)
{
	int	in_fd;
	int	out_fd;

	if (i == 0)
	{
		in_fd = ppx->infile_fd;
		out_fd = ppx->fds[1];
		ft_close(&ppx->fds[0]);
	}
	else
	{
		in_fd = ppx->fds[0];
		out_fd = ppx->outfile_fd;
		ft_close(&ppx->fds[1]);
	}
	if (dup2(in_fd, STDIN_FILENO) < 0)
		ft_error(ppx, DUP_FAIL, 8);
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		ft_error(ppx, DUP_FAIL, 8);
	if (in_fd != STDIN_FILENO)
		ft_close(&in_fd);
	if (out_fd != STDIN_FILENO)
		ft_close(&out_fd);
}

void	execute_command(t_ppx *ppx, char *command, char **env, int i)
{
	char	*full_path;
	char	**args;

	do_dup(ppx, i);
	args = get_command_array(command);
	if (!args)
		ft_error(ppx, MALLOC_FAILED, 12);
	full_path = verify_and_get_command_path(args[0], env);
	if (!full_path)
	{
		free_splited_array(args);
		ft_error(ppx, INV_CMD, 127);
	}
	execve(full_path, args, NULL);
	free_splited_array(args);
	free(full_path);
	exit(127);
}
