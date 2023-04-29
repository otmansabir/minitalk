/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:42:08 by osabir            #+#    #+#             */
/*   Updated: 2023/02/24 20:35:41 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int sig, siginfo_t *info, void *p)
{
	static int		i;
	static char		c;
	static int		pid;

	(void)p;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		i = 0;
		c = 0;
	}	
	if (sig == SIGUSR1)
		c = c | (1 << i);
	i++;
	if (i == 8)
	{
		ft_putchar(c);
		i = 0;
		c = '\0';
	}
}

int	main(void)
{
	struct sigaction	gets;

	ft_putnbr(getpid());
	write(1, "\n", 1);
	gets.sa_sigaction = &handler;
	gets.sa_flags = SIGINFO;
	while (1)
	{
		sigaction(SIGUSR2, &gets, NULL);
		sigaction(SIGUSR1, &gets, NULL);
		pause();
	}
}
