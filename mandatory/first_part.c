/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:52:07 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/07 16:27:33 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_part_2(char **av, char **env, int *fds, int fd)
{
	char	**cmd;
	char	cmd_path[50];

	cmd = get_command_array(av[2]);
	if (!cmd)
	{
		close(fds[1]);
		close(fd);
		ft_exit(MALLOC_FAILED, 7);
	}
	if (!verify_and_get_command_path(cmd[0], env, cmd_path))
	{
		close(fds[1]);
		close(fd);
		ft_exit(INV_CMD, 8);
	}
	execve(cmd_path, cmd, NULL);
	free_splited_array(cmd);
}

void	first_part(char **av, char **env, int *fds)
{
	int	fd;
	int	dup_ret;

	close(fds[0]);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		close(fds[1]);
		ft_exit(ERR_OP_FILE, 4);
	}
	dup_ret = dup2(fd, STDIN_FILENO);
	if (dup_ret < 0)
	{
		close(4);
		close(fds[1]);
		ft_exit(DUP_FAIL, 5);
	}
	dup_ret = dup2(fds[1], STDOUT_FILENO);
	if (dup_ret < 0)
	{
		close(fd);
		close(fds[1]);
		ft_exit(DUP_FAIL, 6);
	}
	first_part_2(av, env, fds, fd);
}
