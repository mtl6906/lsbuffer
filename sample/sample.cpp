#include "ls/Buffer.h"
#include "string"
#include "iostream"

using ls::Buffer;
using namespace std;

int main()
{	
	Buffer buffer;
//	push前, buffersize=0, offset=0
	buffer.push("123");
//	push后, buffersize=3, offset=0
	string text(3, '\0');
//	pop后, buffersize=3, offset=3
	buffer.pop(text);
	cout << text << endl;
//	Buffer数据为空后, 调用clear将offset和buffersize置0
	buffer.clear();
	return 0;
}
