#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#include<unistd.h>


typedef struct ListNode{
int _data;
struct  ListNode *_next;
}ListNode_t,*ListNode_p,**ListNode_pp;

pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond=PTHREAD_COND_INITIALIZER;

ListNode_p alloc_node(int data)
{
   ListNode_p _n=(ListNode_p)malloc(sizeof(ListNode_t));
   if(_n==NULL)
   {
      perror("malloc");
      return NULL;
   }
   _n->_data = data;
   return _n;
}

void del_node(ListNode_p node)
{
   assert(node);
   free(node);
   node=NULL;
}
int isEmpty(ListNode_p node)
{
   assert(node);
   if(node->_next!=NULL)
   {
     return 0;
   }
   return 1;
}

void InitList(ListNode_pp head)
{
   *head=alloc_node(0);  
}

void PushFront(ListNode_p head,int data)
{
   assert(head);
   ListNode_p newnode=alloc_node(data);
   newnode->_next=head->_next;
   head->_next=newnode;  
}
void PopFront(ListNode_p head,int *data)
{
   assert(head);
   assert(data);
   while(isEmpty(head)) 
   {
     printf("list is empty!\n");
     return;
   }
   ListNode_p del=head->_next;
   head->_next=del->_next;
   *data=del->_data;
   del_node(del);
}
void Destory(ListNode_p head)
{
   int data=0;
   assert(head);
   while(!isEmpty(head))
   {
      PopFront(head,&data);
   }   
   del_node(head);
}

void Display(ListNode_p node)
{
   assert(node);
   ListNode_p cur=node->_next;
   while(cur)
   {
     printf("%d",cur->_data);
     cur=cur->_next;
   }
   printf("\n");  
}

void *thread_product(void* arg)
{ 
   ListNode_p head=(ListNode_p)arg;
   while(1) 
   {
     sleep(1);
     int data=rand()%10000;
     pthread_mutex_lock(&mylock);
     PushFront(head,data);
     pthread_mutex_unlock(&mylock);
     pthread_cond_signal(&mycond);
     printf("product done,data is:%d\n",data);
   } 
   
}
void *thread_consumer(void* arg)
{
   ListNode_p head=(ListNode_p)arg;
   int data=0;
   while(1)
   {
      pthread_mutex_lock(&mylock);
      while(isEmpty(head))
      {
        pthread_cond_wait(&mycond,&mylock);
      }
      PopFront(head,&data);
      pthread_mutex_unlock(&mylock);
      printf("consumer done,data is:%d\n",data);
   }    
}
int main()
{
   ListNode_p head=NULL;       
   InitList(&head);
//int i = 0;
//for(;i < 10;i++)
//PushFront(head,i);
//Display(head);
//
//for(i = 0;i < 10;i++)
//
//int data = 999;
//PopFront(head, &data);
//Display(head);
//}*/

   pthread_t tid1,tid2;
   pthread_create(&tid1,NULL,thread_product,(void*)head);
   pthread_create(&tid2,NULL,thread_consumer,(void*)head);

   
   pthread_join(tid1,NULL);
   pthread_join(tid2,NULL);
   // int data=0;
   //PushFront(head,1);
   // PushFront(head,0);
   //PushFront(head,9);
   //  PopFront(head,&data);
    // Display(head);
   Destory(head);
   pthread_mutex_destroy(&mylock);
   pthread_cond_destroy(&mycond);
   return 0;
}
