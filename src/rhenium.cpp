/* 
 * File:   rhenium.cpp
 * Author: vkandy
 * 
 * Created on July 4, 2012, 11:23 PM
 */
#include <cstdlib>
#include <iostream>
#include <zmq.hpp>
#include "rhenium.h"

rhenium::rhenium()
{
}

rhenium::rhenium(const rhenium& orig)
{
}

rhenium::~rhenium()
{
}

/**
 * Rhenium client that subscribes to rheniumd server. Messages are printed to 
 * stdout or to a file.
 */
int main(int argc, char** argv)
{
    zmq::context_t context(1);

    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.setsockopt(ZMQ_IDENTITY, "rhenium", 5);
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    subscriber.connect("tcp://localhost:5565");

    zmq::socket_t sync(context, ZMQ_PUSH);
    sync.connect("tcp://localhost:5564");
    rhenium::s_send(sync, "");

    while (true)
    {
        std::string string = rhenium::s_recv(subscriber);
        std::cout << string << std::endl;
    }

    return EXIT_SUCCESS;
}
