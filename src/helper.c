/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:11:06 by magebreh          #+#    #+#             */
/*   Updated: 2025/11/20 19:49:59 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void error_exit(char *err)
{
	printf("%s\n", err);
	exit(EXIT_FAILURE);
}
uint64_t get_time_us(void)
{
	struct timeval tv;

	if(gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((uint64_t)tv.tv_sec * 1000000ULL + tv.tv_usec);
}

void log_action(t_philo *philo, char *action)
{
	uint64_t current_time;
	uint64_t elapsed_ms;

	if(should_stop(philo->table))
		return ;
	current_time = get_time_us();
	if(current_time == 0)
		return ;
	pthread_mutex_lock(&philo->table->log_mtx);
	if(should_stop(philo->table))
	{
		pthread_mutex_unlock(&philo->table->log_mtx);
		return ;
	}
	elapsed_ms = (current_time - philo->table->start_us) / 1000;
	printf("%llu %d %s\n", (unsigned long long)elapsed_ms, philo->id, action);
	pthread_mutex_unlock(&philo->table->log_mtx);
}

void release_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->left->mtx);
    pthread_mutex_unlock(&philo->right->mtx);
}

int should_stop(t_data *table)
{
    int stop;

    pthread_mutex_lock(&table->stop_mtx);
    stop = table->stop;
    pthread_mutex_unlock(&table->stop_mtx);
    return (stop);    
}
