/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:09:10 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/08 18:46:13 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(char *message, int status)
{
	ft_putstr_fd("pipex :", 2);
	ft_putendl_fd(message, 2);
	exit(status);
}

static void	check_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_exit("Error opening file!", 1);
	close(fd);
}

void	leaks(void)
{
	system("lsof -c pipex");
}

int	main(int ac, char **av, char **env)
{
	int	fds[2];
	int	pid;
	int	pipe_ret;

	if (ac != 5)
		ft_exit(INV_ARGS, 2);
	check_infile(av[1]);
	pipe_ret = pipe(fds);
	if (pipe_ret < 0)
		ft_exit(PIPE_FAIL, 3);
	pid = fork();
	if (pid < 0)
	{
		close(fds[0]);
		close(fds[1]);
		ft_exit(FORK_FAIL, 3);
	}
	if (pid == 0)
		first_part(av, env, fds);
	else
		second_part(av, env, fds, pid);
}
