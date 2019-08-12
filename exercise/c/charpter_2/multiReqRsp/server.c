#include "zhelpers.h"
int main(void)
{
	void *context = zmq_ctx_new();
	void *responder = zmq_socket(context, ZMQ_REP);
	zmq_connect(responder, "tcp://localhost:5560");
	
	while(1) {
		char *string = s_recv(responder);
		printf("recv request: [%s]\n", string);
		free(string);
		s_sleep(1);
		s_send(responder, "world");
	}
	
	zmq_close(responder);
	zmq_ctx_destroy(context);
	return 0;
}
