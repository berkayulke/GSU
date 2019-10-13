#include "sc.h"

//tested
Person *create_person(char *name, char *surname, char *city, char *homeNumber)
{
  Person *per = malloc(sizeof(Person));

  per->name = malloc(sizeof(char *));
  per->surname = malloc(sizeof(char *));
  per->city = malloc(sizeof(char *));
  per->homeNumber = malloc(sizeof(char *));

  strcpy(per->city, city);
  strcpy(per->name, name);
  strcpy(per->surname, surname);
  strcpy(per->homeNumber, homeNumber);

  return per;
}

PersonList *create_empty_person_list()
{
  PersonList *head = malloc(sizeof(PersonList));
  head->next = head;
  head->person = NULL;
  return head;
}

Person *copy_person(Person *source)
{
  Person *target = create_person(source->name, source->surname, source->city, source->homeNumber);
  return target;
}

PersonList *get_last_person(PersonList *head)
{
  PersonList *cur = head;
  while (cur->next != head)
    cur = cur->next;
  return cur;
}

PersonList *add_person_before(PersonList *head, Person *new_pers)
{
  PersonList *new_node = create_empty_person_list();
  get_last_person(head)->next = new_node;
  new_node->person = copy_person(new_pers);
  new_node->next = head;
  return new_node;
}

PersonList *add_person(PersonList *head, Person *new_pers)
{
  //boşsa
  if (!head->person)
  {
    head->person = copy_person(new_pers);
    head->next = head;
    return head;
  }
  //tek elemanlıysa
  else if (head->next == head)
  {
    add_person_before(head, new_pers);
    if (strcmp(head->person->surname, new_pers->surname) >= 0)
      return head->next;
    else
      return head;
  }
  if (strcmp(head->person->surname, new_pers->surname) >= 0)
    return add_person_before(head, new_pers);

  PersonList *cur = head->next;
  while (cur != head)
  {
    if (strcmp(cur->person->surname, new_pers->surname) >= 0)
    {
      add_person_before(cur, new_pers);
      return head;
    }
    cur = cur->next;
  }
  add_person_before(head, new_pers);
  return head;
}

PersonList *delete_person(PersonList *head, char *surname)
{
  PersonList *cur = head->next;
  PersonList *prev = head;
  PersonList *last = get_last_person(head);
  if (strcmp(head->person->surname, surname) == 0)
  {
    if (head->next == head)
    {
      free(head);
      return create_empty_person_list();
    }
    last->next = head->next;
    PersonList *for_ret = head->next;
    free(head);
    return for_ret;
  }

  while (cur != head && head->person)
  {
    if (strcmp(cur->person->surname, surname) == 0)
    {
      prev->next = cur->next;
      free(cur);
      return head;
    }
    prev = cur;
    cur = cur->next;
  }
  printf("Couldn't find it\n");
  return head;
}

void print_person(Person *person, CityList *city_list)
{
  City *city = NULL;
  //city = search_city(city_list, person->city);
  printf("Name:       %s\n", person->name);
  printf("Surname:    %s\n", person->surname);
  printf("City:       %s\n", person->city);
  if (city)
  {
    printf("Home Number: (%i) %s\n", city->code, person->homeNumber);
  }
  else
  {
    printf("Home Number: %s\n", person->homeNumber);
  }

  printf("-------------------\n");
}

void print_person_list(PersonList *head, CityList *city_list)
{
  printf("-------------------\n");
  PersonList *cur = head;
  PersonList *last = get_last_person(head);

  while (cur->person && cur != last)
  {
    print_person(cur->person, city_list);
    cur = cur->next;
  }
  if (cur->person)
    print_person(cur->person, city_list);
}

void search_person(PersonList *head, char *surname, CityList *city_list)
{
  PersonList *cur = head;
  PersonList *last = get_last_person(head);

  while (cur && cur != last)
  {
    if (strcmp(cur->person->surname, surname) == 0)
    {
      printf("-------------------\n");
      printf("person is: \n");
      print_person(cur->person, city_list);
      return;
    }
    cur = cur->next;
  }
  if (strcmp(cur->person->surname, surname) == 0)
  {
    printf("-------------------\n");
    printf("person is: \n");
    print_person(cur->person, city_list);
    return;
  }
  printf("Couldn't find it \n");
}

