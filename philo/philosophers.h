/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aedouard <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/12/05 15:27:54 by aedouard		  #+#	#+#			 */
/*   Updated: 2021/12/09 15:26:58 by aedouard         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define EAT		"is eating"
# define SLEEP		"is sleeping"
# define THINK		"is thinking"
# define TAKE		"has taken a fork"
# define DIE		"died"
# define LEFT_FORK	0
# define RIGHT_FORK 1

typedef struct philo_data
{
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	long int	min_eat;
	long int	nb_philo;
	int			one_dead;
	int			*forks;
}				t_philo_data;

typedef struct s_philosopher
{
	pthread_t		thread;
	int				*one_dead;
	int				id;
	int				alive;
	int				ready;
	int				eat_left;
	long int		time_to_die;
	long int		last_eat_sec;
	long int		last_eat_usec;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		start_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				lf_available;
	int				rf_available;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*read_lock;
	int				*forks;
	int				nb_philo;
}					t_philosopher;

int				start_threads(t_philosopher **philosophers, int n);
int				all_alive(t_philosopher **philosophers);
int				can_continue(t_philosopher *philosoper);
int				all_ready(t_philosopher **philosopers);
int				take_fork(t_philosopher *philo, int fork_value);
int				eat(t_philosopher *philo);
int				philo_sleep(t_philosopher *philo);
int				think(t_philosopher *philo);
int				all_eat(t_philosopher **philosophers);
int				ft_atoi(const char *str);
int				ft_is_only_digits(char *str);
int				init_philo_data(int ac, char **av, t_philo_data *data);
pthread_mutex_t	**init_mutexes(int n);
t_philosopher	**init_philosophers(t_philo_data data, pthread_mutex_t **fork,
					pthread_mutex_t *wlock, pthread_mutex_t **rlock);
void			init_timer(t_philosopher **philosophers);
void			*philo_routine(void *arg);
void			*main_routine(void *arg);
void			print_action(t_philosopher *philosopher, char *action);
void			free_philo(t_philosopher **philosophers);
int				check_args(int ac, char **av);
int				ft_atoi_error(long int *ret, char *str);
void			ft_usleep(long value, t_philosopher *philo);

#endif
