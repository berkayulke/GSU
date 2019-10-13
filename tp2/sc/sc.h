#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __SC_H_
#define __SC_H_

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

typedef struct PersonList
{
  Person *person;
  struct PersonList *next;
} PersonList;

typedef struct CityList
{
  City *city;
  struct CityList *next;
} CityList;

//For person list
PersonList *create_empty_person_list();
Person *create_person(char *name, char *surname, char *city, char *homeNumber);
Person *copy_person(Person *source);
PersonList *add_person(PersonList *head, Person *new_pers);
void search_person(PersonList *head, char *surname, CityList *city_list);
PersonList *delete_person(PersonList *head, char *surname);
void print_person(Person *person, CityList *city_list);
void print_person_list(PersonList *head, CityList *city_list);
PersonList *get_last_person(PersonList *head);
PersonList *add_person_before(PersonList *head, Person *new_pers);

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
void get_person(PersonList **head);
void get_city(CityList **head);

#endif