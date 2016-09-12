//
//  main.cpp
//  PacketSerializer
//
//  Created by 신일환 on 2016. 9. 10..
//  Copyright © 2016년 acoross. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <type_traits>
#include <sstream>
#include <strstream>

#include "packet_serializer_1.hpp"
#include "packet_serializer_1_types.hpp"
#include "packet_serializer_2.hpp"
#include "packet_serializer_3.hpp"

#include "Cereal/cereal.hpp"
#include "Cereal/archives/binary.hpp"

namespace packet_serializer_1 {
	class MyPacket : public Packet {
	public:
		IntType i_val_{ this };
		CharType c_val_{ this };
		StringType str_val_{ this };
	};
}

namespace packet_serializer_2 {
	class InnerStruct : public Struct {
	public:
		StructVal<CharType> c_val_{ this };
		StructVal<StringType> str_val_{ this };
	};

	struct InnerStruct2 {
		int a{0};
		char b{1};
		unsigned char data[100]{0,};
	};

	class MyPacket2 : public Struct {
	public:
		StructVal<IntType> i_val_{ this };
		StructVal<StringType> str_val_{ this };
		StructVal<ListType<ShortType>> l_val_{ this };
		StructVal<InnerStruct> struct_val_{ this };

		StructVal<RawType<InnerStruct2>> struct2_val_{this};
	};
}

namespace Datagram {
	template <typename T, bool _cond = std::is_integral<T>::value>
	class DataSerializer;

	template <typename T>
	class DataSerializer<T, true> {
	public:
		static unsigned char* _Serialize(
			unsigned char* buffer, T data)
		{
			memcpy(buffer, (void*)&data, sizeof(data));
			return buffer + sizeof(data);
		}
	};

	template <typename T>
	class DataSerializer<T, false> {
	public:
		static unsigned char* _Serialize(
			unsigned char* buffer, T data)
		{
			memcpy(buffer, (void*)&data, sizeof(data));
			return buffer + sizeof(data);
		}
	};

	template <typename T>
	unsigned char* serialize(unsigned char* buffer, T data) {
		return DataSerializer<T>::_Serialize(buffer, data);
	}

	template <typename T>
	unsigned char* serialize(unsigned char* buffer, T* data) {
		static_assert(0, "cannot serialize pointer");
		return buffer;
	}
}

void test1() {
	using namespace packet_serializer_1;

	MyPacket packet;
	packet.i_val_.data_ = 0xcdcdffab;
	packet.c_val_.data_ = 'c';
	packet.str_val_.data_ = std::string("bakashinji");

	unsigned char buffer[100]{ 0, };
	packet.Serialize(buffer);

	int i;
	i = 10;
}

void test2() {
	using namespace packet_serializer_2;

	MyPacket2 packet;
	packet.i_val_.data_ = 0xcdcdffab;
	packet.str_val_.data_ = "bakashinji";
	for (int i = 0; i < 10; ++i) {
		packet.l_val_.data_list_.push_back(i);
	}

	packet.struct_val_.c_val_.data_ = 0x7f;
	packet.struct_val_.str_val_.data_ = "acoross";

	packet.struct2_val_.data_.a = 1;
	//packet.struct2_val_.data_.b = 2;
	packet.struct2_val_.data_.data[0] = 0xab;

	unsigned char buffer[100]{ 0, };
	packet.Serialize(buffer);

	int i;
	i = 10;
}

int main(int argc, const char * argv[]) {

	std::strstream strs;
	std::stringbuf sb;
	std::stringstream ss;
	//ss.set_rdbuf(&sb);	//basic_ios:: _Mysb *_Mystrbuf;

	{
		cereal::BinaryOutputArchive ar(ss);
		ar('s', 'e', 'x');	//itsStream.rdbuf()->sputn(...)
	}

	std::cout << "sb: " << sb.str() << std::endl;
	std::cout << "ss: " << ss.str() << std::endl;
		// ss.str() : _Mysb _Stringbuffer;	// the string buffer

	return 0;
}
