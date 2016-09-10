//
//  packet_defines.hpp
//  PacketSerializer
//
//  Created by 신일환 on 2016. 9. 10..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef packet_defines_hpp
#define packet_defines_hpp

//// enum 으로 packet number 구분하기
enum MyEnum {
	First,
	Second
};

template <MyEnum e>
class TTTT {
	const MyEnum val = e;
};

#endif /* packet_defines_hpp */
