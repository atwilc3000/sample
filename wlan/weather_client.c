/* 
 * Weather Client sample for wlan in Linux OS
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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

#define WEATHER_SERVER_ADDR "api.openweathermap.org"
#define PORT 80

#define HTML_QUERY_PREFIX "GET /data/2.5/weather?q="
#define CITY "seoul"
#define HTML_QUERY_END " HTTP/1.1\r\nHost: api.openweathermap.org\r\nAccept: */*\r\n\r\n"

#define BUFFER_SIZE 1024
int main(int argc, char * argv[])
{
	int socketfd, n;
	struct hostent *server;
	struct sockaddr_in server_addr;
	char buffer[BUFFER_SIZE];
	char *json;

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
		printf("Cannot Open socket\n");
		return -1;
	}
	server = gethostbyname(WEATHER_SERVER_ADDR);
	if (server == NULL) {
		printf("No such host\n");
		return -1;
	}

	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
	server_addr.sin_port = htons(PORT);

	printf("connecting...\n");

	if (connect(socketfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0){
		printf("Cannot connect\n");
		return -1;
	}

	bzero(buffer,BUFFER_SIZE);
	sprintf((char *)buffer, "%s%s%s", HTML_QUERY_PREFIX, CITY, HTML_QUERY_END);
	n = write(socketfd,buffer,strlen(buffer));
	if (n < 0){
		printf("Writing error\n");
		return -1;
	}
	
	bzero(buffer,BUFFER_SIZE);
	n = read(socketfd,buffer,BUFFER_SIZE);
	if (n < 0){
		printf("Reading error\n");
		return -1;
	}
	
	json = strchr(buffer,'{');
	printf("%s\n", json);
	close(socketfd);
	return 0;
}
