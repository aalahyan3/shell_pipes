/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:09:54 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/19 16:07:27 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(int *fd)
{
	if (*fd > 0)
	{
		close(*fd);
		*fd = -1;
	}
}

void	ft_error(t_ppx *ppx, char *message, int status)
{
	ft_close(&ppx->fds[0]);
	ft_close(&ppx->fds[1]);
	ft_close(&ppx->infile_fd);
	ft_close(&ppx->outfile_fd);
	ft_putstr_fd("pipex: ", 2);
	ft_putendl_fd(message, 2);
	exit(status);
}
