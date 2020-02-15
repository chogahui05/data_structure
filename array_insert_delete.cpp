#include <stdio.h>
class my_array
{
private:
    int size;
    int capacity;
    int *arr;
public:
    my_array()
    {
        init();
    }
    void init()
    {
        arr = new int[16];
        size = 0; capacity = 16;
    }
    void add(int lo,int num)
    {
        if(size < lo)
            return;
        if(size == capacity)
            grow();
        for(int i=size-1;i>=lo;i--)
            arr[i+1] = arr[i];
        arr[lo] = num;
        size++;
    }
    void del(int lo)
    {
        del(lo,lo);
    }
    void del(int s,int e)
    {
        int pos = s;
        if(s<0||e>=size)
            return;
        for(int i=e+1;i<size;i++)
            arr[pos++] = arr[i];
        size = pos;
    }
    void print()
    {
        printf("[");
        for(int i=0;i<size;i++)
            printf("%d ",arr[i]);
        printf("]\n");
    }
private:
    void grow()
    {
        int *temp = new int[2*capacity];
        for(int i=0;i<size;i++)
            temp[i] = arr[i];
        delete arr;
        arr = temp;
        capacity = 2*capacity;
    }
};
my_array v;
int main(void)
{
    v.add(0,1);
    v.add(0,2);
    v.add(0,3);
    v.add(0,4);
    v.add(0,5);
    v.print();
    
    v.del(4,4);
    v.print();
    
    v.add(2,6);
    v.print();
    
    v.del(1,2);
    v.print();
    v.del(1,2);
    v.print();
    v.del(0,0);
    v.print();
}
