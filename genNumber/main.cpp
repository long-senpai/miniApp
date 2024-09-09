//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: WebSocket server, synchronous
//
//------------------------------------------------------------------------------

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

namespace beast = boost::beast;        
namespace http = beast::http;          
namespace websocket = beast::websocket;
namespace net = boost::asio;           
using tcp = boost::asio::ip::tcp;      

//------------------------------------------------------------------------------

void
do_session(tcp::socket socket)
{
    try
    {
        // Construct the stream by moving in the socket
        websocket::stream<tcp::socket> ws{std::move(socket)};

        // Set a decorator to change the Server of the handshake
        ws.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res)
            {
                res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-server-sync");
            }));

        // Accept the websocket handshake
        ws.accept();
        int number = 0;
        while (true) {
            std::string message = std::to_string(number);
            ws.write(net::buffer(message));  // Send the number as a string

            std::cout << "Sent: " << message << std::endl;
            number++;  // Increment the number

            // Sleep for 1 second before sending the next number
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const beast::system_error& se) {
        std::cerr << "WebSocket session error: " << se.what() << std::endl;
    }
}


int main()
{
    try
    {
        net::io_context ioc;
        tcp::acceptor acceptor{ioc, tcp::endpoint{tcp::v4(), 8080}};

        while (true) {
            tcp::socket socket{ioc};

            // Wait for a client connection
            acceptor.accept(socket);

            // Launch a new thread to handle the WebSocket session
            std::thread{&do_session, std::move(socket)}.detach();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}