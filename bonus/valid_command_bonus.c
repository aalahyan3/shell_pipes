/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:12:05 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/17 16:30:19 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*get_path_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

static char	*get_full_path(char *cmd, char *path)
{
	char	*full_path;
	char	*ptr;

	full_path = ft_strdup(path);
	if (!full_path)
		return (NULL);
	ptr = full_path;
	full_path = ft_strjoin(full_path, "/");
	free(ptr);
	if (!full_path)
		return (NULL);
	ptr = full_path;
	full_path = ft_strjoin(full_path, cmd);
	free(ptr);
	return (full_path);
}

static char	*verify_and_get_path(char *cmd, char **env)
{
	char	*path_env;
	char	**paths;
	char	*cmd_path;
	int		i;

	path_env = get_path_env(env);
	if (!path_env)
		return (false);
	path_env += 5;
	paths = ft_split(path_env, ':');
	if (!paths)
		return (false);
	i = 0;
	while (paths[i])
	{
		cmd_path = get_full_path(cmd, paths[i]);
		if (!cmd_path)
			return (free_splited_array(paths), NULL);
		if (access(cmd_path, X_OK) == 0)
			return (free_splited_array(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	free_splited_array(paths);
	return (false);
}

char	*verify_and_get_command_path(char *cmd, char **env)
{
	if (*cmd == '/' && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (*cmd == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (false);
	}
	if (*cmd == '/')
		return (false);
	return (verify_and_get_path(cmd, env));
}
