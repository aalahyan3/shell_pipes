/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:56:34 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/13 17:33:54 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	open_files(char *infile, char *outfile, t_ppx *ppx)
{
	ppx->in_fd = -1;
	ppx->out_fd = -1;
	ppx->outfile = -1;
	ppx->infile = -1;
	ppx->infile = open(infile, O_RDONLY);
	if (ppx->infile < 0)
		ft_error(ppx, ERR_OP_FILE);
	ppx->outfile = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0677);
	if (ppx->outfile < 0)
		ft_error(ppx, ERR_OP_FILE);
}

static void	init_pipes(t_ppx *ppx)
{
	int	i;

	i = 0;
	while (i < ppx->nb_pipes)
	{
		ppx->pipes[i].fds[0] = -1;
		ppx->pipes[i].fds[1] = -1;
		i++;
	}
}

static void	open_pipes(t_ppx *ppx)
{
	int	i;

	i = 0;
	while (i < ppx->nb_pipes)
	{
		if (pipe(ppx->pipes[i].fds) < 0)
			ft_error(ppx, PIPE_FAIL);
		i++;
	}
}

void	multiple_pipes(int ac, char **av, char **env)
{
	t_ppx	ppx;
	int		last_cmd_state;

	ppx.nb_pipes = ac - 4;
	ppx.pipes = ft_calloc(ppx.nb_pipes, sizeof(struct s_pipe *));
	if (!ppx.pipes)
		ft_error(&ppx, MALLOC_FAILED);
	init_pipes(&ppx);
	open_files(av[1], av[ac - 1], &ppx);
	open_pipes(&ppx);
	last_cmd_state = start_pipes(&ppx, av, env);
	free(ppx.pipes);
	exit(WEXITSTATUS(last_cmd_state));
}
