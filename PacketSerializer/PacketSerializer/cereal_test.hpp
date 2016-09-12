//
//  cereal_test.hpp
//  PacketSerializer
//
//  Created by 신일환 on 2016. 9. 13..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef cereal_test_hpp
#define cereal_test_hpp

#include <sstream>
#include <strstream>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <utility>
#include <iostream>

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/unordered_map.hpp>

namespace test_cereal {

	inline void testCereal() {

		char buf[100] {0,};
		std::strstream strs(buf, 100);	// deprecated... but I can use in VS2015 and XCode

		{ // cannot use. maybe VS2015 mistakes.
			//std::stringstream ss;
			//std::stringbuf& sb = *(ss.rdbuf());
			//ss.set_rdbuf(&sb);	//basic_ios:: _Mysb *_Mystrbuf;
			//sb.rdbuf();
		}

		{
			cereal::BinaryOutputArchive ar(strs);
			ar('s', 'e', 'x');	//itsStream.rdbuf()->sputn(...)
		}

		//	std::cout << "sb: " << sb.str() << std::endl;
		//	std::cout << "ss: " << ss.str() << std::endl;
		// ss.str() : _Mysb _Stringbuffer;	// the string buffer
		std::cout << "strs: " << (strs.str() ? strs.str() : "") << std::endl;
	}

	struct Datagram1 {
		template<typename Archive>
		void serialize(Archive& ar) {
			//ar(a, age, name, list, map, uomap);
			ar(map);
		}

		int a{0};
		short age{30};
		std::string name{""};
		std::list<char> list;
		std::map<char, int> map;
		std::unordered_map<char, int> uomap;
	};

	inline void test_2() {
		char buf[100] {0,};

		{
			std::strstream strs(buf, 100);

			Datagram1 dg;
			dg.a = 12;
			dg.age = 31;
			dg.name = "shin";
			dg.list.push_back('i');
			dg.list.push_back('j');
			dg.list.push_back('k');
			dg.list.push_back('l');
			dg.list.push_back('m');
			dg.list.push_back('n');

			dg.map['a'] = 0;
			dg.map['b'] = 1;
			dg.map['c'] = 2;
			dg.map['d'] = 3;

			dg.uomap['w'] = 3;
			dg.uomap['x'] = 2;
			dg.uomap['y'] = 1;
			dg.uomap['z'] = 0;
			
			cereal::BinaryOutputArchive ar(strs);
			ar(dg);
		}

		{
			std::istrstream strs(buf, 100);

			Datagram1 dg;
			cereal::BinaryInputArchive ar(strs);
			ar(dg);

			std::cout << dg.name.c_str();

			std::cout << "map\n";
			for (auto& v : dg.map) {
				std::cout << v.first << ", " << v.second << std::endl;
			}
			std::cout << "map\n";

			std::cout << "uomap\n";
			for (auto& v : dg.uomap) {
				std::cout << v.first << ", " << v.second << std::endl;
			}
			std::cout << "uomap\n";
		}
	}

}
#endif /* cereal_test_hpp */
