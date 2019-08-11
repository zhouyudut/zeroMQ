#include "zhelpers.h"

int main()
{
	void *context = zmq_ctx_new();
	void *suber = zmq_socket(context, ZMQ_SUB);
	zmq_connect(suber, "tcp://localhost:5559");
	zmq_setsockopt(suber, ZMQ_SUBSCRIBE, "B", 1);
	
	while (1) {
		char *address = s_recv(suber);
		char *contents = s_recv(suber);
		printf("[%s] %s\n", address, contents);
		free(address);
		free(contents);
	}
}