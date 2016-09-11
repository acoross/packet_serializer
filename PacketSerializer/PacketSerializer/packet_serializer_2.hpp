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

	class ISerializable {
	public:
		virtual unsigned char* Serialize(unsigned char* buffer) = 0;
	};

	///////////////////////////////////////////////////////////////////////////
	template <typename NumericT>
	class NumericType : public ISerializable {
	public:
		NumericType() : data_(0) {}
		NumericType(NumericT v) : data_(v) {}
		
		virtual	unsigned char* Serialize(unsigned char* buffer) override {
			memcpy(buffer, (void*)&data_, sizeof(data_));
			return buffer + sizeof(data_);
		}
		
		NumericT data_{ 0 };
	};

	using IntType = NumericType<int>;
	using CharType = NumericType<char>;
	using ShortType = NumericType<short>;

	class StringType : public ISerializable {
	public:
		virtual unsigned char* Serialize(unsigned char* buffer) override {
			memcpy(buffer, data_.c_str(), data_.length());
			return buffer + data_.length();
		}

		std::string data_;
	};

	template <typename SerializableT>
	class ListType : public ISerializable {
	public:
		virtual unsigned char* Serialize(unsigned char* buffer) override {
			for (auto& val : data_list_) {
				buffer = val.Serialize(buffer);
			}
			return buffer;
		}

		std::list<SerializableT> data_list_;
	};
	
	///////////////////////////////////////////////////////////////////
	class Struct : public ISerializable {
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
					return Serialize(buffer);
				});
			}

		};
		virtual unsigned char*  Serialize(unsigned char* buffer) override {
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
