/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:24:55 by osabir            #+#    #+#             */
/*   Updated: 2023/02/25 13:33:05 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_call
{
	int		i;
	int		size_of_bits;
	int		stop_check;
	int		print;
	int		bit;
	char	c;
	char	unicode[4];
}			t_call;

void		ft_putchar(char c);
void		ft_putnbr(int n);
int			ft_atoi(const char *str);
void		ft_putstr(char *s);
void		clear_unicode(t_call *help);

#endif