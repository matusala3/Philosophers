/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:47:04 by magebreh          #+#    #+#             */
/*   Updated: 2025/11/20 19:43:04 by magebreh         ###   ########.fr       */
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
