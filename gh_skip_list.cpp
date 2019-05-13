#include <stdio.h>
#include <stdlib.h>
class gh_skiplist
{
    struct node
    {
        int value;
        int sz;
        struct node **go;
        int *jump;
    };
    typedef struct node node;
private:
    int add_num;
    node *root;
public:
    gh_skiplist()
    {
    	root = (node *)malloc(sizeof(node));
    	init_node(root,0,20);
        init();
    }
    void insert(int x)
    {
    	int __bit = bit_count(add_num);
    	node *__new = (node *)malloc(sizeof(node));
    	node *prev[20];
    	node *cur[20];
    	int temp_jump[20]={0};
    	int tj = 1;
    	init_node(__new,x,__bit);
    	prev[19] = root;
	for(int i=19;i>=0;i--)
    	{
    	    //node position init.
            if(i!=19)
    	        prev[i] = prev[i+1];
    	    while((prev[i]->go[i]!=NULL)&&(prev[i]->go[i]->value<x))
    	    {
                temp_jump[i] = temp_jump[i] + (prev[i]->jump[i]);
    		prev[i] = (prev[i]->go[i]);
    	    }
	}
        for(int i=19;i>=__bit;i--)
            (prev[i]->jump[i]) = (prev[i]->jump[i])+1;
		
        for(int i=0;i<__bit;i++)
        {
            int total_jump = (prev[i]->jump[i])+1;
            prev[i]->jump[i] = tj;
            __new->jump[i] = total_jump-tj;
            tj = tj + temp_jump[i];
        }
    	for(int i=0;i<__bit;i++)
    	{
            //link two
            __new->go[i] = prev[i]->go[i];
            prev[i]->go[i] = __new;
        }
        //how to select add_num?
        add_num = next(); add_num = (add_num&1048575);
    }
    void remove(int x)
    {
        node *prev[20];
    	node *cur[20];
    	node *current_node;
    	int sz;
    	prev[19] = root;
        for(int i=19;i>=0;i--)
    	{
            //node position init.
            if(i!=19)
                prev[i] = prev[i+1];
            while((prev[i]->go[i]!=NULL)&&(prev[i]->go[i]->value<x))
                prev[i] = (prev[i]->go[i]);
        }
        current_node = prev[0]->go[0];
        sz = (current_node->sz);
        if(current_node==NULL||current_node->value!=x) //not find x
            return;
        for(int i=0;i<sz;i++)
        {
            int aa = prev[i]->jump[i];
            int bb = current_node->jump[i]; //current_node == prev[0]->go[0]
            //jumping distance update
            prev[i]->jump[i] = aa+bb-1;
            prev[i]->go[i] = current_node->go[i];
        }
        free(current_node);
        for(int i=sz;i<20;i++)
            prev[i]->jump[i] = (prev[i]->jump[i])-1;
    }
	int kth(int x)
	{
		int ret = 0;
		node *cur = root;
		for(int i=19;i>=0;i--)
		{
			while((cur!=NULL)&&(ret+(cur->jump[i])<=x))
			{
			    ret = ret + (cur->jump[i]);
				cur = cur->go[i];    
			}
		}
		if(cur==NULL)
		    return -1;
		return cur->value;
	}
	void print()
	{
		for(int i=19;i>=0;i--)
		{
			node *cur = root;
			while(1)
			{
				cur = cur->go[i];
				if(cur==NULL) break;
				printf("%d ",cur->value);
			}
			printf("\n");
		}
	}
private:
    void init()
    {
        add_num = 0;
    }
    void init_node(node *tar,int value,int sz)
    {
    	tar->value = value; tar->sz = sz;
    	tar->go = (node **)malloc(sizeof(node *)*sz);
    	tar->jump = (int *)malloc(sizeof(int)*sz);
    	for(int i=0;i<sz;i++)
    	{
    		tar->go[i] = NULL;
    		tar->jump[i] = 1;
		}
	}
	int bit_count(int x)
	{
		int t = x+1;
		for(int i=19;i>=0;i--)
		{
			int mask = (1<<i)-1;
			if((t&mask)==0)
			    return (i+1);
		}
	}
	int next()
	{
		long long tari = add_num * 214013L + 2531011L;
		return ((tari >> 16) & 0x7fff);
	}
};
int main(void)
{
	
}
