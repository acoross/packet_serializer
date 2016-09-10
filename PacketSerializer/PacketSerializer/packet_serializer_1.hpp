//
//  packet_serializer_1.hpp
//  PacketSerializer
//
//  Created by 신일환 on 2016. 9. 10..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef packet_serializer_1_hpp
#define packet_serializer_1_hpp

#include <list>
#include <string>

namespace packet_serializer_1 {

	class Packet {
	public:
		class Serializable {
		public:
			Serializable(Packet* owner) {
				owner->Add(this);
			}

			virtual unsigned char* Serialize(unsigned char* buffer){
				return buffer;
			}
		};

		void Serialize(unsigned char* buffer){
			for (auto& v : values_) {
				buffer = v->Serialize(buffer);
			}
		}

	private:
		void Add(Serializable* val) {
			values_.push_back(val);
		}

		std::list<Serializable*> values_;
	};
}

#endif /* packet_serializer_1_hpp */
