/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:10:03 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/08 17:54:46 by aalahyan         ###   ########.fr       */
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

int		main(int ac, char **av, char **env);
void	ft_exit(char *message, int status);
void	first_part(char **av, char **env, int *fds);
bool	verify_and_get_command_path(char *cmd, char **env, char *full_path);
void	second_part(char **av, char **env, int *fds, int pid);
char	**get_command_array(char *cmd);
char	**ft_split_pipex(char const *s);
#endif