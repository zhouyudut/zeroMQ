#include "zhelpers.h"

int main()
{
	void *context = zmq_ctx_new();
	void *client = zmq_socket(context, ZMQ_REQ);
	zmq_connect(client, "tcp://localhost:5559");
	int32_t nbr;
	for (nbr = 0; nbr < 10; nbr++) {
		s_send(client, "hello");
		char *string = s_recv(client);
		printf("recv response: [%s]\n", string);
	}
	zmq_close(client);
	zmq_ctx_destroy(context);
}
