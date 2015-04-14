/* 
 * UDP Server sample for wlan in Linux OS
 * Copyright (C) 2015 by Tony Cho
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "netinet/in.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/socket.h"
#include "sys/types.h"

#define  BUFF_SIZE   1024

int main(int argc, char *argv[])
{
	struct sockaddr_in s_addr, c_addr;
	int	sock;
	char	buff_rcv[BUFF_SIZE];
	char	buff_snd[BUFF_SIZE];
	socklen_t c_addr_size;

	if(argc != 2) {
		printf("usage : %s [port]\n", argv[0]);
		exit(0);
	}

	if((sock  = socket( PF_INET, SOCK_DGRAM, 0)) == -1) {
		printf("Server : Can't open UDP server socket\n");
		exit(0);
	}

	memset(&s_addr, 0x00, sizeof(s_addr));

	s_addr.sin_family     = AF_INET;
	s_addr.sin_port       = htons(atoi(argv[1]));
	s_addr.sin_addr.s_addr= htonl(INADDR_ANY);

	if(bind(sock, (struct sockaddr*)&s_addr, sizeof(s_addr)) == -1) {
		printf("Can not Bind\n");
		return -1;
	}

	while(1)
	{
		c_addr_size = sizeof(c_addr);
		recvfrom(sock, buff_rcv, BUFF_SIZE, 0, ( struct sockaddr*)&c_addr, &c_addr_size);
		printf("Server received : %s\n", buff_rcv);

		sprintf(buff_snd, "%s", buff_rcv);
		sendto(sock, buff_snd, strlen(buff_snd)+1, 0, (struct sockaddr*)&c_addr, sizeof(c_addr));
	}
	return 0;
}
