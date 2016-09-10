//
//  main.cpp
//  PacketSerializer
//
//  Created by 신일환 on 2016. 9. 10..
//  Copyright © 2016년 acoross. All rights reserved.
//

#include <iostream>

#include "packet_serializer_1.hpp"
#include "packet_serializer_1_types.hpp"

using namespace packet_serializer_1;


class MyPacket : public Packet {
public:
	MyPacket()
	: i_val_(this)
	, c_val_(this), ba_val_(this), str_val_(this)
	{
		
	}

	IntType i_val_;
	CharType c_val_;
	StringType str_val_;
	ByteArrayType<10> ba_val_;
};


int main(int argc, const char * argv[]) {
	MyPacket packet;
	packet.i_val_.data_ = 0xcdcdffab;
	packet.c_val_.data_ = 'c';
	packet.str_val_.data_ = std::string("bakashinji");

	unsigned char buffer[100]{0,};
	packet.Serialize(buffer);

	return 0;
}
