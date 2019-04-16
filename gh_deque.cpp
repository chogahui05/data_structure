#include <stdio.h>
template <typename T>
class gh_deque
{
private:
	int s,e;
	int capacity;
	T *deque;
public:
	gh_deque()
	{
		deque_init();
	}
	deque_init()
	{
		deque = new T[16];
		capacity = 16;
		s = 7; e = 8;
	}
	T& operator[] (int x) 
	{
		return deque[s+1+x];
	}
	bool empty()
	{
    		return (s+1==e);
	}
	T front()
	{
		return deque[s+1];
	}
	T back()
	{
		return deque[e-1];
	}
	void clear()
	{
		delete(deque); deque_init();
	}
	void push_front(T item)
	{
		if(s<0)
			deque_extend();
		deque[s--] = item;
	}
	void push_back(T item)
	{
		if(e==capacity)
			deque_extend();
		deque[e++] = item;
	}
	int size()
	{
		return e-s-1;
	}
	void pop_front()
	{
		if(s+1<e)
		{
			deque[s] = 0;
			s++;
		}
	}
	void pop_back()
	{
		if(s+1<e)
		{
			deque[e] = 0;
			e--;
		}
	}
	
private:
	deque_extend()
	{
		T *_new = new T[2*capacity];
		int new_capacity = 2*capacity;
		int new_mid = new_capacity/2;
		int mid = (s+e)/2;
		for(int i=s+1;i<e;i++)
			_new[new_mid-mid+i] = deque[i];
		s = new_mid-mid+s;
		e = new_mid-mid+e;
		capacity = new_capacity;
		delete(deque);
		deque = _new;
	}
};
gh_deque <int> dq;
void print_dq();
int main(void)
{
	return 0;	
}