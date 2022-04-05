/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_client_simple.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:57:05 by jmaing            #+#    #+#             */
/*   Updated: 2022/04/05 21:49:58 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_CLIENT_SIMPLE_H
# define TCP_CLIENT_SIMPLE_H

# include <netinet/ip.h>

typedef int	t_error;

typedef struct s_tcp_server_simple {
	int	server_fd;
}	t_tcp_server_simple;

t_error	create_tcp_server_simple(
			struct sockaddr_in sockaddr_in,
			t_tcp_server_simple **out);

#endif
