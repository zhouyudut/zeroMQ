#include "zhelpers.h"
#include <pthread.h>

static void *step1(void *context)
{
	void *xmitter = zmq_socket(context, ZMQ_PAIR);
	zmq_connect(xmitter, "inproc://step2");
	printf("step 1 ready, signaling step 2\n");
	s_send(xmitter, "READY");
	zmq_close(xmitter);
	return NULL;
}

static void *step2(void *context)
{
	void *recver = zmq_socket(context, ZMQ_PAIR);
	zmq_bind(recver, "inproc://step2");
	pthread_t threadId;
	pthread_create(&threadId, NULL, step1, context);
	
	char *string = s_recv(recver);
	free(string);
	zmq_close(recver);
	
	void *xmitter = zmq_socket(context, ZMQ_PAIR);
	zmq_connect(xmitter, "inproc://step3");
	printf("step 2 ready, signaling  step 3\n");
	s_send(xmitter, "READY");
	zmq_close(xmitter);
	return NULL;
}

int main(void)
{
	void *context = zmq_ctx_new();
	void *recver = zmq_socket(context, ZMQ_PAIR);
	zmq_bind(recver, "inproc://step3");
	pthread_t threadId;
	pthread_create(&threadId, NULL, step2, context);
	char *string = s_recv(recver);
	free(string);
	zmq_close(recver);
	printf("test successfully\n");
	zmq_ctx_destroy(context);
	return 0;
}
