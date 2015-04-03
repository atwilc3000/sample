/* 
 * SDP Register for Linux by using BlueZ
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

#include <unistd.h>
#include <stdlib.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/sdp.h>
#include <bluetooth/sdp_lib.h>
#include "sdp_test.h"

int register_service(sdp_session_t *session)
{
    uint8_t rfcomm_channel = 11;
    const char *service_name = "Atmel Simple Test Service";
    const char *svc_dsc = "Simple Test for SDP Register";
    const char *service_prov = "Tony";
	int ret = 0;

    uuid_t root_uuid, l2cap_uuid, rfcomm_uuid, svc_uuid, 
           svc_class_uuid;
    sdp_list_t *l2cap_list = 0, 
               *rfcomm_list = 0,
               *root_list = 0,
               *proto_list = 0, 
               *access_proto_list = 0,
               *svc_class_list = 0,
               *profile_list = 0;
    sdp_data_t *channel = 0;
    sdp_profile_desc_t profile;
    sdp_record_t record = { 0 };

    /* set the general service ID */
    sdp_uuid128_create( &svc_uuid, &uuid128 );
    sdp_set_service_id( &record, svc_uuid );

    /* set the service class */
    sdp_uuid16_create(&svc_class_uuid, SERIAL_PORT_SVCLASS_ID);
    svc_class_list = sdp_list_append(0, &svc_class_uuid);
    sdp_set_service_classes(&record, svc_class_list);

    /* set the Bluetooth profile information */
    sdp_uuid16_create(&profile.uuid, SERIAL_PORT_PROFILE_ID);
    profile.version = 0x0100;
    profile_list = sdp_list_append(0, &profile);
    sdp_set_profile_descs(&record, profile_list);

    /* make the service record publicly browsable */
    sdp_uuid16_create(&root_uuid, PUBLIC_BROWSE_GROUP);
    root_list = sdp_list_append(0, &root_uuid);
    sdp_set_browse_groups( &record, root_list );

    /* set l2cap information */
    sdp_uuid16_create(&l2cap_uuid, L2CAP_UUID);
    l2cap_list = sdp_list_append( 0, &l2cap_uuid );
    proto_list = sdp_list_append( 0, l2cap_list );

    /* register the RFCOMM channel for RFCOMM sockets */
    sdp_uuid16_create(&rfcomm_uuid, RFCOMM_UUID);
    channel = sdp_data_alloc(SDP_UINT8, &rfcomm_channel);
    rfcomm_list = sdp_list_append( 0, &rfcomm_uuid );
    sdp_list_append( rfcomm_list, channel );
    sdp_list_append( proto_list, rfcomm_list );

    access_proto_list = sdp_list_append( 0, proto_list );
    sdp_set_access_protos( &record, access_proto_list );

    /* set the name, provider, and description */
    sdp_set_info_attr(&record, service_name, service_prov, svc_dsc);

    /* register the service record, */
    if(sdp_record_register(session, &record, SDP_RECORD_PERSIST) < 0) {
		printf("Service Record registration failed\n");
		ret = -1;
		goto end;
	}

end:
    // cleanup
    sdp_data_free(channel);
    sdp_list_free(l2cap_list, 0);
    sdp_list_free(rfcomm_list, 0);
    sdp_list_free(root_list, 0);
    sdp_list_free(access_proto_list, 0);
    sdp_list_free(svc_class_list, 0);
    sdp_list_free(profile_list, 0);

    return ret;
}

int main(int argc, char **argv)
{
    sdp_session_t* session = sdp_connect(BDADDR_ANY, BDADDR_LOCAL, SDP_RETRY_IF_BUSY);
	if(!session) {
		printf("fail to SDP connect\n");
		exit(1);
	}
	if(register_service(session) < 0) {
		printf("fail to register service\n");
		exit(1);
	}

    sdp_close(session);
   	printf("done...\n");
    return 0;
}
