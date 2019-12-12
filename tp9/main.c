#include "test.h"

int main(int argc, char const *argv[])
{
   int size = 4;
   char *names[] = {"name1", "name2", "name3", "name4"};
   char *surnames[] = {"surname1", "surname2", "surname3", "surname4"};
   int notes[] = {1, 2, 33};
   enum Credit cre[] = {F, AA, CC};

   StudentTree *head = create_empty_tree();
   add_student_to_tree(&head, create_student("name1", "surname", notes, cre, 10));
   add_student_to_tree(&head, create_student("name2", "surname", notes, cre, 10));
   print_tree(head);
   return 0;
}
