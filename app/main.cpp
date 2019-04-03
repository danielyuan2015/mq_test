#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

/*struct args {
	bool isServer;
	//string mqttIPAddress;
};

static struct args args = {
		.isServer = true,
};
static const char optionsstr[] =
		"-p  Publish mode\n"
		"-s  Subscribe mode\n";
//		"-p  Mqtt server address\n";

static const char usage[] =
		"Usage: " APP_NAME "[-p] [-s]";

static int parse_opt(int argc, char * const argv[])
{
	int c;

	while ((c = getopt(argc, argv, "sc")) != -1) {
		switch (c) {
		case 's':
			args.isServer = true;
			break;
		case 'c':
			args.isServer = false;
			break;
		case 'p':
			break;
		default:
			printf("%s\n\n", usage);
			printf("%s\n", optionsstr);
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}*/
static int interrupted = 0;

void signal_handler(int sig)
{
    (void)sig;
    interrupted = 1;
}

void catch_signals(void)
{
    struct sigaction action;
    action.sa_handler = signal_handler;
    action.sa_flags = 0;
    sigemptyset (&action.sa_mask);
    sigaction (SIGINT, &action, NULL);
}

void dump_msg(const void * data, int size)
{
    //printf("dump_msg\r\n");
    unsigned char * ptr = (unsigned char *)data;
    printf ("[%03d] ", size);
    int i = 0;
    for (i = 0; i < size; i++)
    printf ("%02X", ptr[i]);
    printf ("\n");
}

int main(void)
{
    catch_signals();
    void *context = zmq_ctx_new();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    /*订阅任何内容*/
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);
    zmq_connect (subscriber, "tcp://127.0.0.1:5555");

    int ret;
    zmq_pollitem_t item[] = {{subscriber, 0, ZMQ_POLLIN, 0}};
    while (!interrupted) {
        ret = zmq_poll(item, 1, -1);
        if(ret == -1)
            perror("zmq_poll");
        if(item[0].revents & ZMQ_POLLIN) {
            zmq_msg_t msg;
            zmq_msg_init(&msg);
            ret = zmq_msg_recv (&msg, subscriber, 0);
            dump_msg(zmq_msg_data(&msg), ret);
            zmq_msg_close(&msg);
        }
    }

    //  程序不会运行到这里，以下只是演示我们应该如何结束
    zmq_close (subscriber);
    zmq_ctx_destroy(context);
    return 0;
}