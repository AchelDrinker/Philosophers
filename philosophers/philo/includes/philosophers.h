/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humartin <humartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:46:25 by humartin          #+#    #+#             */
/*   Updated: 2022/10/03 09:49:39 by humartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

// MACROS

# define FAILURE -1
# define SUCESS 0

//STRUCTURES

struct	s_rules;

typedef struct s_philosophe
{
	int				id;
	int				right_fork;
	int				left_fork;
	struct s_rules	*rules;
	int				ate;
	long long		last_eat;
	pthread_t		thread;
}	t_philosophe;

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				died;
	int				all_ate;
	long long		first_timestamp;
	t_philosophe	philosophes[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	writing;
	pthread_mutex_t	check_eat;
}	t_rules;

//UTILS.C

int			ft_atoi(char *str);
long long	timestamp(void);
long long	time_diff(long long past, long long current);
void		print_msg(t_rules *rules, int fd, char *msg);
void		inter_time(t_rules *rules, int time);

//INIT.C

int			init_mutex(t_rules *rules);
int			init_philosophers(t_rules *rules);
int			init_all(t_rules *rules, char **av);

//THREAD.C

void		eating(t_philosophe *p);
void		*p_thread(void	*p_data);
void		death(t_rules *rules, t_philosophe *p);
void		end_thread(t_rules *rules, t_philosophe *p);
int			start_thread(t_rules *rules);

//MAIN.c

int			main(int ac, char **av);

#endif
