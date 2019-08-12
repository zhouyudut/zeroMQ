#include "zhelpers.h"
int main(int argc, char *argv[])
{
	void *context = zmq_ctx_new();
	printf("Collecting updates from weather server...\n");
	void *suber = zmq_socket(context, ZMQ_SUB);
	char *filter = "10001";
	int32_t rc = zmq_setsockopt(suber, ZMQ_SUBSCRIBE, filter, strlen(filter));
	rc = zmq_connect(suber, "tcp://localhost:5556");
	if (rc != 0) {
		printf("zmq_connect failed");
//		return 0;
	}
	
//	char *filter = (argc > 1) ? argv[1] : "10001 ";
//	rc = zmq_setsockopt(suber, ZMQ_SUBSCRIBE, filter, strlen(filter));
	if (rc != 0) {
		printf("zmq_setsockopt failed");
//		return 0;
	}
	
	int32_t update_nbr;
	uint32_t total_temp = 0;
	for (update_nbr = 0; update_nbr < 100; update_nbr++) {
		char *string = s_recv(suber);
		
		int32_t zipcode;
		int32_t temperature;
		int32_t relhumidity;
		sscanf(string, "%d %d %d", &zipcode, &temperature, &relhumidity);
		total_temp += temperature;
		free(string);
		printf("recv %u messages\n", update_nbr + 1);
	}
	printf("Average tempature for zipcode '%s' was %dF\n", filter, (int32_t)(total_temp/update_nbr));
	zmq_close(suber);
	zmq_ctx_destroy(context);
	return 0;
}
