//
//  packet_serializer_1_types.hpp
//  PacketSerializer
//
//  Created by 신일환 on 2016. 9. 10..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef packet_serializer_1_types_hpp
#define packet_serializer_1_types_hpp

#include <stdio.h>

#include "packet_serializer_1.hpp"

namespace packet_serializer_1{

	class IntType : public Packet::Serializable {
	public:
		int data_{0};

		IntType(Packet* owner)
		: Packet::Serializable(owner) {

		}

		virtual unsigned char* Serialize(unsigned char* buffer) override {
			memcpy(buffer, (void*)&data_, sizeof(data_));
			return buffer + sizeof(data_);
		}
	};

	class CharType : public Packet::Serializable {
	public:
		char data_{0};

		CharType(Packet* owner)
		: Packet::Serializable(owner) {

		}

		virtual unsigned char* Serialize(unsigned char* buffer) override {
			memcpy(buffer, (void*)&data_, sizeof(data_));
			return buffer + sizeof(data_);
		}
	};

	template <size_t Size>
	class ByteArrayType : public Packet::Serializable {
	public:
		char data_[Size]{0,};

		ByteArrayType(Packet* owner)
		: Packet::Serializable(owner) {

		}

		virtual unsigned char* Serialize(unsigned char* buffer) override {
			memcpy(buffer, data_, sizeof(data_));
			return buffer + sizeof(data_);
		}
	};

	class StringType : public Packet::Serializable {
	public:
		std::string data_;

		StringType(Packet* owner)
		: Packet::Serializable(owner) {

		}

		virtual unsigned char* Serialize(unsigned char* buffer) override {
			memcpy(buffer, data_.c_str(), data_.length());
			return buffer + data_.length();
		}
	};

	template <typename T>
	class ListType : public Packet::Serializable {
		std::list<T> values_;

		ListType(Packet* owner)
		: Packet::Serializable(owner) {

		}

		virtual unsigned char* Serialize(unsigned char* buffer) override {
			for (auto& v : values_) {
				buffer = v.Serialize(buffer);
			}
			return buffer;
		}
	};
}

#endif /* packet_serializer_1_types_hpp */
