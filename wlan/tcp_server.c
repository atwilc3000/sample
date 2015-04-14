/* 
 * TCP Server sample for wlan in Linux OS
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
#include "unistd.h"

#define BUFF_SIZE 1024

int main(int argc, char *argv[]) 
{
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int n;
	char rcvBuffer[BUFF_SIZE];
	socklen_t len;

	if(argc != 2) {
		printf("usage : %s [port]\n", argv[0]);
		exit(0);
	}

	if((s_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("Server : Can't open TCP server socket\n");
		exit(0);
	}

	memset(&s_addr, 0, sizeof(s_addr));

	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(atoi(argv[1]));

	if(bind(s_socket, (struct sockaddr*) &s_addr, sizeof(s_addr)) == -1) {
		printf("Can not Bind\n");
		return -1;
	}

	if(listen(s_socket, 5) == -1) {
		printf("listen Fail\n");
		return -1;
	}

	while(1) {
		len = sizeof(c_addr);
		c_socket = accept(s_socket, (struct sockaddr*) &c_addr, &len);

		while((n = read(c_socket, rcvBuffer, sizeof(rcvBuffer))) != 0) {
			rcvBuffer[n] = '\0';
			printf("FROM Client : %s",rcvBuffer);
			if(write(c_socket, rcvBuffer, n) == -1)
			{
				printf("write Fail\n");
			}
		}
		close(c_socket);
	}
	return 0;
}
