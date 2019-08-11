#include "zhelpers.h"

int main(void)
{
	void *context = zmq_ctx_new();
	void * puber = zmq_socket(context, ZMQ_PUB);
	zmq_bind(puber, "tcp://*:5559");
	
	while (1) {
		s_sendmore(puber, "A");
		s_send(puber, "we don't want see it");
		s_sendmore(puber, "B");
		s_send(puber, "we want see it");
		s_sleep(1);
	}
	zmq_close(puber);
	zmq_ctx_destroy(context);
	return 0;
}