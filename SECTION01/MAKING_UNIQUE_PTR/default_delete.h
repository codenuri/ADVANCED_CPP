#pragma once
#include <iostream>

template<typename T> struct default_delete
{
	default_delete() = default;

	template<typename U> default_delete( const default_delete<U>&) {}

	void operator()(T* p) const
    {
        std::cout << "delete" << std::endl;
        delete p;
    }
};
// T[] 부분 특수화
template<typename T> struct default_delete<T[]>
{
	default_delete() = default;

	template<typename U> default_delete( const default_delete<U>&) {}

	void operator()(T* p) const
    {
        std::cout << "delete[]" << std::endl;
        delete[] p;
    }
};
