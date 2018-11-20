#include "String.h"

void String::Swap(String& s)
{
	std::swap(_ptr, s._ptr);
	std::swap(_size, s._size);
	std::swap(_capacity, s._capacity);
}
String& String::operator=(String s)
{
	this->Swap(s);
	return *this;
}

ostream& operator<<(ostream& out, const String& s)
{
	out << s._ptr << endl;
	out << "_size: " << s._size << endl;
	out << "_capacity: " << s._capacity << endl;
	return out;
}

istream& operator>>(istream& in, String& s)
{
	char buffer[1024] = { 0 };
	in >> buffer;
	if (in)
	{
		String tmp(buffer);
		s.Swap(tmp);
	}
	return in;
}

void String::Addend(size_t n, char c)
{
	for (size_t i = 0; i < n; i++)
	{
		PushBack(c);
	}
}
void String::Addend(const char* str)
{
	(*this) += str;
}
String& String::operator+=(const char c)
{
	PushBack(c);
	return *this;
}
String& String::operator+=(const char* str)
{
	if (nullptr == str)
	{
		return *this;
	}
	for (size_t i = 0; i < strlen(str); i++)
	{
		PushBack(str[i]);
	}
	return *this;
}
String& String::operator+=(const String& s)
{
	for (size_t i = 0; i < s._size; i++)
	{
		PushBack(s._ptr[i]);
	}
	return *this;
}

String String::operator+(const String& s) const
{
	String tmp(*this);
	tmp += s;
	return tmp;
}
String String::operator+(const char* str) const
{
	String tmp(*this);
	tmp += str;
	return tmp;
}

String String::operator+(const char c) const
{
	String tmp(*this);
	tmp += c;
	return tmp;
}

bool String::operator==(const String& s)
{
	return strcmp(this->_ptr, s._ptr) == 0 ? true : false;
}
bool String::operator<(const String& s)
{
	int i = 0;
	Iterator it = this->Begin();
	Iterator cit = s.cBegin();
	while ((it != this->End()) && (cit != s.cEnd()))
	{
		if (*it < *cit)
		{
			return true;
		}
		else if (*it == *cit)
		{
			it++;
			cit++;
		}
		else
		{
			return false;
		}
	}
	if ((it == this->End()) && (cit != s.cEnd()))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool String::operator<=(const String& s)
{
	return ((*this)<s) || ((*this) == s);
}
bool String::operator>(const String& s)
{
	return !((*this) <= s);
}
bool String::operator>=(const String& s)
{
	return ((*this)>s) || ((*this) == s);
}
bool String::operator!=(const String& s)
{
	return !(*this == s);
}

size_t String::Find(char c, size_t pos) const   //返回第一次出现的位置
{
	for (size_t i = pos; i < this->Size(); i++)
	{
		if (_ptr[i] == c)
			return i;
	}
	return npos;
}
size_t String::RFind(const char c, const size_t pos) const   //返回第一次出现的位置
{
	size_t end = _size - 1;
	if (pos != npos)
	{
		assert(pos < _size);
		end = pos;
	}
	while (end >= 0)
	{
		if (c == _ptr[end])
			return end;
		end--;
	}
	return npos;
}

size_t String::Find(const char* str, size_t pos) const //返回子串出现的位置
{
	assert(pos < _size);
	if (str == nullptr)
	{
		return npos;
	}
	else
	{
		size_t pos = 0;
		char* ret = strstr(_ptr + pos, str);
		if (ret == nullptr)
		{
			return npos;
		}
		return ret - _ptr;
	}
}
String String::SubStr(size_t pos, size_t n)   //截取从pos位置开始的n个字符
{
	assert(pos < _size);
	String ret;
	if (n >= (_size - pos))
	{
		n = _size - pos;
	}
	ret.Reserve(n);
	for (size_t i = pos; i < pos + n; i++)
	{
		ret += _ptr[i];
	}
	return ret;
}
String& String::Insert(size_t pos, char c)    //在pos位置上插入字符c
{
	assert(pos <= _size);
	if (this->Size() == this->Capacity())
	{
		Reserve(2 * _capacity);
	}
	for (size_t i = this->Size(); i > pos; i--)
	{
		_ptr[i] = _ptr[i - 1];
	}
	_ptr[pos] = c;
	_size++;
	_ptr[_size] = '\0';
	return *this;
}
String& String::Insert(size_t pos, const char* str)  //在pos位置插入字符串
{
	assert(str);
	size_t len = strlen(str);
	size_t i = 0;
	while (len--)
	{
		Insert(pos + i, str[i]);
		i++;
	}
	return *this;
}
String& String::Erase(size_t pos, size_t len)  //删除pos位置往后的len个字符
{
	assert(pos <= this->Size());
	if (len >= (this->Size() - pos))
	{
		_size = pos;
		_ptr[_size] = '\0';
	}
	else
	{
		while ((pos + len) <= Size())
		{
			_ptr[pos] = _ptr[pos + len];
			pos++;
		}
		_size -= len;
	}
	return *this;
}
