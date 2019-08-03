#include "zhelpers.h"
int main(void)
{
	void *context = zmq_ctx_new();
	void *sender = zmq_socket(context, ZMQ_PUSH);
	zmq_bind(sender, "tcp://*:5557");
	void *sink = zmq_socket(context, ZMQ_PUSH);
	zmq_connect(sink, "tcp://lcoalhost:5558");
	printf("press enter when the workers are ready");
	getchar();
	printf("sending tasks to workers...\n");
	
	s_send(sink, "0");
	srandom((unsigned)time(NULL));
	
	int32_t task_nbr;
	int32_t total_msc = 0;
	for (task_nbr = 0; task_nbr < 100; task_nbr++) {
		int32_t workload;
		workload = randof(100) + 1;
		total_msc += workload;
		char string[10];
		sprintf(string, "%d", workload);
		s_send(sender, string);
	}
	printf("total expected cost: %d msec\n", total_msc);
	s_sleep(1);
	
	zmq_close(sink);
	zmq_close(sender);
	zmq_ctx_destroy(context);
	return 0;
}
