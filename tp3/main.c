#include "tree.h"
int main(int argc, char const *argv[])
{
  Tree *tree_head = create_node(0, "");

  tree_head = insert_node(tree_head, create_node(10, "SW"));
  tree_head = insert_node(tree_head, create_node(20, "SW"));
  tree_head = insert_node(tree_head, create_node(30, "SW"));
  tree_head = insert_node(tree_head, create_node(40, "SW"));
  tree_head = insert_node(tree_head, create_node(50, "SW"));
  tree_head = insert_node(tree_head, create_node(25, "SW"));

  print_tree(tree_head, LEVEL);
  tree_head = delete_node(tree_head, 40);
  print_tree(tree_head, LEVEL);
  tree_head = delete_node(tree_head, 20);
  print_tree(tree_head, LEVEL);
  tree_head = delete_node(tree_head, 25);
  print_tree(tree_head, LEVEL);

  int input = 1;
  while (input)
  {
    printf("1 - Add new country\n");
    printf("2 - List all countries\n");
    printf("3 - Delete country\n");
    printf("4 - Search country\n");
    printf("0 - Exit\n");
    scanf("%i", &input);
    switch (input)
    {
    case 1:
      printf("Country shortname (2 characters) \n");
      char *country_name = malloc(2 * sizeof(char));
      int code;
      scanf("%s", country_name);
      printf("Country code \n");
      scanf("%i", &code);
      tree_head = insert_node(tree_head, create_node(code, country_name));
      free(country_name);
      break;
    case 2:
      printf("  Choose your method:\n");
      printf("  1 - Preorder\n");
      printf("  2 - Inorder\n");
      printf("  3 - Postorder\n");
      printf("  4 - Levelorder\n");
      int method;
      scanf("%i", &method);
      print_tree(tree_head, method - 1);
      break;
    case 3:
      printf("Enter country code: \n");
      int country_code;
      scanf("%i", &country_code);
      tree_head = delete_node(tree_head, country_code);
      break;
    case 4:
      printf("Enter country code: \n");
      int code4;
      scanf("%i", &code4);
      Tree *res = search_node(tree_head, code4);
      printf("Name: %s", res->name);
      printf("Code: %i", res->code);
      break;

    default:
      return 0;
    }
  }
  return 0;
}