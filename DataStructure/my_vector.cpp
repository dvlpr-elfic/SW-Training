
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <memory.h>

#define MAX 10001

using namespace std;

typedef int vnode;

typedef struct _vector
{
	vnode data[MAX];
	int index, size;
	_vector(void)			// »ý¼ºÀÚ
	{
		index = -1, size = 0, memset(data, 0, sizeof(data));
	}
	void pop_back(void)
	{
		if(index > -1){
			vnode clear = {0, };
			data[index--] = clear;
			size--;
		}
	}
	vnode back(void)
	{
		if(index > -1){
			return data[index];
		}
	}
	void push_back(vnode item)
	{
		data[++index] = item;
		size++;
	}	
}_vector;

int main(void)
{
	_vector v;
	v.push_back(1);
	v.push_back(2);
	v.pop_back();
	cout << v.back() << endl;
	v.pop_back();
	return 0;
}
