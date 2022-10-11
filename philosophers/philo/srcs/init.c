/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humartin <humartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:46:43 by humartin          #+#    #+#             */
/*   Updated: 2022/10/03 09:49:28 by humartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		pthread_mutex_init(&(rules->forks[i]), NULL);
	}
	pthread_mutex_init(&(rules->writing), NULL);
	pthread_mutex_init(&(rules->check_eat), NULL);
	return (SUCESS);
}

int	init_philosophe(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		rules->philosophes[i].id = i;
		rules->philosophes[i].left_fork = i;
		rules->philosophes[i].right_fork = (i + 1) % rules->nb_philo;
		rules->philosophes[i].last_eat = 0;
		rules->philosophes[i].ate = 0;
		rules->philosophes[i].rules = rules;
	}
	return (SUCESS);
}

int	init_all(t_rules *rules, char **av)
{
	rules->nb_philo = ft_atoi(av[1]);
	rules->time_to_die = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		rules->nb_eat = ft_atoi(av[5]);
	rules->died = 0;
	rules->all_ate = 0;
	if (rules->nb_philo < 1 || rules->time_to_die < 60
		|| rules->time_to_eat < 60 || rules->time_to_sleep < 60
		|| rules->nb_philo > 200)
		return (FAILURE);
	if (av[5])
		if (rules->nb_eat < 1)
			return (FAILURE);
	init_mutex(rules);
	init_philosophe(rules);
	return (SUCESS);
}
