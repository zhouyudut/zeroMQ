#include "zhelpers.h"

#define SUBSCRIBERS_EXPECTED 10

int main(void)
{
	void *context = zmq_ctx_new();
	void *puber = zmq_socket(context, ZMQ_PUB);
	zmq_bind(puber, "tcp://*:5559");
	void *syncRecver = zmq_socket(context, ZMQ_REP);
	zmq_bind(syncRecver, "tcp://*:5560");
	
	printf("waiting for subscribers\n");
	int subscribers = 0;
	while (subscribers < SUBSCRIBERS_EXPECTED) {
		char *string = s_recv(syncRecver);
		free(string);
		s_send(syncRecver, "");
		printf(" puber recv one sync msg\n");
		subscribers++;
	}
	s_sleep(5);	
	printf("Broadcasting messages\n");
	int32_t update_nbr;
	for (update_nbr = 0; update_nbr < 1000; update_nbr++) {
		s_send(puber, "ERhubarb");
	}
	s_send(puber, "END");

	printf("send broadcasting msg over\n");
	while(1);
	zmq_close(puber);
	zmq_close(syncRecver);
	zmq_ctx_destroy(context);
	return 0;
}
