#include "tree.h"

int max(int n1, int n2)
{
  if (n1 > n2)
    return n1;
  return n2;
}

int power(int base, int pow)
{
  int res = 1;
  for (int i = 0; i < pow; i++)
    res *= base;
  return res;
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

List *push(List *head, int new_num, char *new_name)
{
  if (!head->code)
  {
    head->code = new_num;
    head->name = strdup(new_name);
    return head;
  }
  List *last = get_last(head);
  List *new_node = malloc(sizeof(List));
  new_node->next = NULL;
  new_node->code = new_num;
  new_node->name = strdup(new_name);
  last->next = new_node;
  return head;
}

void print_list(List *head, int space_between, int start_space)
{
  List *cur = head;
  for (int i = 0; i < start_space; i++)
    printf(" ");

  while (cur)
  {
    printf("%03d", cur->code);
    for (int i = 0; i < max(space_between, 1); i++)
      printf(" ");
    cur = cur->next;
  }
  printf("\n");
  for (int i = 0; i < start_space; i++)
    printf(" ");
  cur = head;
  while (cur)
  {
    if (cur->name)
      printf("%s ", cur->name);
    else
      printf("   ");
    for (int i = 0; i < max(space_between, 1); i++)
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

Tree *create_node(int code, char *name)
{
  Tree *node = malloc(sizeof(Tree));
  node->code = code;
  node->name = strdup(name);
  node->left = NULL;
  node->right = NULL;
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

Tree *get_prev(Tree *head, int value)
{
  Tree *temp = head;
  Tree *prev = NULL;
  while (temp)
  {
    if (temp->code == value)
      return prev;
    prev = temp;
    if (temp->left && value < temp->code)
      temp = temp->left;
    else if (temp->right && value > temp->code)
      temp = temp->right;
    else
      return NULL;
  }
  return NULL;
}

//TO DO - SHOULD BE TESTED
//ya sağın max'ını ya da solun minini getir
Tree *delete_node(Tree *head, int value)
{
  Tree *cur = head;

  while (cur)
  {
    if (cur->code == value)
    {
      if (cur->left)
      {
        Tree *max = find_max(cur->left);
        Tree *prev = get_prev(head, max->code);
        cur->code = max->code;
        prev->right = NULL;
        free(max);
      }
      else if (cur->right)
      {
        Tree *min = find_max(cur->right);
        Tree *prev = get_prev(head, min->code);
        cur->code = min->code;
        prev->left = NULL;
        free(min);
      }
    }

    //keep going
    if (value < cur->code)
      cur = cur->left;
    else
      cur = cur->left;
  }
  return head;
}

List *get_level(Tree *head, int level)
{
  if (level == 0)
  {
    List *list_head = malloc(sizeof(List));
    list_head->next = NULL;
    if (head)
    {
      list_head->code = head->code;
      list_head->name = strdup(head->name);
    }
    else
    {
      list_head->code = 0;
      list_head->name = NULL;
    }
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

/*
                                                                     bastan     arada
                              111                                    30(2^5-2)
              111                             222                    14(2^4-2)    29
      111             222             333             444            6 (2^3-2)    13
  111     222     333     444     555     666     777     888        2 (2^2-2)    05
111 222 333 444 555 666 777 888 000 111 222 333 444 555 666 777      0            01
  */
void amazingly_print_tree(Tree *tree_head)
{
  int height = find_height(tree_head) + 1;
  int i = 1;
  for (int i = 0; i < height; i++)
  {
    int start_space = power(2, height - i + 1) - 2;
    int space_between = 2 * start_space + 1;
    print_list(get_level(tree_head, i), space_between, start_space);
    printf("\n");
  }
}

void print_tree(Tree *head, int order)
{
  switch (order)
  {
  case PRE:
    if (head)
    {
      printf("%i %s\n", head->code, head->name);
      print_tree(head->left, order);
      print_tree(head->right, order);
    }
    break;
  case IN:
    if (head)
    {
      print_tree(head->left, order);
      printf("%i %s\n", head->code, head->name);
      print_tree(head->right, order);
    }
    break;
  case POST:
    if (head)
    {
      print_tree(head->left, order);
      print_tree(head->right, order);
      printf("%i %s\n", head->code, head->name);
    }
    break;
  case LEVEL:
    amazingly_print_tree(head);
    break;

  default:
    break;
  }
}

int main(int argc, char const *argv[])
{
  Tree *tree_head = create_node(51, "TR");

  tree_head = insert_node(tree_head, create_node(81, "FR"));
  tree_head = insert_node(tree_head, create_node(61, "US"));
  tree_head = insert_node(tree_head, create_node(71, "NE"));
  tree_head = insert_node(tree_head, create_node(31, "EN"));
  tree_head = insert_node(tree_head, create_node(41, "SP"));
  tree_head = insert_node(tree_head, create_node(21, "IT"));
  tree_head = insert_node(tree_head, create_node(22, "IT"));
  tree_head = insert_node(tree_head, create_node(11, "GR"));
  tree_head = insert_node(tree_head, create_node(91, "SW"));

  print_tree(tree_head, LEVEL);
  tree_head = delete_node(tree_head, 31);
  print_tree(tree_head, LEVEL);
  return 0;
}