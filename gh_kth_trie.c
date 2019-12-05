#include <stdio.h>
#define Q 100000
struct trie_node
{
    int go[2];
    int v;
};
typedef struct trie_node trie_node;
trie_node trie[32*Q];
int upd(int v,int dx,int node_num);
int foo(int node_num);
int kth(int x);
int main(void)
{
	int q,op,a,b,cur_node = 0; scanf("%d",&q);
	for(int i=0;i<q;i++)
	{
		scanf("%d",&op);
		if(op == 1)
		{
			scanf("%d",&a);
            int res = kth(a);
			printf("%d\n",res);
            cur_node = upd(res,-1,cur_node);
		}
		else
		{
			scanf("%d%d",&a,&b);
			cur_node = upd(a,b,cur_node);
		}
	}
}
int kth(int x)
{
	int cur_th = 0;
	int cur = 0;
	int res = 0;
	for(int i=31;i>=0;i--)
	{
        int rr = cur_th + foo(cur);
		if(x<=rr)
		    cur = trie[cur].go[0];
		else
		{
		    cur = trie[cur].go[1];
            cur_th = rr;
		    res = res + (1LL<<i);
		}
	}
	return res;
}
int foo(int node_num)
{
	if(trie[node_num].go[0]!=0)
	{
		int next = trie[node_num].go[0];
		return trie[next].v;
	}
	return 0;
}
int upd(int v,int dx,int node_num)
{
	int cur_num = node_num;
	int cur = 0;
	int poi;
	for(int i=31;i>=0;i--)
	{
		trie[cur].v = trie[cur].v + dx;
		poi = ((v&(1<<i))!=0);
		if(trie[cur].go[poi] == 0)
			trie[cur].go[poi] = (++cur_num);
		cur = trie[cur].go[poi];
	}
	trie[cur].v = trie[cur].v + dx;
	return cur_num;
}
