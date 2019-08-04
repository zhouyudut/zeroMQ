#include "zhelpers.h"
int main(void)
{
	void *context = zmq_ctx_new();
	void *receiver = zmq_socket(context, ZMQ_PULL);
	zmq_connect(receiver, "tcp://localhost:5557");
	void *suber = zmq_socket(context, ZMQ_SUB);
	zmq_connect(suber, "tcp://localhost:5556");
	zmq_setsockopt(suber, ZMQ_SUBSCRIBE, "10001", 6);
	
	zmq_pollitem_t items[] = {
		{receiver, 0, ZMQ_POLLIN, 0},
		{suber, 0, ZMQ_POLLIN, 0}
	};
	
	while (1) {
		zmq_msg_t msg;
		zmq_poll(items, 2, -1);
		if (items[0].revents & ZMQ_POLLIN) {
			zmq_msg_init(&msg);
			zmq_msg_recv(&msg, receiver, 0);
			// 处理任务
			zmq_msg_close(&msg);
		}
		if (items[1].revents & ZMQ_POLLIN) {
			zmq_msg_init(&msg);
			zmq_msg_recv(&msg, suber, 0);
			zmq_msg_close(&msg);
		}
	}
	zmq_close(receiver);
	zmq_close(suber);
	zmq_ctx_destroy(context);
	return 0;
}
/*
typedef struct{
	void *socket;
	int fd;
	short events;
	short revents;
}
*/
