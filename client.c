/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:42:16 by osabir            #+#    #+#             */
/*   Updated: 2023/02/24 17:31:45 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	exit_error(void)
{
	ft_putstr("ERROR\n");
	exit(1);
}

void	send_signal(char c, int pid)
{
	int	j;
	int	kill_check;

	j = 0;
	kill_check = 0;
	while (j < 8)
	{
		if (c & (1 << j))
		{
			kill_check = kill(pid, SIGUSR1);
			if (kill_check == -1)
				exit(1);
		}
		else
		{
			kill_check = kill(pid, SIGUSR2);
			if (kill_check == -1)
				exit(1);
		}
		j++;
		usleep(700);
	}
}

int	main(int ac, char **av)
{
	static int	pid;
	int			i;
	int			j;

	j = 0;
	i = 0;
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (pid == 0 || pid == -1)
			exit_error();
		while (av[2][i])
		{
			send_signal(av[2][i], pid);
			usleep(700);
			i++;
		}
	}
	return (0);
}
