#include "tree.h"

int max(int n1, int n2)
{
  if (n1 > n2)
    return n1;
  return n2;
}

List *get_last(List *head)
{
  if (!head->next)
    return head;
  List *cur = head;
  List *prev = NULL;
  while (cur)
  {
    prev = cur;
    cur = cur->next;
  }
  return prev;
}

List *push(List *head, int new_num)
{
  if (!head->code)
  {
    head->code = new_num;
    return head;
  }
  List *last = get_last(head);
  List *new_node = malloc(sizeof(List));
  new_node->next = NULL;
  new_node->code = new_num;
  last->next = new_node;
  return head;
}

int *to_array(List *head)
{
  int lenght = 0;
  int *ar2 = malloc(sizeof(int));

  int *ar = malloc(lenght * sizeof(int));
  List *cur = head;
  for (int i = 0; i < lenght; i++)
  {
    ar[i] = cur->code;
    cur = cur->next;
  }
  return ar;
}

void print_list(List *head, int space_count)
{
  List *cur = head;
  while (cur)
  {
    if (cur->code)
      printf("%i", cur->code);
    else
      printf("000");
    for (int i = 0; i < max(space_count, 1); i++)
      printf(" ");

    cur = cur->next;
  }
}

Tree *insert_node(Tree *head, Tree *new)
{
  if (!head->code)
    head->code = new->code;

  else if (new->code <= head->code)
  {
    if (head->left)
      head->left = insert_node(head->left, new);
    else
    {
      head->left = new;
    }
  }
  else
  {
    if (head->right)
      head->right = insert_node(head->right, new);
    else
    {
      head->right = new;
    }
  }

  return head;
}

Tree *create_node(int code, char *name, Tree *left, Tree *right)
{
  Tree *node = malloc(sizeof(Tree));
  node->code = code;
  node->name = strdup(name);
  node->left = left;
  node->right = right;
  return node;
}

Tree *find_min(Tree *head)
{
  if (!head->left)
    return head;

  Tree *cur = head->left;
  Tree *prev = head;
  while (cur)
  {
    prev = cur;
    cur = cur->left;
  }
  return prev;
}

Tree *find_max(Tree *head)
{
  if (!head->right)
    return head;

  Tree *cur = head->right;
  Tree *prev = head;
  while (cur)
  {
    prev = cur;
    cur = cur->right;
  }
  return prev;
}

int find_height(Tree *head)
{
  Tree *cur = head;
  if (cur->left && cur->right)
    return 1 + max(find_height(cur->left), find_height(cur->right));
  if (cur->right)
    return 1 + find_height(cur->right);
  else if (cur->left)
    return 1 + find_height(cur->left);
  else
    return 0;
}

Tree *delete_node(Tree *head, int value)
{
  return NULL;
}

List *get_level(Tree *head, int level)
{
  if (level == 0)
  {
    List *list_head = malloc(sizeof(List));
    list_head->next = NULL;
    if (head)
      list_head->code = head->code;
    else
      list_head->code = 0;
    return list_head;
  }
  else
  {
    List *left_list = get_level(head->left, level - 1);
    List *right_list = get_level(head->right, level - 1);
    List *left_last = get_last(left_list);
    left_last->next = right_list;
    return left_list;
  }
}

int power(int base, int pow)
{
  int res = 1;
  for (int i = 0; i < pow; i++)
    res *= base;
  return res;
}


/*
                                                                     bastan     arada
                              111                                    30(2^5-2)
              111                             222                    14(2^4-2)    29
      111             222             333             444            6 (2^3-2)    13
  111     222     333     444     555     666     777     888        2 (2^2-2)    05
111 222 333 444 555 666 777 888 000 111 222 333 444 555 666 777      0            01
  */
void print_tree(Tree* tree_head)
{
    int height = find_height(tree_head) + 1;

  for (int i = 0; i < height; i++)
  {
    int start_space = power(2, height - i + 1) - 2;
    int space_between = 2 * start_space +1;
    for (int j = 0; j < start_space; j++)
      printf(" ");
    print_list(get_level(tree_head, i), space_between);
    printf("\n");
  }
}

int main(int argc, char const *argv[])
{
  Tree *tree_head = create_node(511, "TR", NULL, NULL);

  tree_head = insert_node(tree_head, create_node(811, "FR", NULL, NULL));
  tree_head = insert_node(tree_head, create_node(611, "FR", NULL, NULL));
  tree_head = insert_node(tree_head, create_node(711, "FR", NULL, NULL));
  tree_head = insert_node(tree_head, create_node(311, "EN", NULL, NULL));
  tree_head = insert_node(tree_head, create_node(411, "EN", NULL, NULL));
  tree_head = insert_node(tree_head, create_node(211, "IT", NULL, NULL));
  tree_head = insert_node(tree_head, create_node(111, "GR", NULL, NULL));
  tree_head = insert_node(tree_head, create_node(911, "FR", NULL, NULL));




 print_tree(tree_head);


  return 0;
}
