CC=$(CROSS_COMPILE)gcc
STRIP=$(CROSS_COMPILE)strip
INC = -I. 
CFLAGS=	-g -O2 -Wall $(INC) 

UDP_SERVER_OBJ=udp_server.o
UDP_SERVER_SRC=$(UDP_SERVER_OBJ:.o=.c)

UDP_CLIENT_OBJ=udp_client.o
UDP_CLIENT_SRC=$(UDP_CLIENT_OBJ:.o=.c)

TCP_SERVER_OBJ=tcp_server.o
TCP_SERVER_SRC=$(TCP_SERVER_OBJ:.o=.c)

TCP_CLIENT_OBJ=tcp_client.o
TCP_CLIENT_SRC=$(TCP_CLIENT_OBJ:.o=.c)

NTP_CLIENT_OBJ=ntp_client.o
NTP_CLIENT_SRC=$(NTP_CLIENT_OBJ:.o=.c)

LOCATION_CLIENT_OBJ=location_client.o
LOCATION_CLIENT_SRC=$(LOCATION_CLIENT_OBJ:.o=.c)

WEATHER_CLIENT_OBJ=weather_client.o
WEATHER_CLIENT_SRC=$(WEATHER_CLIENT_OBJ:.o=.c)

ALL=udp-server udp-client tcp-server tcp-client ntp location weather

all: $(ALL)

udp-server: $(UDP_SERVER_OBJ)
	$(CC) -o $@ $(CFLAGS) $(UDP_SERVER_SRC) 

udp-client: $(UDP_CLIENT_OBJ)
	$(CC) -o $@ $(CFLAGS) $(UDP_CLIENT_SRC)

tcp-server: $(TCP_SERVER_OBJ)
	$(CC) -o $@ $(CFLAGS) $(TCP_SERVER_SRC)

tcp-client: $(TCP_CLIENT_OBJ)
	$(CC) -o $@ $(CFLAGS) $(TCP_CLIENT_SRC)

ntp: $(NTP_CLIENT_OBJ)
	$(CC) -o $@ $(CFLAGS) $(NTP_CLIENT_SRC)

location: $(LOCATION_CLIENT_OBJ)
	$(CC) -o $@ $(CFLAGS) $(LOCATION_CLIENT_SRC)

weather: $(WEATHER_CLIENT_OBJ)
	$(CC) -o $@ $(CFLAGS) $(WEATHER_CLIENT_SRC)

new:
	$(MAKE) clean
	$(MAKE)

clean:
	-rm -f $(ALL) $(WEATHER_CLIENT_OBJ) $(LOCATION_CLIENT_OBJ) $(TCP_SERVER_OBJ) $(TCP_CLIENT_OBJ) $(UDP_SERVER_OBJ) $(UDP_CLIENT_OBJ) $(NTP_CLIENT_OBJ)

