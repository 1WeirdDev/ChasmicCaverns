#include "Packet.h"

#include <array>
#include <iostream>
#include <math.h>
#include <stdexcept>
#include <string>
#include <cstring>

namespace Networking {
	Packet::Packet(int packet_size) {
		this->packet_size = packet_size;
		data = new uint8_t[packet_size];
		std::fill(data, data + packet_size, 0);
		bit_index = 32;
	}
	Packet::Packet(int size, uint8_t* data) {
		packet_size = size;
		this->data = data;
		bit_index = 0;	//0 so we can read the length of the packet
		//Ideally the first thing we read in a buffer is its length
	}
	Packet::~Packet() {
		if (delete_data)
			DeleteData();
	}

	void Packet::DeleteData() {
		delete data;
		data = nullptr;
		packet_size = 0;
	}

	void Packet::WriteLength() {
		//The first 4 bytes are reserved just for packet length
		uint32_t bit = bit_index;
		bit_index = 0;

		//Get the bit index and divide it by 8 to get the last write pos in bytes
		//Since this includes the first 4 bytes being the length of the vector the size will be the actual length the buffer used
		WriteInt(bit / 8);

		bit_index = bit;
	}

	void Packet::WriteChar(int8_t value) {
		int32_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;

		data[byte_pos] |= value >> filled_bits;
		data[byte_pos + 1] |= (value & ((1 << remaining) - 1)) << remaining;

		bit_index += 8;
	}
	void Packet::WriteUChar(uint8_t value) {
		int32_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;

		data[byte_pos] |= value >> filled_bits;
		data[byte_pos + 1] |= (value & ((1 << remaining) - 1)) << remaining;

		bit_index += 8;
	}

	void Packet::WriteShort(int16_t value) {
		int32_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;

		data[byte_pos] |= value >> 16 >> filled_bits;
		data[byte_pos + 1] |= value >> filled_bits;
		data[byte_pos + 2] |= (value & ((1 << remaining) - 1)) << remaining;

		bit_index += 16;
	}
	void Packet::WriteUShort(uint16_t value) {
		int32_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;

		data[byte_pos] |= value >> 16 >> filled_bits;
		data[byte_pos + 1] |= value >> filled_bits;
		data[byte_pos + 2] |= (value & ((1 << remaining) - 1)) << remaining;

		bit_index += 16;
	}
	void Packet::WriteInt(int32_t value) {
		int32_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;

		data[byte_pos] |= (value >> 24) >> filled_bits;
		data[byte_pos + 1] |= (value >> 16) >> filled_bits;
		data[byte_pos + 2] |= (value >> 8) >> filled_bits;
		data[byte_pos + 3] |= value >> filled_bits;
		data[byte_pos + 4] |= (value & ((1 << remaining) - 1)) << remaining;

		bit_index += 32;
	}

	void Packet::WriteUInt(uint32_t value) {
		int32_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;

		data[byte_pos] |= (value >> 24) >> filled_bits;
		data[byte_pos + 1] |= (value >> 16) >> filled_bits;
		data[byte_pos + 2] |= (value >> 8) >> filled_bits;
		data[byte_pos + 3] |= value >> filled_bits;
		data[byte_pos + 4] |= (value & ((1 << remaining) - 1)) << remaining;

		bit_index += 32;
	}
	void Packet::WriteFloat(float value) {
		int32_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;

		union hello {
			float input;
			int32_t val;
		};
		hello f;
		f.input = value;
		data[byte_pos] |= (f.val >> 24) >> filled_bits;
		data[byte_pos + 1] |= (f.val >> 16) >> filled_bits;
		data[byte_pos + 2] |= (f.val >> 8) >> filled_bits;
		data[byte_pos + 3] |= f.val >> filled_bits;
		data[byte_pos + 4] |= (f.val & ((1 << remaining) - 1)) << remaining;

		bit_index += 32;
	}

	void Packet::WriteBool(bool value) {
		uint8_t index = bit_index % 8;
		data[bit_index / 8] |= (value << (7 - index));
		bit_index++;
	}

	void Packet::WriteString(const char* value) {
		for (int i = 0; i < strlen(value); i++) {
			WriteUChar((uint8_t)value[i]);
		}
		WriteUChar(0x00);
	}
	void Packet::WriteString(std::string& value) {
		for (int i = 0; i < value.size(); i++) {
			WriteUChar((uint8_t)value[i]);
		}
		WriteUChar(0x00);
	}
	void Packet::WriteString(std::string value) {
		for (int i = 0; i < value.size(); i++) {
			WriteChar((uint8_t)value[i]);
		}
		WriteChar(0x00);
	}

	void Packet::WriteUCharArray(size_t array_size, uint8_t* array) {
		WriteUInt(array_size);
		for (size_t i = 0; i < array_size; i++) {
			WriteUChar(array[i]);
		}
	}
	void Packet::WriteCharArray(size_t array_size, int8_t* array) {
		WriteUInt(array_size);
		for (size_t i = 0; i < array_size; i++) {
			WriteChar(array[i]);
		}
	}

	int8_t Packet::GetChar() {
#ifdef NETWORKING_READ_SAFE
		if (byte_pos / 8 + 2 <= packet_size) {
			throw std::range_error("Unable to read byte. Not enough bytes left to read.\n");
			return 0;
		}
#endif
		//A byte is 1 byte/8 bits
		int32_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;
		int8_t value = data[byte_pos] << filled_bits;
		value |= (data[byte_pos + 1] >> (8 - filled_bits));
		bit_index += 8;
		return value;
	}
	
