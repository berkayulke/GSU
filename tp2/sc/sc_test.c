#include "sc.h"

int main()
{
  int choice = 10;
  PersonList *person_list = create_empty_person_list();
  CityList *city_list = create_empty_city_list();
  while (choice)
  {
    printf("1 - Add Person\n");
    printf("2 - Add City\n");
    printf("3 - Delete Person\n");
    printf("4 - Delete City\n");
    printf("5 - Search Person\n");
    printf("6 - Search City\n");
    printf("7 - Print Person List\n");
    printf("8 - Print City List\n");
    printf("0 - Exit\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:;
      get_person(&person_list);
      break;
    case 2:;
      get_city(&city_list);
      break;
    case 3:;
      char surname_of_person[128];
      printf("surname_of_person:\n ");
      scanf("%s", &surname_of_person);
      person_list = delete_person(person_list, surname_of_person);
      break;
    case 4:;
      char name_of_city[128];
      printf("name_of_city:\n ");
      scanf("%s", &name_of_city);
      city_list = delete_city(city_list, name_of_city);
      break;
    case 5:;
      char search_by_surname[128];
      printf("Surname:\n ");
      scanf("%s", &search_by_surname);
      search_person(person_list, search_by_surname, city_list);
      break;
    case 6:;
      char search_by_city_name[128];
      printf("Name:\n ");
      scanf("%s", &search_by_city_name);
      City *city_res = search_city(city_list, search_by_city_name);
      print_city(city_res);
      break;
    case 7:;
      print_person_list(person_list, city_list);
      break;
    case 8:;
      print_city_list(city_list);
      break;
    default:
      choice = 0;
      break;
    }
  }
}