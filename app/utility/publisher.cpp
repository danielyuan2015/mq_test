//服务端：
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <assert.h>
#include <zmq.h>

using namespace std;

int main ()
{
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, "tcp://*:5556");
    assert (rc == 0);

    //  Initialize random number generator
    srand(time(0));
    while (1) {
        int zipcode, temperature, relhumidity;
        zipcode     = rand() % 100000;
        temperature = rand() % 215 - 80;
        relhumidity = rand() % 50 + 10;

        ostringstream os;
        os << setw(5) << setfill('0')<< zipcode <<" "
           << temperature <<" "<< relhumidity << "\n";

        zmq_send(publisher, os.str().c_str(), strlen(os.str().c_str()), 0);
    }
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}