/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:00:36 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/13 17:28:26 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_pipes(t_ppx *ppx)
{
	int		i;
	bool	err;

	i = 0;
	err = false;
	while (i < ppx->nb_pipes)
	{
		ppx->pipes[i].fds[0] = -1;
		ppx->pipes[i].fds[1] = -1;
		if (pipe(ppx->pipes[i].fds) < 0)
			err = true;
		i++;
	}
	if (err)
		ft_error(ppx, PIPE_FAIL);
}

static void	open_files(t_ppx *ppx, char **av, int ac)
{
	ppx->infile = open(HERE_DOC, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (ppx->infile < 0)
		ft_error(ppx, ERR_OP_FILE);
	ppx->outfile = open(av[ac - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (ppx->outfile < 0)
		ft_error(ppx, ERR_OP_FILE);
}

static void	fill_tmp_file(t_ppx *ppx, char **av)
{
	char	*line;
	char	*limiter;
	size_t	len;

	limiter = ft_strjoin(av[2], "\n");
	if (!limiter)
	{
		unlink("here_doc");
		ft_error(ppx, MALLOC_FAILED);
	}
	len = ft_strlen(limiter) + 1;
	ft_putstr_fd(">", 1);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, limiter, len) != 0 && line)
	{
		ft_putstr_fd(line, ppx->infile);
		free(line);
		ft_putstr_fd(">", 1);
		line = get_next_line(STDIN_FILENO);
	}
	free(limiter);
}

static void	reset_offset(t_ppx *ppx)
{
	ft_close(&ppx->infile);
	ppx->infile = open(HERE_DOC, O_RDONLY);
	if (ppx->infile < 0)
	{
		unlink(HERE_DOC);
		ft_error(ppx, ERR_OP_FILE);
	}
}

void	here_doc(int ac, char **av, char **env)
{
	t_ppx	ppx;
	int		last_status;

	ppx.nb_pipes = ac - 5;
	ppx.in_fd = -1;
	ppx.out_fd = -1;
	ppx.outfile = -1;
	ppx.infile = -1;
	ppx.pipes = ft_calloc(ppx.nb_pipes, sizeof(struct s_pipe *));
	if (!ppx.pipes)
		ft_error(&ppx, MALLOC_FAILED);
	init_pipes(&ppx);
	open_files(&ppx, av, ac);
	fill_tmp_file(&ppx, av);
	reset_offset(&ppx);
	last_status = start_pipes(&ppx, av + 1, env);
	unlink(HERE_DOC);
	free(ppx.pipes);
	exit(WEXITSTATUS(last_status));
}
