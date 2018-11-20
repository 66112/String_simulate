#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

class String
{
public:
	typedef char* Iterator;
	static const size_t npos = -1;
	String(const char* arg = "")
	{
		if (arg == nullptr)
		{
			arg = "";
		}
		_size = strlen(arg);
		_ptr = new char[_size + 1];
		strcpy(_ptr, arg);
		_capacity = _size;
	}
	String(const String& s)     //拷贝构造
		:_ptr(nullptr)
	{
		String tmp(s._ptr);
		this->Swap(tmp);
	}
	~String()
	{
		delete[] _ptr;
		_ptr = nullptr;
		_size = _capacity = 0;
	}
	void Reserve(size_t newcapacity)          //扩容
	{
		if (newcapacity > _capacity)
		{
			char* newptr = new char[newcapacity + 1];
			strcpy(newptr, _ptr);
			delete[] _ptr;
			_ptr = newptr;
			_capacity = newcapacity;
		}
	}
	void Resize(size_t newsize, char c = char())
	{
		if (newsize<_size)
		{
			_ptr[newsize] = '\0';
			_size = newsize;
			return;
		}
		else if (newsize > _capacity)
		{
			Reserve(newsize);
		}
		memset(_ptr + _size, c, newsize - _size);
		_size = newsize;
		_ptr[_size] = '\0';
	}
	void PushBack(char c)
	{
		if (_size == _capacity)
		{
			Reserve(_capacity * 2);
		}
		_ptr[_size++] = c;
		_ptr[_size] = '\0';
	}
	String& operator=(String s);
	String& operator+=(const char c);
	String& operator+=(const char* str);
	String& operator+=(const String& s);
	String operator+(const String& s) const;
	String operator+(const char* str) const;
	String operator+(const char c) const;
	void Addend(size_t n, char c);
	void String::Addend(const char* str);

	char& operator[](size_t pos)
	{
		assert(pos < _size);
		return _ptr[pos];
	}
	char& operator[](size_t pos) const
	{
		assert(pos < _size);
		return _ptr[pos];
	}
	// Iterator
	Iterator Begin()
	{
		return _ptr;
	}
	Iterator End()
	{
		return _ptr + _size;
	}
	Iterator cBegin() const
	{
		return _ptr;
	}
	Iterator cEnd() const
	{
		return _ptr + _size;
	}
	void Clear()
	{
		_size = 0;
		_ptr[_size] = 0;
	}
	const char* C_str()
	{
		return _ptr;
	}
	size_t Size()const
	{
		return _size;
	}
	size_t Capacity()const
	{
		return _capacity;
	}
	bool Empty()const
	{
		return 0 == _size;
	}
	friend ostream& operator<<(ostream& out, const String& s);
	friend istream& operator>>(istream& in, String& s);
	bool operator<(const String& s);
	bool operator<=(const String& s);
	bool operator>(const String& s);
	bool operator>=(const String& s);
	bool operator==(const String& s);
	bool operator!=(const String& s);

	size_t Find(char c, size_t pos = 0) const;   //返回第一次出现的位置
	size_t String::RFind(char c, const size_t pos = npos) const;   //返回第一次出现的位置
	size_t Find(const char* str, size_t pos = 0) const; //返回子串出现的位置
	String SubStr(size_t pos, size_t n);   //截取从pos位置开始的n个字符
	String& Insert(size_t pos, char c);    //在pos位置上插入字符c
	String& Insert(size_t pos, const char* str);  //在pos位置插入字符串
	String& Erase(size_t pos, size_t len);  //删除pos位置往后的len个字符
	void Swap(String& s);
private:
	char* _ptr;
	size_t _size;
	size_t _capacity;
};