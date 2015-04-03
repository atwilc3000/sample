/* 
 * L2CAP server for Linux by using BlueZ
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
 
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>
#include "l2cap_socket.h"

int main(int argc, char **argv)
{
	struct sockaddr_l2 loc_addr = { 0 }, rem_addr = { 0 };
	char buf[1024] = { 0 };
	int server_socket, client_socket, bytes_read;
	unsigned int opt = sizeof(rem_addr);

	printf("Start Bluetooth L2CAP server...\n");
	
	/* allocate socket */
	server_socket = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);

	/* bind socket to the local bluetooth adapter */
	loc_addr.l2_family = AF_BLUETOOTH;						/* Addressing family, always AF_BLUETOOTH */
	bacpy(&loc_addr.l2_bdaddr, BDADDR_ANY);					/* Bluetooth address of local bluetooth adapter */
	loc_addr.l2_psm = htobs(L2CAP_SERVER_PORT_NUM);			/* port number of local bluetooth adapter */

	printf("binding\n");
	if(bind(server_socket, (struct sockaddr *)&loc_addr, sizeof(loc_addr)) < 0) {
		perror("failed to bind");
		exit(1);
	}

	printf("listening\n");
	/* put socket into listening mode */
	listen(server_socket, 1);

	/* accept one connection */
	client_socket = accept(server_socket, (struct sockaddr *)&rem_addr, &opt);	/* return new socket for connection with a client */

	ba2str( &rem_addr.l2_bdaddr, buf );
	printf("connected from %s\n", buf);
	
	/* read data from the client */
	memset(buf, 0, sizeof(buf));
	bytes_read = recv(client_socket, buf, sizeof(buf), 0);
	if( bytes_read > 0 ) {
		printf("received [%s]\n", buf);
	}

	/* close connection */
	close(client_socket);
	close(server_socket);
	return 0;
}

