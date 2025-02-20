/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:48:59 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/19 16:07:17 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	close_all_fds(t_ppx *ppx)
{
	int	i;

	if (ppx->infile > 0 && ppx->in_fd != ppx->infile)
		ft_close(&ppx->infile);
	if (ppx->outfile > 0 && ppx->out_fd != ppx->outfile)
		ft_close(&ppx->outfile);
	i = 0;
	while (i < ppx->nb_pipes)
	{
		if (ppx->pipes[i].fds[0] > 0 && ppx->pipes[i].fds[0] != ppx->in_fd)
			ft_close(&ppx->pipes[i].fds[0]);
		if (ppx->pipes[i].fds[1] > 0 && ppx->pipes[i].fds[1] != ppx->out_fd)
			ft_close(&ppx->pipes[i].fds[1]);
		i++;
	}
}

static void	do_dup(t_ppx *ppx)
{
	if (dup2(ppx->in_fd, STDIN_FILENO) < 0)
		ft_error(ppx, DUP_FAIL);
	if (dup2(ppx->out_fd, STDOUT_FILENO) < 0)
		ft_error(ppx, DUP_FAIL);
	close(ppx->in_fd);
	close(ppx->out_fd);
}

static void	run_command(t_ppx *ppx, char **av, char **env, int index)
{
	char	**cmd;
	char	*full_path;

	close_all_fds(ppx);
	do_dup(ppx);
	cmd = get_command_array(av[index + 2]);
	if (!cmd)
		ft_error(ppx, MALLOC_FAILED);
	full_path = verify_and_get_command_path(cmd[0], env);
	if (!full_path)
	{
		free_splited_array(cmd);
		ft_error(ppx, INV_CMD);
	}
	execve(full_path, cmd, NULL);
	free_splited_array(cmd);
	free(full_path);
	exit(127);
}

static void	controle_file_traffic(t_ppx *ppx, int i)
{
	if (i == 0)
	{
		ppx->in_fd = ppx->infile;
		ppx->out_fd = ppx->pipes[i].fds[1];
	}
	else if (i == ppx->nb_pipes)
	{
		ppx->in_fd = ppx->pipes[i - 1].fds[0];
		ppx->out_fd = ppx->outfile;
	}
	else
	{
		ppx->in_fd = ppx->pipes[i - 1].fds[0];
		ppx->out_fd = ppx->pipes[i].fds[1];
	}
}

int	start_pipes(t_ppx *ppx, char **av, char **env)
{
	int	i;
	int	status;

	i = 0;
	while (i <= ppx->nb_pipes)
	{
		controle_file_traffic(ppx, i);
		ppx->pids[i] = fork();
		if (ppx->pids[i] == 0)
			run_command(ppx, av, env, i);
		i++;
		ft_close(&ppx->in_fd);
		ft_close(&ppx->out_fd);
	}
	i = 0;
	while (i <= ppx->nb_pipes)
		waitpid(ppx->pids[i++], &status, 0);
	return (status);
}
