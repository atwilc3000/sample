/* 
 * L2CAP client for Linux by using BlueZ
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
#include <stdlib.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>
#include "l2cap_socket.h"
 
int main(int argc, char **argv)
{
	struct sockaddr_l2 addr = { 0 };
	int sock;
	const char *sample_text = "L2CAP Simple Example Done";

	printf("Start Bluetooth L2CAP client, server addr %s\n", L2CAP_SERVER_BLUETOOTH_ADDR);
	
	/* allocate a socket */
	sock = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);

	/* set the outgoing connection parameters, server's address and port number */
	addr.l2_family = AF_BLUETOOTH;								/* Addressing family, always AF_BLUETOOTH */
	addr.l2_psm = htobs(L2CAP_SERVER_PORT_NUM);					/* server's port number */
	str2ba(L2CAP_SERVER_BLUETOOTH_ADDR, &addr.l2_bdaddr);		/* server's Bluetooth Address */

	/* connect to server */
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("failed to connect");
		exit(1);
	}

	/* send a message */
	printf("connected...\n");
	send(sock, sample_text, strlen(sample_text), 0);
	
	close(sock);
	return 0;
}


