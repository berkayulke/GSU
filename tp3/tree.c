#include "tree.h"

int max(int n1, int n2)
{
  if (n1 > n2)
    return n1;
  return n2;
}
int min(int n1, int n2)
{
  if (n1 < n2)
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
      printf("___");
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
    switch (cur->b_fac)
    {
    case D_LEFT:
      printf("DLF");
      break;
    case LEFT:
      printf("LFT");
      break;
    case EQ:
      printf("EQL");
      break;
    case RIGHT:
      printf("RGT");
      break;
    case D_RIGHT:
      printf("DRT");
      break;
    default:
      printf("   ");
      break;
    }
    for (int i = 0; i < max(space_between, 1); i++)
      printf(" ");
    cur = cur->next;
  }
}

Tree *insert_node(Tree *head, Tree *new)
{
  if (!head->code)
  {
    head->code = new->code;
    head->name = strdup(new->name);
    return head;
  }

  else if (new->code <= head->code)
  {
    if (head->left)
      head->left = insert_node(head->left, new);
    else
      head->left = new;
    head->b_fac--;
  }
  else
  {

    if (head->right)
      head->right = insert_node(head->right, new);
    else
      head->right = new;
    head->b_fac = max(head->b_fac++, D_RIGHT);
  }
  head->b_fac = get_balance_fac(head);
  return head;
}

Tree *create_node(int code, char *name)
{
  Tree *node = malloc(sizeof(Tree));
  node->code = code;
  node->name = strdup(name);
  node->left = NULL;
  node->right = NULL;
  node->b_fac = EQ;
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
  if (!head)
    return -1;
  Tree *cur = head;
  if (cur->left && cur->right)
    return 1 + max(find_height(cur->left), find_height(cur->right));
  if (cur->right && !cur->left)
    return 1 + find_height(cur->right);
  else if (cur->left && !cur->right)
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
        cur->name = strdup(max->name);
        if (cur == prev)
        {
          prev->left = max->left;
          free(max);
          return head;
        }
        prev->right = NULL;
        return head;
      }
      if (cur->right)
      {
        //cur -> 25
        Tree *min = find_min(cur->right);       //30
        Tree *prev = get_prev(head, min->code); //25
        cur->code = min->code;
        cur->name = strdup(min->name);
        if (cur == prev)
        {
          prev->right = min->right;
          free(min);
          return head;
        }
        prev->left = NULL;
        return head;
      }
      if (!cur->right && !cur->left)
      {
        Tree *prev = get_prev(head, cur->code);
        if (cur->code < prev->code)
          prev->left = NULL;
        else
          prev->right = NULL;
        free(cur);
        return head;
      }
    }

    //keep going
    if (value < cur->code)
      cur = cur->left;
    else
      cur = cur->right;
  }
  return head;
}

List *get_level(Tree *head, int level)
{
  if (!head)
  {
    List *list_head = malloc(sizeof(List));
    list_head->code = 0;
    list_head->name = NULL;
    list_head->b_fac = EQ;
    List *cur = list_head;
    for (int i = 0; i < power(2, level) - 1; i++)
    {
      cur->next = malloc(sizeof(List));
      cur->next->code = 0;
      cur->next->name = NULL;
      cur->next->b_fac = EQ;
      cur = cur->next;
    }
    cur->next = NULL;
    return list_head;
  }
  if (level == 0)
  {
    List *list_head = malloc(sizeof(List));
    list_head->next = NULL;
    if (head)
    {
      list_head->code = head->code;
      list_head->name = strdup(head->name);
      list_head->b_fac = head->b_fac;
    }
    else
    {
      list_head->code = 0;
      list_head->name = NULL;
      list_head->next->b_fac = EQ;
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

Tree *search_node(Tree *head, int value)
{
  Tree *cur = head;
  while (cur)
  {
    if (value == cur->code)
      break;
    else if (value < cur->code)
      cur = cur->left;
    else
      cur = cur->right;
  }
  return cur;
}

//AVL
int get_balance_fac(Tree *head)
{
  if (!head)
    return EQ;
  else
    return EQ - find_height(head->left) + find_height(head->right);
}

Tree *left_rotate_avl(Tree *head)
{
  Tree *right = head->right;
  Tree *new_right = right->left;
  right->left = head;
  head->right = new_right;

  right->b_fac = get_balance_fac(right);
  if (right->left)
    right->left->b_fac = get_balance_fac(right->left);
  if (right->right)
    right->right->b_fac = get_balance_fac(right->right);
  return right;
}

Tree *right_rotate_avl(Tree *head)
{
  Tree *left = head->left;
  Tree *new_left = left->right;
  left->right = head;
  head->left = new_left;

  left->b_fac = get_balance_fac(left);
  if (left->left)
    left->left->b_fac = get_balance_fac(left->left);
  if (left->right)
    left->right->b_fac = get_balance_fac(left->right);
  return left;
}

Tree *balance_tree(Tree *head)
{
  if (!head)
    return head;
  if (head->b_fac == D_LEFT)
  {

    if (head->left->b_fac == D_LEFT)
      head = right_rotate_avl(head);
    else if (head->left->right && head->left->right->b_fac == D_RIGHT)
    {
      head->left = left_rotate_avl(head->left);
      head = right_rotate_avl(head);
    }
  }
  else if (head->b_fac >= D_RIGHT)
  {

    if (head->right->b_fac >= D_RIGHT)
    {
      head = left_rotate_avl(head);
    }
    else if (head->right->left && head->right->left->b_fac == D_RIGHT)
    {
      head->right = right_rotate_avl(head->right);
      head = left_rotate_avl(head);
    }
  }
  head->left = balance_tree(head->left);
  head->right = balance_tree(head->right);
  return head;
}

Tree *insert_avl(Tree *head, Tree *new)
{
  head = insert_node(head, new);
  head = balance_tree(head);
  return head;
}

Tree *delete_avl(Tree *head, int value)
{
  head = delete_node(head, value);
  head = balance_tree(head);
  return head;
}

int is_balanced(Tree *head)
{
  if (!head)
    return 1;
  if (head->b_fac == D_LEFT || head->b_fac == D_RIGHT)
    return 0;
  else
    return min(is_balanced(head->right), is_balanced(head->left));
}
