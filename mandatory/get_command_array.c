/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:33:21 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/08 18:46:03 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	defernciate_command(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				if (str[i] == ' ')
					str[i] = '\x01';
				if (str[i] == '\t')
					str[i] = '\x02';
				i++;
			}
		}
		i++;
	}
}

static void	trim_single_quotes(char **arr)
{
	int		i;
	char	*new;

	i = 0;
	while (arr[i])
	{
		new = ft_strtrim(arr[i], "'");
		if (!new)
			return (free_splited_array(arr));
		free(arr[i]);
		arr[i] = new;
		i++;
	}
}

static void	redefernciate_command(char	**array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == '\x01')
				array[i][j] = ' ';
			else if (array[i][j] == '\x02')
				array[i][j] = '\t';
			j++;
		}
		i++;
	}
}

char	**get_command_array(char *cmd)
{
	char	**array;
	char	*str;
	int		i;
	int		j;

	defernciate_command(cmd);
	array = ft_split_pipex(cmd);
	if (!array)
		return (NULL);
	trim_single_quotes(array);
	if (!array)
		return (NULL);
	redefernciate_command(array);
	return (array);
}
