//
//  main.cpp
//  PacketSerializer
//
//  Created by 신일환 on 2016. 9. 10..
//  Copyright © 2016년 acoross. All rights reserved.
//

#include <iostream>
#include <tuple>

#include "packet_serializer_1.hpp"
#include "packet_serializer_1_types.hpp"

#include "packet_serializer_2.hpp"

#include "packet_serializer_3.hpp"

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

	class MyPacket2 : public Struct {
	public:
		StructVal<IntType> i_val_{ this };
		StructVal<StringType> str_val_{ this };
		StructVal<ListType<ShortType>> l_val_{ this };
		StructVal<InnerStruct> struct_val_{ this };
	};
}

int main(int argc, const char * argv[]) {
	{
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

	{
		using namespace packet_serializer_2;

		MyPacket2 packet;
		packet.i_val_.data_ = 0xcdcdffab;
		packet.str_val_.data_ = "bakashinji";
		for (int i = 0; i < 10; ++i) {
			packet.l_val_.data_list_.push_back(i);
		}

		packet.struct_val_.c_val_.data_ = 0xfa;
		packet.struct_val_.str_val_.data_ = "acoross";

		unsigned char buffer[100]{ 0, };
		packet.Serialize(buffer);

		int i;
		i = 10;
	}


	return 0;
}
