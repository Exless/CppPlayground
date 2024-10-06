//
// Created by vlad on 06.10.24..
//

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <boost/asio.hpp>
#include <boost/circular_buffer.hpp>
using boost::asio::ip::tcp;


class TcpServer {
public:
  TcpServer(boost::asio::io_context& io_context, short port);
  virtual ~TcpServer() = default;
private:
  tcp::acceptor acceptor_;
  void startAccept();
};

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
  TcpConnection(tcp::socket socket): socket_(std::move(socket)), message_buffer_(4)
  {
  }
  void start();

private:
  void readMessage();
  void processMessage(std::string& message);
  tcp::socket socket_;
  std::array<char, 1024> buffer_;
  boost::circular_buffer<std::string> message_buffer_;
  void printOutCircularBufferContents();
};



#endif //TCPSERVER_H
