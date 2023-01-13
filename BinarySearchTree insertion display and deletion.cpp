#include<stdio.h>
#include<stdlib.h>
struct BSTnode 
{
	int data;
	struct BSTnode *left;
	struct BSTnode *right;
};
struct arrayQ
{
	int front;
	int rear;
	int capacity;
	struct BSTnode **array;
};
struct arrayQ* CreateQ()
{
	struct arrayQ *Q;
	Q=(struct arrayQ*)malloc(sizeof(struct arrayQ));
	Q->front=-1;
	Q->rear=-1;
	Q->capacity=15;
	Q->array=(struct BSTnode**)malloc(sizeof(struct BSTnode*)*Q->capacity);
	return Q;
}
int isEmpty(struct arrayQ *Q)
{
   if(Q->front==-1)
    return 1;
    else 
    return 0;
}
void enQueue(struct arrayQ *Q,struct BSTnode *root)
{
    Q->rear=(Q->rear+1)%Q->capacity;
    Q->array[Q->rear]=root;
    if(Q->front==-1)
    Q->front=Q->front+1;
}
struct BSTnode* deQ(struct arrayQ *Q)
{
	struct BSTnode *boot;
	if(!isEmpty(Q))
	{
		boot=Q->array[Q->front];
		if(Q->front==Q->rear)
         Q->front=Q->rear=-1;
         else
         Q->front=(Q->front+1)%Q->capacity;
	}
	return boot;
}
void LevelOrder(struct BSTnode *root)
{
   struct arrayQ *Q;
   struct BSTnode *temp;
   Q=CreateQ();
   if(root)
   enQueue(Q,root);
   while(!isEmpty(Q))
   {
   	 temp=deQ(Q);
   	 printf("%d ",temp->data);
   	 if(temp->left)
   	 enQueue(Q,temp->left);
   	 if(temp->right)
   	 enQueue(Q,temp->right);
   }
}
struct BSTnode* newnode(int data)
{
	struct BSTnode *s;
	s=(struct BSTnode*)malloc(sizeof(struct BSTnode));
	s->left=NULL;
	s->right=NULL;
    s->data=data;
    return s;
}
struct BSTnode* insert(struct BSTnode *root,int data)
{
	struct BSTnode *s;
	if(root==NULL)
	{
	   s=newnode(data);
	   root=s;	
	}
    if(root->data>data)
	root->left=insert(root->left,data);
	if(root->data<data)
	root->right=insert(root->right,data);
	return root;
}
void inorder(struct BSTnode* root)
{
	if(root)
	{
		inorder(root->left);
		printf("%d ",root->data);
		inorder(root->right);
	}
}
struct BSTnode* find_max(struct BSTnode *root)
{
	while(root->right!=NULL)
	root=root->right;
	return root;
}
struct BSTnode* delete_node(struct BSTnode *root,int data)
{
	struct BSTnode *s;
	if(root==NULL)
	printf("\nThe data do not exit");
	else if(root->data>data)
	 root->left=delete_node(root->left,data);
	else if(root->data<data)
	root->right=delete_node(root->right,data);
	else
	{
		if(root->right&&root->left)
		{
			s=find_max(root->left);
			root->data=s->data;
			root->left=delete_node(root->left,data);
		}
		else
		{
			s=root;
			if(root->right==NULL)
			root=root->left;
			if(root->left==NULL)
			root=root->right;
			free(s);
		}
	}
	return root;
}
int display_leaf(struct BSTnode *root)
{
	if(root)
	{
		if(root->left==NULL&&root->right==NULL)
		 {
		  printf("%d",root->data);
	     }
		else if(root->left==NULL)
		 display_leaf(root->right);
		else if(root->right==NULL)
		 display_leaf(root->left);
		 else
		 {
		 	display_leaf(root->left);
		 	display_leaf(root->right);
		   }  
	}
}
int count_node(struct BSTnode *root,int i)
{
	if(root)
	{
		i++;
		if(root->left!=NULL&&root->right!=NULL)
		{
		   i=count_node(root->left,i);
		   i=count_node(root->right,i);	
		}
		else if(root->left!=NULL)
		 i=count_node(root->left,i);
		else if(root->right!=NULL)
	   	i=count_node(root->right,i);	
	}
	 return i;
}
int max_height(int a,int b)
{
	if(a>=b)
	return a;
	else 
	return b;
}
int height(struct BSTnode *root,int i)
{
	int a,i1,i2;
	if(root)
	{
		i++;
		a=i;
		if(root->left!=NULL&&root->right!=NULL)
		{
			i1=height(root->left,i);
			i2=height(root->right,i);
			a=max_height(i1,i2);
		}
		 else if(root->left!=NULL)
		  a=height(root->left,i);
		 else if(root->right!=NULL)
		  a=height(root->right,i);  
	}
	return a;
}
int ex_leaf(struct BSTnode *root,int i)
{
	if(root)
	{
		if(root->left!=NULL || root->right!=NULL)
		{
			i++;
			if(root->left!=NULL&&root->right!=NULL)
			{
				i=ex_leaf(root->right,i);
				i=ex_leaf(root->left,i);
			}
			else if(root->left!=NULL)
			 i=ex_leaf(root->left,i);
			else if(root->right!=NULL)
			 i=ex_leaf(root->right,i);
		}
		return i;
    }
}
int sum_node(struct BSTnode *root,int sum)
{
	if(root)
	{
		sum+=root->data;
		if(root->right!=NULL)
		  sum=sum_node(root->right,sum);
		if(root->left!=NULL)
		 sum=sum_node(root->left,sum);  	
	}
	return sum;
}
void display_left(struct BSTnode *root)
{
	if(root)
	{
	   if(root->left)
	   {
	   	 printf("%d ",root->left->data);
	   	 if(root->left!=NULL)
	   	   display_left(root->left);
	   	  if(root->right!=NULL)
	   	   display_left(root->right);
	   }
	}
}
int cal_dis(struct BSTnode *root,int data,int i)
{
	if(root==NULL)
	 i=0;
	else if(root->data>data)
	 i=cal_dis(root->left,data,i+1);
	else if(root->data<data)
	 i=cal_dis(root->right,data,i+1);
	else 
	i++;
	return i;   	
}
struct BSTnode* search(struct BSTnode *root,int data)
{
	if(root==NULL)
	return NULL;
	if(root->data>data)
	root=search(root->left,data);
	if(root->data<data)
	root=search(root->right,data);
	return root;
}
int common_an(struct BSTnode *root,int data1,int data2)
{
	int a;
	if(search(root,data1)==NULL||search(root,data2)==NULL)
	 return 0;
	else
	{
		 if(root->data>data1&&root->data>data2)
		   a=common_an(root->left,data1,data2);
		 else if(root->data<data1&&root->data<data2)
		  a=common_an(root->right,data1,data2);
         else
         a=root->data;
         return a;
	} 
}

