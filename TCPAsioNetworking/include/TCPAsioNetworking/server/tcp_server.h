//
// Created by ozzadar on 2021-08-22.
//

#pragma once

#include <boost/asio.hpp>
#include <TCPAsioNetworking/server/tcp_connection.h>
#include <functional>
#include <optional>
#include <unordered_set>

namespace TCPAsio {
    namespace io = boost::asio;

    enum class IP_VERSION {
        IP_V4,
        IP_V6
    };

    class TCPServer {
        using OnJoinHandler = std::function<void(TCPConnection::tcp_connection)>;
        using OnLeaveHandler = std::function<void(TCPConnection::tcp_connection)>;
        using OnClientMessageHandler = std::function<void(std::string)>;

    public:
        TCPServer(IP_VERSION ipv, int port);

        int Run();
        void Broadcast(const std::string& message);
    private:
        void startAccept();

    public:
        OnJoinHandler OnJoin;
        OnLeaveHandler OnLeave;
        OnClientMessageHandler OnClientMessage;

    private:
        IP_VERSION _ipVersion;
        int _port;

        io::io_context io_context_;
        io::ip::tcp::acceptor  acceptor_;
        std::optional<io::ip::tcp::socket> socket_;
        std::unordered_set<TCPConnection::tcp_connection> connections_ {};
    };
}


