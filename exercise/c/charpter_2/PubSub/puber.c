#include "zhelpers.h"
int main(void)
{
	void *context = zmq_ctx_new();
	void *publisher = zmq_socket(context, ZMQ_PUB);
	int rc = zmq_bind(publisher, "tcp://*:5556");
	if (rc != 0) {
		printf("zmq_bind error");
//		return 0;
	}
//        rc = zmq_bind(publisher, "ipc://weather.ipc");	
	srandom((unsigned)time(NULL));
	int32_t count = 0;
	while(1)
	{
		int32_t zipcode, tmperature, relhumidity;
	//	zipcode = randof(100000);
		zipcode = 10001;
		tmperature = randof(215) - 80;
		relhumidity = randof(50) + 10;
		
		char update[20];
		sprintf(update, "%05d %d %d", zipcode, tmperature, relhumidity);
		count++;
		if (count == 1) {
			printf("%05d before send\n", zipcode);
		}
		s_send(publisher, update);
	}
	zmq_close(publisher);
	zmq_ctx_destroy(context);
	return 0;
}
