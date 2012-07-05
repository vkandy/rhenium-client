/* 
 * File:   rhenium.h
 * Author: vkandy
 *
 * Created on July 4, 2012, 11:23 PM
 */

#ifndef RHENIUM_H
#define	RHENIUM_H

class rhenium
{
public:
    rhenium();
    rhenium(const rhenium& orig);
    virtual ~rhenium();
    
    static bool s_send(zmq::socket_t &socket, const std::string &string)
    {
        zmq::message_t message(string.size());
        memcpy(message.data(), string.data(), string.size());

        bool rc = socket.send(message);
        return (rc);
    }

    static std::string s_recv(zmq::socket_t &socket)
    {
        zmq::message_t message;
        socket.recv(&message);

        return std::string(static_cast<char*> (message.data()), message.size());
    }    
private:

};

#endif	/* RHENIUM_H */

