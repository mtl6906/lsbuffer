#include "ls/Buffer.h"
#include "string"
#include "cstring"

namespace ls {


Buffer::Buffer(std::string &data) : data(std::move(data)), buffer((char *)this -> data.c_str()), offset(0), buffersize(this -> data.size()), maxBufferSize(this -> data.size())
{

}

Buffer::Buffer(int maxBufferSize) : data(std::string(maxBufferSize, '\0')), buffer((char *)data.c_str()), offset(0), buffersize(0), maxBufferSize(maxBufferSize)
{

}

std::string &Buffer::getData()
{
	return data;
}

int Buffer::size()
{
	return buffersize - offset;
}

int Buffer::restSize()
{
	return maxBufferSize - buffersize;
}

char *Buffer::begin()
{
	return buffer + offset;
}

char *Buffer::end()
{
	return buffer + buffersize;
}

int Buffer::push(const char *data, int len)
{
	if(len > restSize())
		len = restSize();
	strncpy(end(), data, len);
	buffersize += len;
	return len;
}

int Buffer::push(Buffer &o, int len) {
	if(len > o.size())
		len = o.size();
	push(o.begin(), len);
	o.offset += len;
	return len;
}

int Buffer::push(const std::string &data)
{
	return push(data.c_str(), data.size());
}
int Buffer::pop(char *data, int len) {
	if(len > size())
		len = size();
	strncpy(data, begin(), len);
	offset += len;
	return len;
}
int Buffer::pop(std::string &data)
{	
	if(data.size() > size())
		data.resize(size());
	strncpy((char *)data.c_str(), begin(), data.size());
	offset += data.size();
	return data.size();
}
int Buffer::pop(Buffer &o, int len)
{
	if(len > o.restSize())
		len = o.restSize();
	len = pop(o.end(), len);
	o.buffersize += len;
	return len;
}
int Buffer::empty()
{
	return buffersize == offset;
}
int Buffer::findFirstOf(const char *mark, int size)
{
	char *ptr = begin();
	char *pmark = (char *)mark;
	while(ptr != end()) {
		for(int i=0;i<size;++i)
			if(*ptr == *(pmark + i))
				return ptr - begin();
		++ptr;
	}
	return -1;
}
int Buffer::find(const char *mark, int size)
{
	char *ptr = begin();
	while(ptr != end())
	{
		if(strncmp(mark, ptr, size) == 0)
			return ptr - begin();
		++ptr;
	}
	return -1;
}
int Buffer::move()
{
	char *ptr1 = buffer, *ptr2 = begin();
	while(ptr2 != end())
		*ptr1++ = *ptr2++;
	return 0;
}
int Buffer::moveBuffersize(int n)
{
	if(buffersize + n >= maxBufferSize)
		buffersize = maxBufferSize;
	else if(buffersize + n < offset)
		buffersize = offset;
	else
		buffersize += n;
	return 0;
}
int Buffer::moveOffset(int n)
{
	if(offset + n < 0)
		offset = 0;
	if(offset + n > buffersize)
		offset = buffersize;
	else
		offset += n;
	return 0;
}
int Buffer::clearWhiteSpace(int len)
{
	if(len > size())
		len = size();
	int whitespace = 0;
	char *st = begin(), *ed = begin() + len;
	bool in_string = false;
	while(st != ed) {
		*st = *(st + whitespace);
		if(*st == '\"') {
		       	in_string == !in_string;
		}
		else if(!in_string && (*st == ' ' || *st == '\n' || *st == '\r' || *st == '\t') ) {
			++whitespace;
			continue;
		}
		++st;
	}
	return whitespace;
}
void Buffer::clear()
{
	offset = buffersize = 0;	
}

}
