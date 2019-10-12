#include "sl.h"

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

SLList *create_empty_person_list()
{
  SLList *head = malloc(sizeof(SLList));
  head->next = NULL;
  head->person = NULL;
  return head;
}

Person *copy_person(Person *source)
{
  Person *target = create_person(source->name, source->surname, source->city, source->homeNumber);
  return target;
}

SLList *add_person(SLList *head, Person *new_pers)
{
  if (!head->person)
  {
    head->person = copy_person(new_pers);
    head->next = NULL;
    return head;
  }
  SLList *cur = head;
  SLList *prev = NULL;
  while (cur)
  {
    if (strcmp(cur->person->surname, new_pers->surname) >= 0)
    {
      SLList *new_node = create_empty_person_list();
      new_node->next = cur;
      if (prev)
      {
        prev->next = new_node;
        new_node->person = copy_person(new_pers);
        return head;
      }
      else
      {
        new_node->next = head;
        new_node->person = copy_person(new_pers);
        //head'i new_node yap
        return new_node;
      }
    }

    prev = cur;
    cur = cur->next;
  }
  prev->next = create_empty_person_list();
  prev->next->person = copy_person(new_pers);
  return head;
}

SLList *delete_person(SLList *head, char *surname)
{
  SLList *cur = head;
  SLList *prev = NULL;

  while (cur)
  {
    if (strcmp(cur->person->surname, surname) == 0)
    {
      if (!prev)
      {
        SLList *for_return = head->next;
        free(head);
        return for_return;
      }
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
  city = search_city(city_list, person->city);
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

void print_person_list(SLList *head, CityList *city_list)
{
  printf("-------------------\n");
  SLList *cur = head;
  while (cur)
  {
    print_person(cur->person, city_list);
    cur = cur->next;
  }
}

void search_person(SLList *head, char *surname, CityList *city_list)
{
  SLList *cur = head;
  SLList *prev = NULL;

  while (cur)
  {
    if (strcmp(cur->person->surname, surname) == 0)
    {
      printf("-------------------\n");
      printf("person is: \n");
      print_person(cur->person, city_list);
      return;
    }
    prev = cur;
    cur = cur->next;
  }
  printf("Couldn't find it \n");
}

CityList *create_empty_city_list()
{
  CityList *head = malloc(sizeof(CityList));
  head->next = NULL;
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

CityList *add_city(CityList *head, City *new_city)
{
  if (!head->city)
  {
    head->city = copy_city(new_city);
    head->next = NULL;
    return head;
  }
  CityList *cur = head;
  CityList *prev = NULL;
  while (cur)
  {
    if (strcmp(cur->city->name, new_city->name) >= 0)
    {
      CityList *new_node = create_empty_city_list();
      new_node->next = cur;
      if (prev)
      {
        prev->next = new_node;
        new_node->city = copy_city(new_city);
        return head;
      }

      new_node->next = head;
      new_node->city = copy_city(new_city);
      return new_node;
    }

    prev = cur;
    cur = cur->next;
  }
  prev->next = create_empty_city_list();
  prev->next->city = copy_city(new_city);
  return head;
}

City *search_city(CityList *head, char *name)
{
  CityList *cur = head;
  CityList *prev = NULL;

  while (cur->city)
  {
    if (strcmp(cur->city->name, name) == 0)
    {
      return cur->city;
    }
    prev = cur;
    cur = cur->next;
  }
  return NULL;
}

CityList *delete_city(CityList *head, char *name)
{
  CityList *cur = head;
  CityList *prev = NULL;

  while (cur)
  {
    if (strcmp(cur->city->name, name) == 0)
    {
      if (!prev)
      {
        CityList *for_return = head->next;
        free(head);
        return for_return;
      }
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
  while (cur)
  {
    print_city(cur->city);
    cur = cur->next;
  }
}

void get_person(SLList **head)
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