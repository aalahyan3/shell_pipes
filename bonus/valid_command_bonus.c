/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:12:05 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/08 20:47:45 by aalahyan         ###   ########.fr       */
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

static bool	verify_and_get_path(char *full_path, char *cmd, char **env)
{
	char	*path_env;
	char	**paths;
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
		ft_strlcpy(full_path, paths[i], 50);
		ft_strlcat(full_path, "/", 50);
		ft_strlcat(full_path, cmd, 50);
		if (access(full_path, X_OK) == 0)
			return (free_splited_array(paths), true);
		i++;
	}
	free_splited_array(paths);
	return (false);
}

bool	verify_and_get_command_path(char *cmd, char **env, char *full_path)
{
	char	*path_env;
	char	**paths;
	int		i;

	if (*cmd == '/' && access(cmd, X_OK) == 0)
		return (ft_strlcpy(full_path, cmd, 50), true);
	if (*cmd == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strlcpy(full_path, cmd, 50), true);
		else
			return (false);
	}
	if (*cmd == '/')
		return (false);
	return (verify_and_get_path(full_path, cmd, env));
}
