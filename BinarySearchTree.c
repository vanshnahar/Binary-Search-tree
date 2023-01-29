#include <stdio.h>
#include <stdlib.h>
struct node
{
  int data;
  struct node *lc;
  struct node *rc;
};
struct node *root;

void displayinorder(struct node *temp)
{
  if (temp)
  {
    displayinorder(temp->lc);
    printf("%d\t", temp->data);
    displayinorder(temp->rc);
  }
}
struct node *insert(struct node *temp, int key)
{
  struct node *newnode;
  if (temp == 0)
  {
    newnode = malloc(sizeof(struct node));
    newnode->lc = newnode->rc = NULL;
    newnode->data = key;
    temp = newnode;
  }
  else
  {
    if (key < temp->data)
      temp->lc = insert(temp->lc, key);
    else
      temp->rc = insert(temp->rc, key);
  }
  // displayinorder(temp);
  return temp;
}

struct node *search(struct node *temp, int key)
{
  if (temp == NULL)
    return NULL;
  if (key == temp->data)
    return temp;
  else if (key < temp->data)
    search(temp->lc, key);
  else
    search(temp->rc, key);
}
int height(struct node *t)
{
  int x, y;
  if (t == NULL)
  {
    return 0;
  }
  else
  {
    x = height(t->lc);
    y = height(t->rc);
    return (x > y) ? x + 1 : y + 1;
  }
}
struct node *inpre(struct node *temp)
{
  while (temp && temp->rc != 0)
    temp = temp->rc;
  return temp;
}
struct node *insuc(struct node *temp)
{
  while (temp && temp->lc != 0)
    temp = temp->lc;
  return temp;
}
struct node *delete(struct node *temp, int key)
{
  struct node *q;
  if (temp == NULL)
    return NULL;
  if (temp->lc == 0 && temp->rc == 0)
  {
    if (temp == root)
      root == NULL;
    free(temp);
    return NULL;
  }

  if (key < temp->data)
    temp->lc = delete (temp->lc, key);
  else if (key > temp->data)
    temp->rc = delete (temp->rc, key);
  else
  {
    if (height(temp->lc) > height(temp->rc))
    {
      q = inpre(temp->lc);
      temp->data = q->data;
      temp->lc = delete (temp->lc, q->data);
    }
    else
    {
      q = insuc(temp->rc);
      temp->data = q->data;
      temp->rc = delete (temp->rc, q->data);
    }
  }
  return temp;
}
int main(void)
{
  int c, n, key;
  struct node *current;
  printf("\n1:create a binary tree\n2:insert in binary tree\n3:Delete from binary tree\n4:display binary tree\n5:search element in binary tree\n6:exit");

  while (1)
  {
    printf("\n===================================================");
    printf("\nenter your choice:");
    scanf("%d", &c);
    switch (c)
    {
    case 1:
      printf("enter the no of element you want to insert in binary tree :");
      scanf("%d", &n);
      for (int i = 0; i < n; i++)
      {
        printf("write the elements:");
        scanf("%d", &key);
        root = insert(root, key);
      }
      displayinorder(root);
      break;

    case 2:
      printf("enter the value you want to insert :");
      scanf("%d", &key);
      root = insert(root, key);
      displayinorder(root);
      break;
    case 3:
      printf("enter the value you want to delete :");
      scanf("%d", &key);
      root = delete (root, key);
      displayinorder(root);
      break;

    case 4:
      displayinorder(root);
      break;
    case 5:
      printf("enter the value you want to search :");
      scanf("%d", &key);
      current = search(root, key);
      if (current != NULL)
        printf("the element %d is found in binary tree", key);
      else
        printf("the element %d is not found ", key);
      break;
    case 6:
      exit(0);
    }
  }
}