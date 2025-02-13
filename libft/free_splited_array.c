/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_splited_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:39:53 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/03 15:42:49 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_splited_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
}
