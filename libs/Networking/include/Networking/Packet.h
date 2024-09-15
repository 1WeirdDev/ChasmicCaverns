#pragma once

#include <string>
#include <array>
#include <cstdint>

#include <Networking/Core.h>

/*
NETWORKING_PACKET_SIZE is by default 2048 bytes
This is a arbitrary number no reason for it being picked
Should Normally read 2048 bytes but for writing just write GetUsedSize() bytes;
*/
#ifndef NETWORKING_MAX_PACKET_SIZE
#define NETWORKING_MAX_PACKET_SIZE 2048
#endif

//NETWORKING_READ_SAFE
/*
if NETWORKING_READ_SAFE is defined then checks will happen to make sure we dont read outside of pack bounds
this should be used on the server incase client sends invalid packet(hacket maybe)
*/

namespace Networking {
	class Packet {
	public:
		//This is just a default value
		NETWORKING_API Packet(int packet_size = NETWORKING_MAX_PACKET_SIZE);
		NETWORKING_API Packet(int size, unsigned char* data);
		NETWORKING_API ~Packet();

		NETWORKING_API void DeleteData();
		NETWORKING_API void WriteLength();
		NETWORKING_API int GetUsedSize() const { return bit_index / 8 + 1; }

		//Maybe we can save some size in the library by having these writing functions-
		//Maybe write only 1 2 3 or 4 bytes.
		//TODO: Add a check when writing to see if we have available space
		NETWORKING_API void WriteChar(int8_t value);
		NETWORKING_API void WriteUChar(uint8_t value);
		NETWORKING_API void WriteShort(int16_t value);
		NETWORKING_API void WriteUShort(uint16_t value);
		NETWORKING_API void WriteInt(int32_t value);	//Will always be 4 bytes
		NETWORKING_API void WriteUInt(uint32_t value);
		NETWORKING_API void WriteFloat(float value);
		NETWORKING_API void WriteBool(bool value);
		NETWORKING_API void WriteString(const char* value);
		NETWORKING_API void WriteString(std::string& value);
		NETWORKING_API void WriteString(std::string value);

		NETWORKING_API void WriteUCharArray(size_t array_size, uint8_t* array);
		NETWORKING_API void WriteCharArray(size_t array_size, int8_t* array);
		
		NETWORKING_API int8_t GetChar();
		NETWORKING_API uint8_t GetUChar();
		NETWORKING_API int16_t GetShort();
		NETWORKING_API uint16_t GetUShort();
		NETWORKING_API int32_t GetInt();
		NETWORKING_API uint32_t GetUInt();
		NETWORKING_API float GetFloat();
		NETWORKING_API bool GetBool();
		NETWORKING_API std::string GetString();
		NETWORKING_API uint8_t* GetUCharArray(size_t* length);
		NETWORKING_API int8_t* GetCharArray(size_t* length);

		//NETWORKING_API unsigned char* GetData() { return data; }
		uint8_t* GetData() const { return data; }
	private:
		uint8_t* data = nullptr;	//The actual data inside the packet
		uint32_t bit_index = 0;	// The index that you can start writing or reading data at
		uint32_t packet_size = 0; // The size when reading for data
		bool delete_data = false; //On deconstructed should we delete packet data aswell?
	};

	struct Message {
		Packet* packet = nullptr;
		bool delete_packet = true;
		unsigned short amount_sent = 0;

		Message(Packet* packet, bool delete_packet = true) {
			this->packet = packet;
			this->delete_packet = delete_packet;
		}
	};
}