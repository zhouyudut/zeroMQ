#include“zhelpers.h"
int main(void)
{
	int32_t major;
	int32_t minor;
	int32_t patch;
	zmq_version(&major, &minor, &patch);
	printf("Current ZMQ version is %d.%d.%d\n", major, minor, patch);
	return 0;
}