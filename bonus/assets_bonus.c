/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:27:22 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/18 15:23:48 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

bool	handle_dup(int input, int output)
{
	if (dup2(input, STDIN_FILENO) < 0)
		return (false);
	if (dup2(output, STDOUT_FILENO) < 0)
		return (false);
	return (true);
}

void	ft_close(int *fd)
{
	if (*fd > 0)
	{
		close(*fd);
		*fd = -1;
	}
}

void	ft_error(t_ppx *ppx, char *message)
{
	int	i;

	ft_putendl_fd(message, 2);
	if (!ppx)
		exit(1);
	if (ppx->pids)
		free(ppx->pids);
	if (ppx->infile > 0)
		ft_close(&ppx->infile);
	if (ppx->outfile > 0)
		ft_close(&ppx->outfile);
	i = 0;
	if (!ppx->pipes)
		exit(1);
	while (i < ppx->nb_pipes)
	{
		ft_close(&ppx->pipes[i].fds[0]);
		ft_close(&ppx->pipes[i].fds[1]);
		i++;
	}
	free(ppx->pipes);
	exit(1);
}

void	close_all_fds(t_ppx *ppx)
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
