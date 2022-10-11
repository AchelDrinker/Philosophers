/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humartin <humartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:47:23 by humartin          #+#    #+#             */
/*   Updated: 2022/10/03 09:49:30 by humartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eating(t_philosophe *p)
{
	t_rules	*rules;

	rules = p->rules;
	pthread_mutex_lock(&(rules->forks[p->left_fork]));
	print_msg(rules, p->id, "\033[94mhas taken a fork !");
	pthread_mutex_lock(&(rules->forks[p->right_fork]));
	print_msg(rules, p->id, "\033[96mhas taken a fork !");
	pthread_mutex_lock(&(rules->check_eat));
	print_msg(rules, p->id, "\033[95mis eating !");
	p->last_eat = timestamp();
	pthread_mutex_unlock(&(rules->check_eat));
	if (rules->nb_eat > 0)
		p->ate++;
	inter_time(rules, rules->time_to_eat);
	pthread_mutex_unlock(&(rules->forks[p->left_fork]));
	pthread_mutex_unlock(&(rules->forks[p->right_fork]));
}

void	*p_thread(void *p_data)
{
	int				i;
	t_philosophe	*p;
	t_rules			*rules;

	i = 0;
	p = (t_philosophe *)p_data;
	rules = p->rules;
	if (p->id % 2)
		usleep(15000);
	while (rules->died == 0 && rules->all_ate == 0)
	{
		eating(p);
		print_msg(rules, p->id, "\033[93mis sleeping !");
		inter_time(rules, rules->time_to_sleep);
		print_msg(rules, p->id, "\033[92mis thinking !");
		i++;
	}
	return (NULL);
}

void	death(t_rules *rules, t_philosophe *p)
{
	int	i;

	while (rules->all_ate == 0)
	{
		i = -1;
		while (++i < rules->nb_philo && rules->died == 0)
		{
			pthread_mutex_lock(&(rules->check_eat));
			if (time_diff(p[i].last_eat, timestamp()) > rules->time_to_die)
			{
				print_msg(rules, p->id, "\033[91mdied !");
				rules->died = 1;
			}
			pthread_mutex_unlock(&(rules->check_eat));
		}
		usleep(100);
		if (rules->died == 1)
			break ;
		i = 0 ;
		while (rules->all_ate == 0 && p[i].ate >= rules->nb_eat)
			i++;
		if (i == rules->nb_philo)
			rules->all_ate = 1;
	}
}

void	end_thread(t_rules *rules, t_philosophe *p)
{
	int	i;

	i = 0;
	while (++i < rules->nb_philo)
	{
		pthread_join(p[i].thread, NULL);
		if (rules->nb_philo == 1)
			break ;
	}
	i = 0;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
}

int	start_thread(t_rules *rules)
{
	t_philosophe	*p;
	int				i;

	p = rules->philosophes;
	i = 0;
	rules->first_timestamp = timestamp();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(p[i].thread), NULL, p_thread, &(p[i])))
			return (FAILURE);
		p[i].last_eat = timestamp();
		i++;
	}
	death(rules, p);
	end_thread(rules, p);
	return (SUCESS);
}
