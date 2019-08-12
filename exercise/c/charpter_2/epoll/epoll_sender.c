#include "zhelpers.h"
int main()
{
	void *context = zmq_ctx_new();
	void *pusher = zmq_socket(context, ZMQ_PUSH);
	zmq_bind(pusher, "tcp://*:5557");
	void *puber = zmq_socket(context, ZMQ_PUB);
	zmq_bind(puber, "tcp://*:5556");
	srandom((unsigned)time(NULL));
	int32_t count = 0;
	while (1) {
		int32_t zipcode, temperature, relhumidity;
		zipcode = randof(100000);
		temperature = randof(215) - 80;
		relhumidity = randof(50) + 10;
		
		char update[20];
		sprintf(update, "%05d %d %d", zipcode, temperature, relhumidity);
		count++;
		if (count % 100 == 0) {
			s_send(pusher, update);
		} else {
			s_send(puber, update);
		}
	}
	zmq_close(puber);
	zmq_close(pusher);
	zmq_ctx_destroy(context);
}
