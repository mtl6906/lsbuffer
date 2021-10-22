#ifndef LS_BUFFER_H
#define LS_BUFFER_H

#include "string"

namespace ls
{
	class Buffer
	{
		std::string data;
		char *buffer;
		int offset;
		int buffersize;
		int maxBufferSize;
		public:
			Buffer(int maxBufferSize = 1 << 20);
			Buffer(std::string &data);
			int push(const char *data, int len);
			int push(Buffer &o, int len);
			int push(const std::string &data);
			int pop(char *data, int len);
			int pop(Buffer &o, int len);
			int pop(std::string &data);
			char *begin();
			char *end();
			int size();
			int restSize();
			int empty();
			int find(const char *mark, int size);
			int findFirstOf(const char *mark, int size);
			int move();
			int moveBuffersize(int n);
			int moveOffset(int n);
			int clearWhiteSpace(int len);
			void clear();
			std::string &getData();
	};
}

#endif
