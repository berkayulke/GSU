#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __DL_H_
#define __DL_H_

typedef struct city
{
  char *name;
  int code;
} City;

typedef struct person
{
  char *name;
  char *surname;
  char *city;
  char *homeNumber;
} Person;

typedef struct SLList
{
  Person *person;
  struct SLList *prev;
  struct SLList *next;
} SLList;

typedef struct CityList
{
  City *city;
  struct CityList *prev;
  struct CityList *next;
} CityList;

//For person list
SLList *create_empty_person_list();
Person *create_person(char *name, char *surname, char *city, char *homeNumber);
Person *copy_person(Person *source);
SLList *add_person(SLList *head, Person *new_pers);
void search_person(SLList *head, char *surname, CityList *city_list);
SLList *delete_person(SLList *head, char *surname);
void print_person(Person *person, CityList *city_list);
void print_person_list(SLList *head, CityList *city_list);

//For city list
CityList *create_empty_city_list();
City *create_city(char *name, int code);
City *copy_city(City *source);
CityList *add_city(CityList *head, City *new_city);
City *search_city(CityList *head, char *name);
CityList *delete_city(CityList *head, char *name);
void print_city(City *city);
void print_city_list(CityList *head);

//For menu
void get_person(SLList **head);
void get_city(CityList **head);

#endif