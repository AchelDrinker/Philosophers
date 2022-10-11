/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humartin <humartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:47:15 by humartin          #+#    #+#             */
/*   Updated: 2022/10/03 09:49:29 by humartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_rules	rules;

	if (ac != 6 && ac != 5)
		return (printf("\033[91mERROR : trop ou pas assez d'arguments !\n"));
	if (init_all(&rules, av) == FAILURE)
		return (printf("\033[91mERROR : initialisation echoue !\n"));
	if (start_thread(&rules) == FAILURE)
		return (printf("\033[91mERROR : erreur dans la creation des threads!\n"));
	return (SUCESS);
}
