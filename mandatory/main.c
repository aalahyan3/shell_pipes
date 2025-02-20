/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:05:21 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/19 16:06:41 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_ppx(t_ppx *ppx)
{
	ppx->fds[0] = -1;
	ppx->fds[1] = -1;
	ppx->infile_fd = -1;
	ppx->outfile_fd = -1;
}

static void	open_files(t_ppx *ppx, char *infile, char *outfile)
{
	ppx->infile_fd = open(infile, O_RDONLY);
	if (ppx->infile_fd < 0)
		ft_error(ppx, ERR_OP_FILE, 5);
	ppx->outfile_fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (ppx->outfile_fd < 0)
		ft_error(ppx, ERR_OUTFILE, 6);
}

static void	close_all_fds(t_ppx *ppx)
{
	ft_close(&ppx->fds[0]);
	ft_close(&ppx->fds[1]);
	ft_close(&ppx->infile_fd);
	ft_close(&ppx->outfile_fd);
}

int	main(int ac, char **av, char **env)
{
	t_ppx	ppx;
	int		i;
	int		pid[2];
	int		status;

	init_ppx(&ppx);
	if (ac != 5)
		ft_error(&ppx, INV_ARGS, 1);
	open_files(&ppx, av[1], av[4]);
	if (pipe(ppx.fds) < 0)
		ft_error(&ppx, PIPE_FAIL, 2);
	i = 0;
	while (i <= 1)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			ft_error(&ppx, FORK_FAIL, 3);
		if (pid[i] == 0)
			execute_command(&ppx, av[i + 2], env, i);
		i++;
	}
	close_all_fds(&ppx);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	return (WEXITSTATUS(status));
}
