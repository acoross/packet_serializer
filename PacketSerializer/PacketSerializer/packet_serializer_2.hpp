//
//  packet_serializer_2.hpp
//  PacketSerializer
//
//  Created by 신일환 on 2016. 9. 11..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef packet_serializer_2_hpp
#define packet_serializer_2_hpp

#include <list>
#include <string>
#include <functional>

namespace packet_serializer_2 {

//	class ISerializable {
//	public:
//		virtual unsigned char* Serialize(unsigned char* buffer) = 0;
//	};

	class SerializableBase {
	public:
	};

	///////////////////////////////////////////////////////////////////////////
	template <typename NumericT>
	unsigned char* Serialize(const NumericT& val, unsigned char* buffer) {
		memcpy(buffer, (void*)&val, sizeof(val));
		return buffer + sizeof(val);
	}

	template <typename NumericT>
	class NumericType {
	public:
		NumericType() : data_(0){}
		NumericType(NumericT v) : data_(v) {}
		
		unsigned char* Serialize(unsigned char* buffer) {
			return packet_serializer_2::Serialize(data_, buffer);
		}
		
		NumericT data_{ 0, };
	};

	using IntType = NumericType<int>;
	using CharType = NumericType<char>;
	using ShortType = NumericType<short>;

	template <typename RawT>
	class RawType {
	public:
		unsigned char* Serialize(unsigned char* buffer) {
			return packet_serializer_2::Serialize(data_, buffer);
		}
		
		RawT data_;
	};

	class StringType {
	public:
		unsigned char* Serialize(unsigned char* buffer) {
			memcpy(buffer, data_.c_str(), data_.length());
			return buffer + data_.length();
		}

		std::string data_;
	};

	template <typename RawT>
	class ListType {
	public:
		unsigned char* Serialize(unsigned char* buffer) {
			for (auto& val : data_list_) {
				buffer = packet_serializer_2::Serialize(val, buffer);
			}
			return buffer;
		}

		std::list<RawT> data_list_;
	};

	template <typename RawT>
	class ListType {
	public:
		unsigned char* Serialize(unsigned char* buffer) {
			for (auto& val : data_list_) {
				buffer = packet_serializer_2::Serialize(val, buffer);
			}
			return buffer;
		}

		std::list<RawT> data_list_;
	};
	
	///////////////////////////////////////////////////////////////////
	class Struct {
	public:
		//typedef IntType ISerializableT;
		template <typename SerializableT>
		class StructVal : public SerializableT {
		public:
			StructVal(Struct* owner)
			{
				owner->add(
					[&](unsigned char* buffer)->unsigned char *
				{
					return SerializableT::Serialize(buffer);
				});
			}

		};
		unsigned char*  Serialize(unsigned char* buffer) {
			for (auto& serializer : values_)
			{
				buffer = serializer(buffer);
			}
			return buffer;
		}

	private:
		using SerializeFunc = std::function<unsigned char*(unsigned char*)>;

		void add(SerializeFunc val)
		{
			values_.push_back(val);
		}

		std::list<SerializeFunc> values_;
	};
}

#endif /* packet_serializer_2_hpp */
