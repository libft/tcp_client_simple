/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:28:48 by jmaing            #+#    #+#             */
/*   Updated: 2022/04/05 22:03:57 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>

#include <ft/tcp_client_simple.h>

t_error	address(const char *hostname, int port, struct sockaddr_in *out)
{
	const struct hostent	*host = gethostbyname(hostname);

	if (!host)
		return (1);
	out->sin_family = AF_INET;
	out->sin_port = htons(port);
	memcpy(&out->sin_addr.s_addr, host->h_addr_list[0], sizeof(char *));
	return (0);
}

int	main(void)
{
	struct sockaddr_in	sockaddr_in;
	t_tcp_server_simple	*server;
	int					client_fd;

	if (
		address("0.0.0.0", 3000, &sockaddr_in)
		|| create_tcp_server_simple(sockaddr_in, &server)
	)
		return (EXIT_FAILURE);
	client_fd = -1;
	while (client_fd < 0)
	{
		client_fd = accept(server->server_fd, NULL, NULL);
		if (client_fd < 0 && !(errno == EAGAIN || errno == EWOULDBLOCK))
			continue ;
		if (client_fd < 0)
			return (EXIT_FAILURE);
	}
	if (send(client_fd, (void *) "Hello world!", 13, 0) == -1)
	{
		perror("send");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
