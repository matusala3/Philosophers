/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:47:04 by magebreh          #+#    #+#             */
/*   Updated: 2025/11/21 11:59:35 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_data table;

	if(argc != 5 && argc != 6)
		error_exit("Usage: ./philo 3 600 100 100 [3]");
	if(parse_arg(&table.cfg, argc, argv) != 0)
		error_exit("error on parsing the argument");
	if(init(&table) != 0)
		error_exit("error on initalizing  simulation");
	run_sim(&table);
	cleanup(&table);
	return (0);
}

void cleanup(t_data *table)
{
	pthread_mutex_destroy(&table->stop_mtx);
	pthread_mutex_destroy(&table->log_mtx);
	cleanup_all_array_mutexes(table);
	if(table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
	if(table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
	printf("✅ Cleanup completed successfully\n");
}

int check_meal_limit(t_data  *table)
{
	int i;
	int full_philos;
	
	if(table->cfg.meal_limit == -1)
		return (0);
	i = 0;
	full_philos = 0;
	while (i < table->cfg.philo_num)
	{
		pthread_mutex_lock(&table->philos[i].state_mtx);
		if(table->philos[i].meals_done >= table->cfg.meal_limit)
			full_philos++;
		pthread_mutex_unlock(&table->philos[i].state_mtx);
		i++;
	}
	if(full_philos == table->cfg.philo_num)
	{
		pthread_mutex_lock(&table->stop_mtx);
		table->stop = 1;
		pthread_mutex_unlock(&table->stop_mtx);
		printf("✅ All philosophers have eaten %d times\n", table->cfg.meal_limit);
		return (1);		
	}
	return(0);
}
