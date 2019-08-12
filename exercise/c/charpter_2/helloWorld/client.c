#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	void *context = zmq_ctx_new();
	printf("Connecting to helloWorld server\n");
	void *requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, "tcp://localhost:5555");
	zmq_msg_t request;
	zmq_msg_init_size(&request, 5);
	memcpy(zmq_msg_data(&request), "hello", 5);
	printf("Sending Hello %d...\n", 1);
	zmq_msg_send(&request, requester, 0);
	zmq_msg_close(&request);
	zmq_msg_t reply;
	zmq_msg_init(&reply);
	zmq_msg_recv(&reply, requester, 0);
	printf("Recv World");
	zmq_msg_close(&reply);
	sleep(2);
	zmq_close(requester);
	zmq_ctx_destroy(context);
	return 0;
}