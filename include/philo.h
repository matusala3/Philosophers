/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:33:02 by magebreh          #+#    #+#             */
/*   Updated: 2025/11/18 18:53:13 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

typedef enum e_philo_state
{
    PH_THINKING = 0,
    PH_EATING,
    PH_SLEEPING,
    PH_DEAD
}   t_philo_state;

typedef struct s_config
{
    int philo_num;
    int time_to_die_ms;
    int time_to_eat_ms;
    int time_to_sleep_ms;
    int meal_limit;
}   t_config;

typedef struct s_fork
{
    int             id;
    pthread_mutex_t mtx;
}   t_fork;

typedef struct s_philo
{
    int              id;
    int              meals_done;
    uint64_t         last_meal_us;
    t_fork          *left;
    t_fork          *right;
    pthread_t        thread;
    pthread_mutex_t  state_mtx;
    t_philo_state    state;
    t_data          *table;
}   t_philo;


typedef struct s_data
{
    t_config         cfg;
    t_fork          *forks;
    t_philo         *philos;
    int              stop;
    pthread_mutex_t  stop_mtx;
    pthread_mutex_t  log_mtx;
    uint64_t         start_us;
    pthread_t        monitor;
}   t_data;


//helper
void error_exit(char *err);
uint64_t get_time_us(void);

int init(t_data *table);

int parse_arg(t_config *cfg, int argc, char **argv);
