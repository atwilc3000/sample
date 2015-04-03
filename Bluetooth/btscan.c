/* 
 * Bluetooth scan for Linux by using BlueZ
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
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#define BLUETOOTH_NAME_MAX_LENGTH_BYTES 248	/* Bluetooth user-friendly name length limit */

int main(int argc, char **argv)
{
	inquiry_info *info = NULL;
	int max_rsp, num_rsp;
	int adapter_id, sock, len;
	int i;
	char address[18] = { 0 };
	char name[BLUETOOTH_NAME_MAX_LENGTH_BYTES] = { 0 };
							 
	adapter_id = hci_get_route(NULL);
	if(adapter_id < 0) {
		fprintf(stderr, "Device is not available.\n");
		exit(1);
	}
	
	sock = hci_open_dev( adapter_id );
	if (adapter_id < 0 || sock < 0) {
		perror("hci_open_dev");
		exit(1);
	}
										 
	len = 8;
	max_rsp = 255;	
	printf("Inquiring ...\n");
	num_rsp = hci_inquiry(adapter_id, len, max_rsp, NULL, &info, IREQ_CACHE_FLUSH);
	if( num_rsp < 0 ) 
		perror("hci_inquiry");
								 
	for (i = 0; i < num_rsp; i++) {
		ba2str(&(info+i)->bdaddr, address);
		memset(name, 0, sizeof(name));
		if (hci_read_remote_name(sock, &(info+i)->bdaddr, sizeof(name), name, 25000) < 0)
			strcpy(name, "[unknown]");

		printf("%s\t%s\n", address, name);
	}
															 
	bt_free(info);
	hci_close_dev(sock);
	
	return 0;
}
