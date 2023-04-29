/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:42:03 by osabir            #+#    #+#             */
/*   Updated: 2023/02/25 14:33:31 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_tab[8];

void	fill_tab(char c)
{
	int		right_shift;
	int		i;

	right_shift = 7;
	i = 0;
	while (right_shift >= 0)
	{
		if (c & (1 << right_shift))
			g_tab[i] = '1';
		else
			g_tab[i] = '0';
		right_shift--;
		i++;
	}
}

int	emoji_check(char c)
{
	int		bits_check;
	int		i;

	i = 0;
	bits_check = 0;
	fill_tab(c);
	while (1)
	{
		if (g_tab[i] == '1')
			bits_check++;
		else
			break ;
		i++;
	}
	return (bits_check);
}

void	wait_unicode(t_call *help)
{
	if ((help->size_of_bits == 0) || (help->size_of_bits == 1))
	{
		ft_putchar(help->c);
		help->size_of_bits = 0;
		help->stop_check = 0;
	}
	else if (help->size_of_bits > 1)
	{
		help->unicode[help->bit] = help->c;
		help->bit++;
		help->print++;
	}
	if (help->size_of_bits == help->print)
	{
		ft_putstr(help->unicode);
		help->stop_check = 0;
		clear_unicode(help);
		help->size_of_bits = 0;
		help->print = 0;
		help->bit = 0;
	}
	help->c = 0;
	help->i = 0;
}

void	handler(int sig, siginfo_t *info, void *p)
{
	t_call		help;
	static int	pid;

	(void)p;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		clear_unicode(&help);
	}
	if (sig == SIGUSR1)
		help.c = help.c | (1 << help.i);
	help.i++;
	if (help.i == 8)
	{
		if (help.c == '\0')
			kill(pid, SIGUSR1);
		else if (help.stop_check == 0)
		{
			help.size_of_bits = emoji_check(help.c);
			help.stop_check++;
		}
		wait_unicode(&help);
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
