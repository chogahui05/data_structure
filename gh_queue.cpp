#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
template <typename T>
class gh_queue
{
private:
    int s,e;
    int capacity,size;
    T *queue;
public:
    gh_queue()
    {
        queue_init();
	}
	void clear()
	{
		delete(queue);
		queue_init();
	}
	void push(T item)
	{
		if(is_full())
			expand_queue();
		queue[e] = item; e = (e+1)%capacity; size++;
	}
	T front()
	{
		T item;
		if(!empty())
		{
			item = queue[s];
			return item;
		}
	}
	void pop()
	{
		if(!empty())
		{
			//queue[s] = 0;
			s = (s+1)%capacity;
			size--;
		}
	}
	bool empty()
	{
		return (size==0);
	}
	bool is_full()
	{
		return (size==capacity);
	}
private:
	void queue_init()
	{
		queue = new T[16];
		capacity = 16; size = 0;
		s = e = 0;
	}
	void expand_queue()
	{
		T *__new = new T[2*capacity];
		for(int i=0;i<size;i++)
			__new[i] = queue[(i+s)%capacity];
		s = 0;
		e = size;
		capacity = capacity*2;
		delete(queue);
		queue = __new;
	}
};
int main(void)
{
    return 0;
}
