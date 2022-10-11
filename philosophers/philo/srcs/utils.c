/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humartin <humartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:47:31 by humartin          #+#    #+#             */
/*   Updated: 2022/10/03 09:49:32 by humartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	neg;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] <= 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * neg);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

long long	time_diff(long long past, long long current)
{
	return (current - past);
}

void	inter_time(t_rules *rules, int time)
{
	long long	i;

	i = timestamp();
	while (rules->died == 0)
	{
		if (time_diff(i, timestamp()) > time)
			break ;
		usleep(50);
	}
}

void	print_msg(t_rules *rules, int id, char *msg)
{
	if (rules->died == 0)
	{
		pthread_mutex_lock(&(rules->writing));
		printf("\033[90m%lli ms : ", timestamp() - rules->first_timestamp);
		printf("\033[90mphilosophe %d ", id + 1);
		printf("%s\n", msg);
		pthread_mutex_unlock(&(rules->writing));
	}
	return ;
}
