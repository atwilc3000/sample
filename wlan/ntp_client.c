/* 
 * NTP Client sample for wlan in Linux OS
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

#include "stdio.h"
#include "string.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "netdb.h"
#include <unistd.h>

#define PORT 123
#define ADDR "pool.ntp.org"
#define RCV_BUFF_SIZE 1024

int main(int argc, char *argv[])
{
	int c_socket;
	struct sockaddr_in server_addr;
	struct sockaddr saddr;
	struct hostent *host_entry;
	char* target_ip;
	uint8_t sndBuffer[48] = {0};
	uint8_t rcvBuffer[RCV_BUFF_SIZE];
	uint32_t secsSince1900, seventyYears, epoch;

	printf("Start NTP client...\n");

	if((c_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		printf("Client : Can't open UDP client socket\n");
		return -1;
	}

	host_entry = (struct hostent *)gethostbyname(ADDR);
	if(host_entry == NULL) {
		printf("Client : Can't get Host\n");
		return -1;
	}
	
	sndBuffer[0] = '\x1b';

	target_ip = inet_ntoa(*((struct in_addr *)host_entry->h_addr));

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_addr.s_addr = inet_addr(target_ip);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);

	if(-1 == sendto(c_socket, sndBuffer, sizeof(sndBuffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr))) {
		printf("Can not connect\n");
		close(c_socket);
		return -1;
	}
	
	socklen_t saddr_l = sizeof(saddr);
	recvfrom(c_socket, rcvBuffer, sizeof(rcvBuffer), 0, (struct sockaddr *)&saddr, &saddr_l);

	if((rcvBuffer[0] & 0x7) != 4) {
		return -1;
	} else {
		secsSince1900 = rcvBuffer[40] << 24 | rcvBuffer[41] << 16 | rcvBuffer[42] << 8 | rcvBuffer[43];
		seventyYears = 2208988800UL;
		epoch = secsSince1900 - seventyYears;
		printf("The GMT time is %lu : %02lu : %02lu \n", (long unsigned int)((epoch % 86400L) / 3600), (long unsigned int)((epoch % 3600) / 60), (long unsigned int)(epoch % 60));
	}

	close(c_socket);
	return 0;
}
