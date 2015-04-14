/* 
 * SDP Search for Linux by using BlueZ
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
#include <bluetooth/bluetooth.h>
#include <bluetooth/sdp.h>
#include <bluetooth/sdp_lib.h>
#include "sdp_test.h"

int main(int argc, char **argv)
{
	int status;
	bdaddr_t target;
	uuid_t svc_uuid;
	sdp_list_t *response_list, *search_list, *attrid_list;
	sdp_session_t *session = 0;
	uint32_t range = 0x0000ffff;
	uint8_t port = 0;

	str2ba(SDP_SERVER_BLUETOOTH_ADDR, &target);

	/* connect to the SDP server running on the remote machine */
	session = sdp_connect(BDADDR_ANY, &target, SDP_RETRY_IF_BUSY);

	sdp_uuid128_create(&svc_uuid, &uuid128);
	search_list = sdp_list_append(0, &svc_uuid);
	attrid_list = sdp_list_append(0, &range);

	// get a list of service records that have UUID 0xabcd
	response_list = NULL;
	status = sdp_service_search_attr_req(session, search_list,
	SDP_ATTR_REQ_RANGE, attrid_list, &response_list);

	if(status == 0) {
		sdp_list_t *proto_list = NULL;
		sdp_list_t *r = response_list;

		// go through each of the service records
		for (; r; r = r->next) {
			sdp_record_t *rec = (sdp_record_t*) r->data;

			// get a list of the protocol sequences
			if(sdp_get_access_protos(rec, &proto_list) == 0 ) {
				// get the RFCOMM port number
				port = sdp_get_proto_port(proto_list, RFCOMM_UUID);

				sdp_list_free(proto_list, 0);
			}
			sdp_record_free(rec);
		}
	}
	sdp_list_free( response_list, 0 );
	sdp_list_free( search_list, 0 );
	sdp_list_free( attrid_list, 0 );
	sdp_close( session );

	if(port != 0) {
		printf("found service running on RFCOMM port %d\n", port);
	}

	return 0;
}
