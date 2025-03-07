#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
char *data;
struct node *left,*right,*parent;
}node;
node * newNode(char *val)
{
node *n = malloc(sizeof(node));
n->data = malloc(strlen(val)+1);
strcpy(n -> data , val);
n -> left = NULL;
n -> right = NULL;
return n;
}
node *lastvisited = NULL;
node *insert(node *root,char *str)
{
if(root == NULL)
root = newNode(str);
if(strcasecmp(str,root->data) < 0)
root -> left = insert(root->left,str);
else if(strcasecmp(str,root->data) > 0)
root -> right = insert(root->right,str);
return root;
}
void inorder(node *root)
{
if(root != NULL)
{
inorder(root->left);
printf("%s",root->data);
inorder(root->right);
}
}
node* frrread(node *root)
{
char str[100];
FILE *f = fopen("Dictionary.txt","r");
if(f != NULL)
{
while(!feof(f))
{
fscanf(f,"%s",str);
root = insert(root,str);
}
fclose(f);
}
return root;
}
int height(node *root)
{
if(root == NULL)
return -1;
else
{
int lh = height(root -> left);
int rh = height(root -> right);
return lh>rh?lh+1:rh+1;
}}
int count(node *root)
{
if(root == NULL)
return 0;
else
{
int c1 = count(root -> left);
int c2 = count(root -> right);
return 1+c1+c2;
}
}
node *search(node *root , char* str)
{
node *temp = root;
while(temp != NULL)
{
if(strcasecmp(str, temp->data)==0)
return temp;
else if(strcasecmp(str, temp->data) < 0)
{
lastvisited = temp;
temp = temp -> left;
}
else
{
lastvisited = temp;
temp = temp -> right;
}
}
return NULL;
}
node* getsuccessor(node *root)
{
if(lastvisited -> right != NULL)
{
node *temp = lastvisited -> right;
while(temp -> left != NULL)
temp = temp -> left;
return temp; //min node
}
else{
node *successor = NULL;
node *ancestor = root;
while( ancestor != lastvisited)
{
if(strcasecmp(lastvisited -> data,ancestor -> data) < 0)
{
successor = ancestor;
ancestor = ancestor ->left;
}
else ancestor = ancestor -> right;
}
return successor;
}
}
node *getpredecessor(node *root)
{
if(lastvisited -> left != NULL)
{
node *temp = lastvisited -> left;
while(temp -> right != NULL)
temp = temp -> right;
return temp; //max node
}
else
{
node *predecessor = NULL;
node *ancestor = root;
while(ancestor != NULL)
{
if(strcasecmp(lastvisited->data, ancestor->data) > 0)
{
predecessor = ancestor;
ancestor = ancestor->right;
}
else if(strcasecmp(lastvisited->data, ancestor->data) < 0)
ancestor = ancestor->left;
else
break;
}
return predecessor;
}
}
int main()
{
char str[200];
node *root = NULL;
node *searchnode = NULL;
node *success = NULL;
node *predess = NULL;
root = frrread(root);
if(root)
printf("Dictionary Loaded Successfully...!\n-----------------------------------------------\n");
printf("size is %d\n-----------------------------------------------\n",count(root));
printf("height is %d\n-----------------------------------------------\n",height(root));
printf("enter sentence : ");
fgets(str, sizeof(str), stdin);
char *token = strtok(str," \n");
while(token != NULL)
{
if(search(root,token) != NULL)
printf("%s - CORRECT \n",token);
else
{
printf("%s - INCORRECT , Suggestions : ",token);
success = getsuccessor(root);
predess = getpredecessor(root);
printf("%s %s %s\n",lastvisited -> data,success -> data, predess->data);
}
token = strtok(NULL, " \n");
}
return 0;
}


