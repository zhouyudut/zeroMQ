#include "zhelpers.h"
int main(void)
{
	void *context = zmq_ctx_new();
	void *suber = zmq_socket(context, ZMQ_SUB);
	zmq_setsockopt(suber, ZMQ_SUBSCRIBE, "E", 1);
	zmq_connect(suber, "tcp://localhost:5559");
	
	void *syncClient = zmq_socket(context, ZMQ_REQ);
	zmq_connect(syncClient, "tcp://localhost:5560");
	
	s_sleep(1);
	s_send(syncClient, "");
	printf("suber send one sync msg\n");
	char *string = s_recv(syncClient);
	printf("suber recv one sync msg\n");
	free(string);
	s_sleep(1);	
	int update_nbr = 0;
	
	while (1) {
		char *string = s_recv(suber);
		if (strcmp(string, "END") == 0) {
			free(string);
			break;
		}
		update_nbr++;
		free(string);
	}
	printf("Recv %d updates\n", update_nbr);
	zmq_close(syncClient);
	zmq_close(suber);
	zmq_ctx_destroy(context);
	printf("suber over\n");
	return 0;
}
