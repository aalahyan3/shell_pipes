/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:10:03 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/19 15:42:46 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <stdio.h>

# define INV_ARGS "Invalid arguments: usage ./pipex infile cmd2 cmd2 outfile"
# define PIPE_FAIL "could not create a pipe!"
# define FORK_FAIL "could not create a child process!"
# define ERR_OP_FILE "Error opening file"
# define DUP_FAIL "dup2 failed"
# define INV_CMD "command not found!"
# define MALLOC_FAILED "malloc() failed at some point!"
# define ERR_OUTFILE "Error creating outfile!"

typedef struct s_ppx
{
	int	fds[2];
	int	infile_fd;
	int	outfile_fd;
}	t_ppx;

int		main(int ac, char **av, char **env);
void	ft_error(t_ppx *ppx, char *message, int status);
void	ft_close(int *fd);
char	**ft_split_pipex(char const *s);
char	**get_command_array(char *cmd);
char	*verify_and_get_command_path(char *cmd, char **env);
void	execute_command(t_ppx *ppx, char *command, char **env, int i);
#endif