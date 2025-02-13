/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:56:26 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/08 20:47:35 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	get_size(char const *s)
{
	int	size;

	size = 0;
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		if (*s)
		{
			size++;
			s++;
		}
		while (*s && (*s != ' ' && *s != '\t'))
			s++;
	}
	return (size + 1);
}

static char	*get_word(char const *start)
{
	char	*word;
	char	*word_start;
	char	*ptr;
	int		size;

	size = 0;
	ptr = (char *)start;
	while (*ptr && *ptr != ' ' && *ptr != '\t')
	{
		size++;
		ptr++;
	}
	word = malloc (sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	word_start = word;
	while (start < ptr)
		*word++ = *start++;
	*word = 0;
	return (word_start);
}

static void	*free_array(char **array, int allocated)
{
	int	i;

	i = 0;
	while (i < allocated)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split_pipex(char const *s)
{
	char	**array;
	int		i;

	if (!s || !*s)
		return (NULL);
	array = malloc(sizeof (char *) * (get_size(s)));
	if (!array)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		if (*s)
		{
			array[i] = get_word(s);
			if (array[i] == NULL)
				return (free_array(array, i));
			i++;
			while (*s && *s != ' ' && *s != '\t')
				s++;
		}
	}
	array[i] = NULL;
	return (array);
}
