#pragma once

#include <vector>
#include <system_error>
#include <functional>
#include <array>
#include <map>
#include <mutex>

#include <Networking/Core.h>
#include <Networking/Packet.h>

namespace Networking {
	class TCPServer;
	extern "C" NETWORKING_API class TCPConnection {
	public:
		TCPConnection(TCPServer* server, void* socket);
		~TCPConnection();

		void Disconnect();

		void AsyncRead();
		void AsyncWrite();
		void Post(Packet* packet, bool delete_packet_data = true);

		void OnRead(const std::error_code& error, std::size_t bytes_transferred);
		void OnWrite(const std::error_code& error, std::size_t bytes_transferred);
		
		bool NoValidMessages();

		unsigned short id = 0;
	private:
		static std::mutex mutex;
		TCPServer* server = nullptr;
		std::array<unsigned char, NETWORKING_MAX_PACKET_SIZE> read_buffer;
		std::vector<Message> messages;

		bool is_writing = false;
		void* socket = nullptr;
	};
	extern "C" NETWORKING_API class TCPServer {
	public:
		TCPServer();
		~TCPServer();

		void Start(int port, unsigned short max_players = 20);
		void Stop();
		void Tick();

		//Sends packet to certain client
		void SendPacket(unsigned short id, Packet* packet, bool delete_packet_data = true);
		//Sends packet to all connected clients
		void SendPacket(Packet* packet, bool delete_packet_data = true);

		void OnDisconnect(TCPConnection* connection);

		std::function<void()> on_server_started;
		std::function<void(bool, const char*)> on_server_stopped;
		std::function<void(std::error_code ec)> on_server_start_failed;

		std::function<void(unsigned short)> on_client_connected;
		std::function<void(const char*)> on_client_failed_connect;
		std::function<void(unsigned short)> on_client_disconnected;

		std::function<void(unsigned short, Packet*, size_t)> on_packet_read;
		std::function<void(unsigned short, size_t)> on_packet_wrote;
	private:
		void* io_context;
		void* acceptor;
		void* socket;
		void StartAccept();

		void OnAccept(const std::error_code& e);
		std::map<unsigned short, TCPConnection*> connections;

		int port;
		unsigned short max_players;
	};
}