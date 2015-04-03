prefix=/usr/local/BlueZ-5.29
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
includedir=${prefix}/include

CC=$(CROSS_COMPILE)gcc
STRIP=$(CROSS_COMPILE)strip
INC = -I. -I${includedir}
CFLAGS=	-g -O2 -Wall $(INC) 

BTSCAN_OBJ=btscan.o
BTSCAN_SRC=$(BTSCAN_OBJ:.o=.c)

RFCOMM-SERVER_OBJ=rfcomm_server.o
RFCOMM-SERVER_SRC=$(RFCOMM-SERVER_OBJ:.o=.c)

RFCOMM-CLIENT_OBJ=rfcomm_client.o
RFCOMM-CLIENT_SRC=$(RFCOMM-CLIENT_OBJ:.o=.c)

L2CAP-SERVER_OBJ=l2cap_server.o
L2CAP-SERVER_SRC=$(L2CAP-SERVER_OBJ:.o=.c)

L2CAP-CLIENT_OBJ=l2cap_client.o
L2CAP-CLIENT_SRC=$(L2CAP-CLIENT_OBJ:.o=.c)

SDP-SEARCH_OBJ=sdp_search.o
SDP-SEARCH_SRC=$(SDP-SEARCH_OBJ:.o=.c)

SDP-REGISTER_OBJ=sdp_register.o
SDP-REGISTER_SRC=$(SDP-REGISTER_OBJ:.o=.c)

ALL=btscan rfcomm-server rfcomm-client l2cap-server l2cap-client sdp-search sdp-register

all: $(ALL)

btscan: $(BTSCAN_OBJ)
	$(CC) -o $@ $(CFLAGS) $(BTSCAN_SRC) -L${libdir} -lbluetooth

rfcomm-server: $(RFCOMM-SERVER_OBJ)
	$(CC) -o $@ $(CFLAGS) $(RFCOMM-SERVER_SRC) -L${libdir} -lbluetooth

rfcomm-client: $(RFCOMM-CLIENT_OBJ)
	$(CC) -o $@ $(CFLAGS) $(RFCOMM-CLIENT_SRC) -L${libdir} -lbluetooth

l2cap-server: $(L2CAP-SERVER_OBJ)
	$(CC) -o $@ $(CFLAGS) $(L2CAP-SERVER_SRC) -L${libdir} -lbluetooth

l2cap-client: $(L2CAP-CLIENT_OBJ)
	$(CC) -o $@ $(CFLAGS) $(L2CAP-CLIENT_SRC) -L${libdir} -lbluetooth

sdp-search: $(SDP-SEARCH_OBJ)
	$(CC) -o $@ $(CFLAGS) $(SDP-SEARCH_SRC) -L${libdir} -lbluetooth

sdp-register: $(SDP-REGISTER_OBJ)
	$(CC) -o $@ $(CFLAGS) $(SDP-REGISTER_SRC) -L${libdir} -lbluetooth

new:
	$(MAKE) clean
	$(MAKE)

clean:
	-rm -f $(ALL) $(BTSCAN_OBJ) $(RFCOMM-SERVER_OBJ) $(RFCOMM-CLIENT_OBJ) $(L2CAP-SERVER_OBJ) $(L2CAP-CLIENT_OBJ) $(SDP-SEARCH_OBJ) $(SDP-REGISTER_OBJ)