int main()
{
	struct BSTnode *root=NULL;
	struct BSTnode *soot;
	int data,choice,a,b,data2;
	while(1)
	{
		printf("\n1.Insert");
		printf("\n2.Inorder Display");
		printf("\n3.Delete");
		printf("\n4.Dispaly leaf");
		printf("\n5.Count nodes");
		printf("\n6.Height");
		printf("\n7.Ex_leaf count");
		printf("\n8.Sum_node");
		printf("\n9.Display leftsubtree");
		printf("\n10.Search");
		printf("\n11.Print LCA");
		printf("\n12.LevelOrdertranvsversal");
		printf("\nEnter your choice");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("\nEnter the data to be inserted");
			        scanf("%d",&data);
			        root=insert(root,data);
			break;
			case 2: inorder(root);
			break;
			case 3: printf("\nEnter the data you want to delete");
			        scanf("%d",&data);
			        root=delete_node(root,data);
			break;
			case 4: display_leaf(root);
			break;
			case 5: data=count_node(root,0);
			         printf("\n%d",data);
			break; 
			case 6: data=height(root,0);
			        printf("The height is %d",data-1);
			break;	
			case 7: data=ex_leaf(root,0);
			        printf("Ex-leaf=%d",data);
			break;	
			case 8: data=sum_node(root,0);
			        printf("SUM=%d",data);
			break;
			case 9: display_left(root);
			break;	
			case 10:  printf("\nEnter the data");
			          scanf("%d",&data);
			          soot=search(root,data);
			          if(soot!=NULL)
			          printf("%d exist",soot->data);
			break;
			case 11: printf("\nEnter both the datas");
			         scanf("%d %d",&data,&data2);
					 a=common_an(root,data,data2);
					 if(a!=0)
					  printf("The LCA is %d",a);
			break;	
			case 12:  LevelOrder(root);
			break;	  		 		        
			default: printf("Invalid");        
		}
	}
}
