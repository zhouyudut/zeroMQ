#include "zhelpers.h"
#include <pthread.h>

static void *WorkerThread(void *context)
{
	void *recver = zmq_socket(context, ZMQ_REP);
	zmq_connect(recver, "inproc://server");
	
	while (1) {
		char *string = s_recv(recver);
		printf("recv request: [%s]\n", string);
		free(string);
		s_sleep(1);
		s_send(recver, "world");
	}
	zmq_close(recver);
	return NULL;
}

int main(void)
{
	void *context = zmq_ctx_new();
	void *clients = zmq_socket(context, ZMQ_ROUTER);
	zmq_bind(clients, "tcp://*:5559");
	void *server = zmq_socket(context, ZMQ_DEALER);
	zmq_bind(server, "inproc://server");
	
	int32_t thread_nbr;
	for (thread_nbr = 0; thread_nbr < 5; thread_nbr++) {
		pthread_t worker;
		pthread_create(&worker, NULL, WorkerThread, context);
	}
	zmq_proxy(server, clients, NULL);
	
	zmq_close(clients);
	zmq_close(server);
	zmq_ctx_destroy(context);
	return 0;
}
