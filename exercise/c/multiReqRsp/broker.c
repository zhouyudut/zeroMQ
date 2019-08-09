#include "zhelpers.h"
int main(void)
{
	void *context = zmq_ctx_new();
	void *router = zmq_socket(context, ZMQ_ROUTER);
	void *dealer = zmq_socket(context, ZMQ_DEALER);
	zmq_bind(router, "tcp://*:5559");
	zmq_bind(dealer, "tcp://*:5560");
	zmq_pollitem_t items[] = {
		{router, 0, ZMQ_POLLIN, 0},
		{dealer, 0, ZMQ_POLLIN, 0}
	};
	
	while (1) {
		zmq_msg_t msg;
		int more;
		zmq_poll(items, 2, -1);
		if (items[0].revents & ZMQ_POLLIN) {
			while (1) {
				zmq_msg_init(&msg);
				zmq_msg_recv(&msg, router, 0);
				size_t more_size = sizeof(more);
				zmq_getsockopt(router, ZMQ_RCVMORE, &more, &more_size);
				zmq_msg_send(&msg, dealer, more ? ZMQ_SNDMORE : 0);
				zmq_msg_close(&msg);
				if (!more) {
					break;
				}
			}
		}
		if (items[1].revents & ZMQ_POLLIN) {
			while (1) {
				zmq_msg_init(&msg);
				zmq_msg_recv(&msg, dealer, 0);
				size_t more_size = sizeof(more);
				zmq_getsockopt(dealer, ZMQ_RCVMORE, &more, &more_size);
				zmq_msg_send(&msg, router, more ? ZMQ_SNDMORE : 0);
				zmq_msg_close(&msg);
				if (!more) {
					break;
				}
			}
		}
	}
	zmq_close(dealer);
	zmq_close(router);
	zmq_ctx_destroy(context);
}
