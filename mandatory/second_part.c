/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:27:45 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/08 18:49:09 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_exit(int	*fds, int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	close(fds[0]);
	exit(WEXITSTATUS(status));
}

static bool	second_part_3(char **av, char **env)
{
	char	full_path[50];
	char	**cmd;

	cmd = get_command_array(av[3]);
	if (!cmd)
		return (false);
	if (!verify_and_get_command_path(cmd[0], env, full_path))
		return (free_splited_array(cmd), false);
	execve(full_path, cmd, NULL);
	return (true);
}

static void	second_part_2(char **av, char **env, int *fds)
{
	int	out_fd;
	int	dup_ret;

	out_fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		close(fds[0]);
		ft_exit(ERR_OUTFILE, 11);
	}
	dup_ret = dup2(out_fd, STDOUT_FILENO);
	if (dup_ret < 0)
	{
		close(fds[0]);
		close(out_fd);
		ft_exit(DUP_FAIL, 12);
	}
	if (!second_part_3(av, env))
	{
		close(fds[0]);
		close(out_fd);
		ft_exit(INV_CMD, 13);
	}
}

void	second_part(char **av, char **env, int *fds, int pid)
{
	int	status;
	int	dup_ret;
	int	pid2;

	waitpid(pid, &status, 0);
	close(fds[1]);
	dup_ret = dup2(fds[0], STDIN_FILENO);
	if (dup_ret < 0)
	{
		close(fds[0]);
		ft_exit(DUP_FAIL, 9);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		close(fds[0]);
		ft_exit(FORK_FAIL, 10);
	}
	if (pid2 == 0)
		second_part_2(av, env, fds);
	else
		handle_exit(fds, pid2);
}
