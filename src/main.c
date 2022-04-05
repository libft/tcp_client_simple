/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:56:41 by jmaing            #+#    #+#             */
/*   Updated: 2022/04/05 21:55:45 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/ip.h>

#include <ft/tcp_client_simple.h>

t_error	create_tcp_server_simple(
	struct sockaddr_in sockaddr_in,
	t_tcp_server_simple **out
)
{
	const struct protoent		*tcp = getprotobyname("tcp");
	t_tcp_server_simple *const	result
		= (t_tcp_server_simple *) malloc(sizeof(t_tcp_server_simple));

	if (!result)
		return (1);
	result->server_fd = socket(PF_INET, SOCK_STREAM, tcp->p_proto);
	if (result->server_fd == -1)
	{
		free(result);
		return (2);
	}
	if (bind(result->server_fd,
			(struct sockaddr *) &sockaddr_in, sizeof(struct sockaddr_in)) == -1)
	{
		close(result->server_fd);
		free(result);
		return (3);
	}
	if (listen(result->server_fd, 1) == -1)
		return (4);
	*out = result;
	return (0);
}
