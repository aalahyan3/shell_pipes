/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:12:50 by aalahyan          #+#    #+#             */
/*   Updated: 2025/02/13 17:27:48 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0 && ac >= 6)
		here_doc(ac, av, env);
	else if (ac > 4)
		multiple_pipes(ac, av, env);
	else
		ft_error(NULL, INV_ARGS);
}
