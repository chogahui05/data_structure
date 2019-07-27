#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
struct node
{
    char str[20];
    struct node *prev,*next;
};
typedef struct node node;
node * make();
node *head,*tail;
void init();
void add(char *str);
void del(char *str);
void search();
int main(void)
{
    init();
    add("at");
    add("b");
    add("e");
    add("d");
    add("com");
    add("a");
    search();
    del("a");
    search();
    del("e");
    search();
    del("b");
    search();
}
void search()
{
    node *cur_n = head->next;
    for(;cur_n!=tail;cur_n=cur_n->next)
    {
        printf("[%s] ",cur_n->str);
    }
    printf("\n");
}
void del(char *str)
{
    node *cur = head;
    node *cur_n = head->next;
    for(;cur_n!=tail;cur=cur->next,cur_n=cur_n->next)
    {
        if(strcmp(cur_n->str,str) == 0)
        {
            node *new_cur_next = cur_n -> next;
            new_cur_next -> prev = cur;
            cur->next = new_cur_next;
            
            cur_n->next = cur_n->prev = NULL;
            free(cur_n);
            return;
        }
    }
}
void add(char *str)
{
    node *cur = head;
    node *cur_n = head->next;
    node *_new = make(); strcpy(_new->str,str);
    for(;cur_n!=tail;cur=cur->next,cur_n=cur_n->next)
    {
        if(strcmp(cur_n->str,str) == 0)
            return;
        if(strcmp(cur_n->str,str)>0)
            break;
    }
    _new->next = cur_n; _new->prev = cur;
    cur->next = _new; cur_n->prev = _new;
}
void init()
{
    head = make(); tail = make();
    head->next = tail;
    tail->prev = head;
}
node * make()
{
    node *_new = (node *)malloc(sizeof(node));
    memset(_new,0,sizeof(node));
    return _new;
}
