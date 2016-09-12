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

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>

namespace test_cereal {

void testCereal() {
	
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

}
#endif /* cereal_test_hpp */