CityList *create_empty_city_list()
{
  CityList *head = malloc(sizeof(CityList));
  head->next = head;
  head->city = NULL;
  return head;
}

City *create_city(char *name, int code)
{
  City *new_city = malloc(sizeof(City));
  new_city->code = code;
  new_city->name = malloc(sizeof(char *));
  strcpy(new_city->name, name);
  return new_city;
}

City *copy_city(City *source)
{
  City *new_city = create_city(source->name, source->code);
  return new_city;
}

CityList *get_last_city(CityList *head)
{
  CityList *cur = head;
  while (cur->next != head)
    cur = cur->next;
  return cur;
}

CityList *add_city_before(CityList *head, City *new_city)
{
  CityList *new_node = create_empty_city_list();
  get_last_city(head)->next = new_node;
  new_node->city = copy_city(new_city);
  new_node->next = head;
  return new_node;
}

CityList *add_city(CityList *head, City *new_city)
{
  if (!head->city)
  {
    head->city = copy_city(new_city);
    head->next = head;
    return head;
  }
  //tek elemanlıysa
  else if (head->next == head)
  {
    add_city_before(head, new_city);
    if (strcmp(head->city->name, new_city->name) >= 0)
      return head->next;
    else
      return head;
  }
  if (strcmp(head->city->name, new_city->name) >= 0)
    return add_city_before(head, new_city);

  CityList *cur = head->next;
  while (cur != head)
  {
    if (strcmp(cur->city->name, new_city->name) >= 0)
    {
      add_city_before(cur, new_city);
      return head;
    }
    cur = cur->next;
  }
  add_city_before(head, new_city);
  return head;
}

City *search_city(CityList *head, char *name)
{
  if (!head || !name)
    return NULL;
  CityList *cur = head;
  CityList *last = get_last_city(head);

  while (cur)
  {
    if (cur == last)
      break;
    if (strcmp(cur->city->name, name) == 0)
      return cur->city;

    cur = cur->next;
  }
  if (strcmp(cur->city->name, name) == 0)
    return cur->city;
  return NULL;
}

CityList *delete_city(CityList *head, char *name)
{
  CityList *cur = head->next;
  CityList *prev = head;
  CityList *last = get_last_city(head);

  if (strcmp(head->city->name, name) == 0)
  {
    if (head->next == head)
    {
      free(head);
      return create_empty_city_list();
    }
    last->next = head->next;
    CityList *for_ret = head->next;
    free(head);
    return for_ret;
  }

  while (cur != head && head->city)
  {
    if (strcmp(cur->city->name, name) == 0)
    {
      prev->next = cur->next;
      free(cur);
      return head;
    }
    cur = cur->next;
  }
  printf("Couldn't find it\n");
  return head;
}
void print_city(City *city)
{
  if (city)
  {
    printf("City Name:    %s\n", city->name);
    printf("City Code:    %i\n", city->code);
    printf("-------------------\n");
  }
  else
  {
    printf("Couldn't find it\n");
  }
}
void print_city_list(CityList *head)
{
  printf("-------------------\n");
  CityList *cur = head;
  CityList *last = get_last_city(head);

  while (cur->city)
  {
    if (cur == last)
      break;
    print_city(cur->city);
    cur = cur->next;
  }
  if (cur->city)
    print_city(cur->city);
}

void get_person(PersonList **head)
{
  char name[128], surname[128], city[128], home_number[128];
  printf("Name:\n ");
  scanf("%s", &name);
  printf("Surame:\n ");
  scanf("%s", &surname);
  printf("City:\n ");
  scanf("%s", &city);
  printf("Home Number:\n ");
  scanf("%s", &home_number);
  Person *new_pers = create_person(name, surname, city, home_number);
  *head = add_person(*head, new_pers);
}

void get_city(CityList **head)
{
  char name[128];
  int code;
  printf("Name:\n ");
  scanf("%s", &name);
  printf("Code:\n ");
  scanf("%i", &code);
  City *new_city = create_city(name, code);
  *head = add_city(*head, new_city);
}