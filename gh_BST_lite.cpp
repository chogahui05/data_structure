#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Simple bst.
class gh_BST
{
    typedef struct node
    {
        int num; //real_data
        int is_removed;
        struct node *left,*right;
    }node;
private:
    node *root;
    node *new_root;
    int remove_count;
    //if remove_node is exceed remove node bound
    //reconstruct Tree
    int remove_node_bound; 
public:
    gh_BST()
    {
    	remove_node_bound = 100;
        gh_init();
    }
public:
    void add(int x)
    {
    	add(&root,x);
    }
    int find_num(int x)
    {
        node *tt = _find(root,x);
	if(tt==NULL)
	    return 0;
	return (tt->is_removed == 0);
    }
    void remove(int x)
    {
        if(find_num(x)==0) //if x is not find. ignore remove Query
            return;
        node *tt = _find(root,x); //have x is exist and tt->is_removed == 0
        tt->is_removed = 1; remove_count++;
        if(remove_count>=remove_node_bound)
        {
	    //rebuild_tree
	    rebuild();
	    remove_count = 0;
        }
    }
private:
    gh_init()
    {
        root = NULL;
    	remove_count = 0;
    }
    void rebuild()
    {
        new_root = NULL;
		
	//traverse.
	do_dfs(root,&new_root);
	remove_all(root);
	root = new_root;
    }
    void remove_all(node *cur)
    {
        if(cur==NULL)
            return;
        remove_all(cur->left);
        remove_all(cur->right);
        delete cur;
    }
    void do_dfs(node *cur,node **NEW_ROOT)
    {
        if(cur==NULL)
	    return;
        if(cur->is_removed==0)
	    add(NEW_ROOT,cur->num);
        do_dfs(cur->left,NEW_ROOT);
        do_dfs(cur->right,NEW_ROOT);
    }
    void add(node **root,int x)
    {
        node *cur,*tt;
        if(*root==NULL)
        {
            *root = make_node(x);
            return;
        }
	tt = _find(*root,x); //find node that have value x
	if(tt!=NULL)
	{
	    tt->is_removed = 0; remove_count--; return;
        }
        cur = *root;
        //find that where value x insert.
	while(1)
	{
	    int key = cur->num;
	    if(x<key)
	        tt = cur->left;
	    else
	        tt = cur->right;
	    if(tt==NULL)
		break;
	    cur = tt;
        }
		
        //ok. connect_node.
        _connect(cur,x);
    }
    void _connect(node *tar,int x)
    {
        if(x<(tar->num))
	    tar->left = make_node(x);
        else
            tar->right = make_node(x);
    }
    node *_find(node *root,int x)
    {
        node *cur = root;
    	while(cur!=NULL)
        {
    	    int key = cur->num;
    	    if(x<key)
    		cur = cur->left;
            else if(x>key)
    		cur = cur->right;
    	    else
    	        return cur;
	}
        return cur;
    }
    node *make_node(int x)
    {
        node *_new = new node;
        _new->num = x;
        _new->is_removed = 0;
        _new->left = _new->right = NULL;
        return _new;
    }
};
int main(void)
{
    gh_BST bst = gh_BST();
	  bst.add(3); bst.add(7); bst.add(5); bst.remove(3);
    for(int i=0;i<500;i++) 
		    bst.add(i);
	  for(int i=0;i<500;i++)
		    bst.remove(4*i);
	  for(int i=0;i<101;i++)
	      printf("%d : %d\n",i,bst.find_num(i));
	  return 0;
}
