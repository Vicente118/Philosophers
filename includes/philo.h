/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:10:55 by vdarras           #+#    #+#             */
/*   Updated: 2024/08/15 19:32:53 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				right_fork;
	int				left_fork;
	int				is_eating;
	int				last_meal;
	long long		last_meal_time;
	int				times_eaten;
	int				id;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				number_philo;
	int				meals_to_eat; // -1 if not specified
	int				is_dead;
	long long		start_time;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t lock;
	int				argc;
	char			**argv;
}				t_data;


// UTILS //
size_t		ft_strlen(const char *str);
int			ft_atoi(const char *str);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *source);
void		ft_usleep(long int time_in_ms);

// PARSING AND INITALIZATION //
int			check_arg(int argc);
int			check_number(char **argv);
int 		check_input(char **argv);
int			init_all(t_data *data);
int			init_data(t_data *data);
void		init_philo(t_data *data);
long long	get_time_ms(void);

// ACTIONS //
void		think(t_data *data, t_philo *philo);
void		eat(t_data *data, t_philo *philo);
void		philo_sleep(t_data *data, t_philo *philo);
void		take_fork(t_data *data, t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2);
void		release_fork(t_data *data, t_philo *philo);

// SIMULATION //

int			start_simulation(t_data *data);
void		*check_death(void *arg);
void 		*philo_routine(void *arg);
int			check_last_meal(t_data *data);

// CLEAR //
void	destroy_mutex_and_free(t_data *data);
#endif