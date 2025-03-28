/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 06:35:39 by aben-dri          #+#    #+#             */
/*   Updated: 2025/03/27 21:18:45 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static t_data	g_data;
	static pid_t	client_pid = 0;

	(void)context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (info->si_pid != client_pid)
	{
		client_pid = info->si_pid;
		g_data.g_bit_counter = 0;
		g_data.current_char = 0;
	}
	if (signum == SIGUSR2)
		g_data.current_char |= (1 << (7 - g_data.g_bit_counter));
	g_data.g_bit_counter++;
	if (g_data.g_bit_counter == 8)
	{
		g_data.g_bit_counter = 0;
		if (g_data.current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &g_data.current_char, 1);
		g_data.current_char = 0;
	}
	kill(client_pid, SIGUSR1);
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
}

int	main(void)
{
	struct sigaction	sa;

	write(1, "Server PID :\n", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) == -1 || sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Error: Signal setup failed\n", 27);
		exit(1);
	}
	while (1)
		pause();
	return (0);
}
