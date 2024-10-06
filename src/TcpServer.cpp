//
// Created by vlad on 06.10.24..
//

#include <fmt/format.h>
#include <easylogging++.h>
#include "TcpServer.h"

using fmt::format;

TcpServer::TcpServer(boost::asio::io_context &io_context, short port) :
    acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
  startAccept();
}
void TcpServer::startAccept()
{
  LOG(INFO) << "TCP Server start, listening for connections";
  acceptor_.async_accept(
    [this](boost::system::error_code ec, tcp::socket socket)
    {
      if (!ec)
      {
        // tcp connection will be defined soon;

        LOG(INFO) << format("Connection came in from {}:{}",
                            socket.remote_endpoint().address().to_string(),
                            socket.remote_endpoint().port());

        auto conn = std::make_shared<TcpConnection>(std::move(socket));
        conn->start();
      }
      else
      {
        LOG(WARNING) << format(
          "Connection failed with error code: {}, message {}", ec.value(),
          ec.message());
      }

      startAccept();
    });
}

void TcpConnection::start()
{
  LOG(INFO) << format(
    "Initialized TCP Listener Circular buffer with capacity: {}",
    message_buffer_.capacity());
  readMessage();
}

void TcpConnection::readMessage()
{
  auto self(shared_from_this());
  socket_.async_read_some(
    boost::asio::buffer(buffer_),
    [this, self](boost::system::error_code ec, std::size_t length)
    {
      if (!ec)
      {
        LOG(INFO) << "Read from TCP Socket into buffer....";
        std::string message(buffer_.data(), length);
        message_buffer_.push_back(message);
        LOG(INFO) << format("Message recieved: {}", message);
        processMessage(message);
        readMessage();
        buffer_.fill(0);
      }
      else
      {
        LOG(WARNING) << format(
          "Connection Ended with code: {}, message {}", ec.value(),
          ec.message());
      }
      printOutCircularBufferContents();
    });
}
void TcpConnection::processMessage(std::string &message)
{
  LOG(INFO) << format("Processing message {}", message);

  std::string response = "ACK";

  boost::asio::async_write(socket_, boost::asio::buffer(response),
    [this, self = shared_from_this(), response](boost::system::error_code ec, std::size_t len)
    {
      if (ec)
      {
        LOG(WARNING) << format("Failed sending response: {} to server", response);
      }
    });
}

void TcpConnection::printOutCircularBufferContents()
{
  LOG(INFO) << "Logging circular buffer contents";
  for (auto& stored_msg : message_buffer_)
  {
    LOG(INFO) << stored_msg;
  }
}