	uint8_t Packet::GetUChar() {
#ifdef NETWORKING_READ_SAFE
		if (byte_pos / 8 + 2 <= packet_size) {
			throw std::range_error("Unable to read unsigned byte. Not enough bytes left to read.\n");
			return 0;
		}
#endif
		//A byte is 1 byte/8 bits
		int32_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;

		uint8_t value = data[byte_pos] << filled_bits;
		value |= (data[byte_pos + 1] >> (8 - filled_bits));
		bit_index += 8;
		return value;
		}


	int16_t Packet::GetShort() {
#ifdef NETWORKING_READ_SAFE
		if (byte_pos / 8 + 3 <= packet_size) {
			throw std::range_error("Unable to read short. Not enough bytes left to read.\n");
			return 0;
		}
#endif
		//An short is 2 bytes
		int32_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;

		int16_t value = (data[byte_pos]) << 16 << filled_bits;
		value |= data[byte_pos + 1] << filled_bits;
		value |= (data[byte_pos + 4] >> (8 - filled_bits));
		bit_index += 16;
		return value;
	}
	uint16_t Packet::GetUShort() {
#ifdef NETWORKING_READ_SAFE
		if (byte_pos / 8 + 3 <= packet_size) {
			throw std::range_error("Unable to read unsigned. Not enough bytes left to read.\n");
			return 0;
		}
#endif
		//An unsigned short is 2 bytes
		uint16_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;

		uint16_t value = (data[byte_pos]) << 16 << filled_bits;
		value |= data[byte_pos + 1] << filled_bits;
		value |= (data[byte_pos + 4] >> (8 - filled_bits));
		bit_index += 16;
		return value;
	}
	int32_t Packet::GetInt() {
#ifdef NETWORKING_READ_SAFE
		if (byte_pos / 8 + 5 <= packet_size) {
			throw std::range_error("Unable to read int. Not enough bytes left to read.\n");
			return 0;
		}
#endif
		//An integer is 4 bytes
		int32_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;

		int32_t value = (data[byte_pos]) << 24 << filled_bits;
		value |= (data[byte_pos + 1] << 16) << filled_bits;
		value |= (data[byte_pos + 2] << 8) << filled_bits;
		value |= (data[byte_pos + 3]) << filled_bits;
		value |= (data[byte_pos + 4] >> (8 - filled_bits));
		bit_index += 32;
		return value;
	}

	uint32_t Packet::GetUInt() {
#ifdef NETWORKING_READ_SAFE
		if (byte_pos / 8 + 5 <= packet_size) {
			throw std::range_error("Unable to read unsigned int. Not enough bytes left to read.\n");
			return 0;
		}
#endif
		//An integer is 4 bytes
		int32_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;

		uint32_t value = (data[byte_pos]) << 24 << filled_bits;
		value |= (data[byte_pos + 1] << 16) << filled_bits;
		value |= (data[byte_pos + 2] << 8) << filled_bits;
		value |= (data[byte_pos + 3] << filled_bits);
		value |= (data[byte_pos + 4] >> (8 - filled_bits));
		bit_index += 32;
		return value;
	}

	float Packet::GetFloat() {
#ifdef NETWORKING_READ_SAFE
		if (byte_pos / 8 + 5 <= packet_size) {
			throw std::range_error("Unable to read float. Not enough bytes left to read.\n");
			return 0;
		}
#endif
		//An float is 4 bytes
		int32_t byte_pos = bit_index / 8;
		uint8_t filled_bits = bit_index % 8;
		uint8_t remaining = 8 - filled_bits;

		int32_t value = (data[byte_pos]) << 24 << filled_bits;
		value |= (data[byte_pos + 1] << 16) << filled_bits;
		value |= (data[byte_pos + 2] << 8) << filled_bits;
		value |= (data[byte_pos + 3] << filled_bits);
		value |= (data[byte_pos + 4] >> (8 - filled_bits));
		bit_index += 32;

		//TODO: Make code better
		union hello {
			int input;
			float val;
		};

		hello f;
		f.input = value;
		return f.val;
	}


	bool Packet::GetBool() {
#ifdef NETWORKING_READ_SAFE
		if (byte_pos / 8 + 1 <= packet_size) {
			throw std::range_error("Unable to read bool. Not enough bytes left to read.\n");
			return 0;
		}
#endif
		uint8_t remaining = bit_index % 8;
		bool value = (1 & (data[bit_index / 8] >> (7 - bit_index))) > 0 ? true : false;
		bit_index++;
		return value;
	}

	std::string Packet::GetString() {
		//TODO: Catch errors
		std::string string;
		uint8_t byte = 0x00;
		while (true) {
			byte = GetChar();
			if (byte == 0x00 || bit_index / 8 >= packet_size)break;
			string += (char)byte;
		}

		return string;
	}
	uint8_t* Packet::GetUCharArray(size_t* length) {
		uint32_t size = GetUInt();
		*length = size;
		uint8_t* data = new uint8_t[size];
		for (uint32_t i = 0; i < size; i++) {
			data[i] = GetUChar();
		}

		return data;
	}
	int8_t* Packet::GetCharArray(size_t* length) {
		int32_t size = GetUInt();
		*length = size;
		int8_t* data = new int8_t[size];
		for (int32_t i = 0; i < size; i++) {
			data[i] = GetChar();
		}

		return data;
	}
}