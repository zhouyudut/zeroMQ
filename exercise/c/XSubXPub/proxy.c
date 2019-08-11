#include "zhelpers.h"
int main()
{
	void *context = zmq_ctx_new();
	void *xsuber = zmq_socket(context, ZMQ_DEALER);
	zmq_connect(xsuber, "tcp://localhost:5559");
	void *xpuber = zmq_socket(context, ZMQ_ROUTER);
	zmq_bind(xpuber, "tcp://*:5560");
	
	zmq_proxy(xsuber, xpuber, NULL);
	zmq_close(xsuber);
	zmq_close(xpuber);
	zmq_ctx_destroy(context);
	return 0;
}
