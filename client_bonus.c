/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:42:35 by osabir            #+#    #+#             */
/*   Updated: 2023/02/24 17:14:16 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	exit_error(void)
{
	ft_putstr("ERROR\n");
	exit(1);
}

void	handler(int sig)
{
	(void)sig;
	ft_putstr("your message it's send\n");
	exit(0);
}

void	send_null(int pid)
{
	int	i;

	i = 0;
	while (i <= 8)
	{
		kill(pid, SIGUSR2);
		usleep(700);
		i++;
	}
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
		signal(SIGUSR1, &handler);
		while (av[2][i])
		{
			send_signal(av[2][i], pid);
			usleep(300);
			i++;
		}
		send_null(pid);
		while (1)
		{
			pause();
		}
	}
	return (0);
}
