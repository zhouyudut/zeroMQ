#include "zhelpers.h"
int main()
{
	void *context = zmq_ctx_new();
	void *router = zmq_socket(context, ZMQ_ROUTER);
	int rc = zmq_bind(router, "tcp://*:5559");
	void *dealer = zmq_socket(context, ZMQ_DEALER);
	rc = zmq_bind(dealer, "tcp://*:5560");
	
	zmq_proxy(router, dealer, NULL);
	
	zmq_close(router);
	zmq_close(dealer);
	zmq_ctx_destroy(context);
	return 0;
}
