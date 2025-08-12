/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:47:04 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/12 17:16:35 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_data table;
	if(argc != 5 && argc != 6)
		error_exit("Usage: ./philo 3 600 100 100 [3]");
	if(parse_arg(&table.cfg, argc, argv) != 0)
		error_exit("error on parsing the argument");
	if(init_sim(&table) != 0)
		error_exit("error on initalizing  simulation");
	run_sim(&table);
	cleanup(&table);
	return (0);
}
