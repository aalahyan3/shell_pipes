/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:10:03 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/18 18:07:50 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdbool.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <stdio.h>

# define INV_ARGS "Invalid arguments: usage ./pipex infile \
c1 c2 ... cn outfile (one pipe minimum)"
# define PIPE_FAIL "could not create a pipe!"
# define FORK_FAIL "could not create a child process!"
# define ERR_OP_FILE "Error opening file"
# define DUP_FAIL "dup2 failed"
# define INV_CMD "command not found!"
# define MALLOC_FAILED "malloc() failed at some point!"
# define ERR_OUTFILE "Error creating outfile!"
# define HERE_DOC "/tmp/here_doc"

struct s_pipe
{
	int	fds[2];
};
typedef struct s_ppx
{
	struct s_pipe	*pipes;
	int				infile;
	int				outfile;
	int				in_fd;
	int				out_fd;
	int				nb_pipes;
	int				*pids;
}	t_ppx;

int		main(int ac, char **av, char **env);
char	**ft_split_pipex(char const *s);
char	**get_command_array(char *cmd);
char	*verify_and_get_command_path(char *cmd, char **env);
void	multiple_pipes(int ac, char **av, char **env);
void	ft_error(t_ppx *ppx, char *message);
void	ft_close(int *fd);
bool	handle_dup(int input, int output);
int		start_pipes(t_ppx *ppx, char **av, char **env);
void	here_doc(int ac, char **av, char **env);
#endif