#include "zhelpers.h"

int main(void)
{
	void *context = zmq_ctx_new();
	void *receiver = zmq_socket(context, ZMQ_PULL);
	zmq_bind(receiver, "tcp://*:5558");
	
	char *string = s_recv(receiver);
	free(string);
	
	int64_t start_time = s_clock();
	
	int32_t task_nbr;
	for (task_nbr = 0; task_nbr < 100; task_nbr++) {
		char *string = s_recv(receiver);
		free(string);
		if (task_nbr % 10 == 0) {
			printf(":");
		} else {
			printf(".");
		}
		fflush(stdout);
	}
	printf("Total elapsed time: %d msec\n", (int32_t)(s_clock() - start_time));
	zmq_close(receiver);
	zmq_ctx_destroy(context);
	return 0;
}
