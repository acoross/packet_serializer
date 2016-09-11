//
//  packet_serializer_3.hpp
//  PacketSerializer
//
//  Created by 신일환 on 2016. 9. 11..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef packet_serializer_3_hpp
#define packet_serializer_3_hpp

namespace packet_serializer_2 {

template <typename... Types>
class Struct2;

template <>
class Struct2<> {
public:
	unsigned char* Serialize(unsigned char* buffer)
	{
		return buffer;
	}
};

template <typename T, typename... Types>
class Struct2<T, Types...> : private Struct2<Types...> {
public:
	using _MyT = Struct2<T, Types...>;
	using _MyBase = Struct2<Types...>;

	unsigned char* Serialize(unsigned char* buffer)
	{
		buffer = val_.Serialize();
		return _MyBase::Serialize(buffer);
	}

	constexpr _MyBase& GetRest()
	{
		return (_MyBase&)(*this);
	}

	T val_;
private:
	
};

template <size_t I, typename T>
struct StructElement;

template <size_t I, typename T, typename... Types>
struct StructElement < I, Struct2<T, Types...>>
{
	using type = typename StructElement < I - 1, Struct2<Types...>>::type;
};

template <typename T, typename... Types>
struct StructElement < 0, Struct2<T, Types...>>
{
	using type = T;
};

template <size_t I, typename T>
StructElement <I, Struct2<T>> get(Struct2<T> struct2);

template <size_t I, typename... Types>
typename StructElement <I, Struct2<Types...>>::type& get(Struct2<Types...>& struct2)
{
	return get<I - 1, Struct2<Types...>::_MyBase>(struct2.GetRest());
}

template <typename... Types>
typename StructElement <0, Struct2<Types...>>::type& get(Struct2<Types...>& struct2)
{
	return struct2.val_;
}

}
#endif /* packet_serializer_3_hpp */

