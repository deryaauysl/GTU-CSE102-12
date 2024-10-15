
#ifndef CUSTOMDICT_H
#define CUSTOMDICT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union
{
    int i;
    float f;
    double d;
    char c;
} Value;

typedef struct
{
    char *key;
    char *dtype;
    Value *value;
} Item;

typedef struct
{
    Item *items;
    int capacity;
    int size;

} CustomDict;

CustomDict *create_dict();
void add_item(CustomDict *dict, char *key, Value *value, char *dtype);
void delete_item(CustomDict *dict, char *key);
void set_value(CustomDict *dict, char *key, Value *value, char *dtype);
Value *search_item(CustomDict *dict, char *key);
void sort_dict(CustomDict *dict);
void print_dict(CustomDict *dict);
void free_dict(CustomDict *dict);
int read_csv(CustomDict *dict, const char *filename);

CustomDict *create_dict()
{
    CustomDict *dict = (CustomDict *)malloc(sizeof(CustomDict));
    dict->items = NULL;
    dict->capacity = 0;
    dict->size = 0;
    return dict;
}

void add_item(CustomDict *dict, char *key, Value *value, char *dtype)
{
    if (dict->size == dict->capacity)
    {
        dict->capacity = (dict->capacity == 0) ? 1 : dict->capacity * 2;
        dict->items = (Item *)realloc(dict->items, dict->capacity * sizeof(Item));
    }
    int i = 0;
    for (i = 0; i < dict->size; i++)
    {
        if (strcmp(dict->items[i].key, key) == 0)
        {
            free(dict->items[i].value);
            dict->items[i].value = (Value *)malloc(sizeof(Value));
            *(dict->items[i].value) = *value;
            free(dict->items[i].dtype);
            dict->items[i].dtype = strdup(dtype);
            return;
        }
    }

    dict->items[dict->size].key = strdup(key);
    dict->items[dict->size].value = (Value *)malloc(sizeof(Value));
    *(dict->items[dict->size].value) = *value;
    dict->items[dict->size].dtype = strdup(dtype);
    dict->size++;
}

void delete_item(CustomDict *dict, char *key)
{
    int i = 0;
    for (i = 0; i < dict->size; i++)
    {
        if (strcmp(dict->items[i].key, key) == 0)
        {
            free(dict->items[i].key);
            free(dict->items[i].value);
            free(dict->items[i].dtype);
            int j = 0;
            for (j = i; j < dict->size - 1; j++)
            {
                dict->items[j] = dict->items[j + 1];
            }
            dict->size--;
            return;
        }
    }
}

void set_value(CustomDict *dict, char *key, Value *value, char *dtype)
{

    int i = 0;
    for (i = 0; i < dict->size; i++)
    {
        if (strcmp(dict->items[i].key, key) == 0)
        {
            free(dict->items[i].value);
            dict->items[i].value = (Value *)malloc(sizeof(Value));
            *(dict->items[i].value) = *value;
            free(dict->items[i].dtype);
            dict->items[i].dtype = strdup(dtype);
            return;
        }
    }
}

Value *search_item(CustomDict *dict, char *key)
{
    int i = 0;
    for (i = 0; i < dict->size; i++)
    {
        if (strcmp(dict->items[i].key, key) == 0)
        {
            return dict->items[i].value;
        }
    }
    return NULL;
}
void sort_dict(CustomDict *dict)
{
    int i = 0;
    for (i = 0; i < dict->size - 1; i++)
    {
        int j = 0;
        for (j = 0; j < dict->size - i - 1; j++)
        {
            if (strcmp(dict->items[j].key, dict->items[j + 1].key) > 0)
            {
                Item temp = dict->items[j];
                dict->items[j] = dict->items[j + 1];
                dict->items[j + 1] = temp;
            }
        }
    }
}

void print_dict(CustomDict *dict)
{
    int i = 0;
    for (i = 0; i < dict->size; i++)
    {
        printf("Key: %s\n", dict->items[i].key);
        printf("Value: ");
        if (strcmp(dict->items[i].dtype, "int") == 0)
        {
            printf("%d ", dict->items[i].value->i);
        }
        else if (strcmp(dict->items[i].dtype, "float") == 0)
        {
            printf("%f ", dict->items[i].value->f);
        }
        else if (strcmp(dict->items[i].dtype, "double") == 0)
        {
            printf("%f ", dict->items[i].value->d);
        }
        else if (strcmp(dict->items[i].dtype, "char") == 0)
        {
            printf("%c ", dict->items[i].value->c);
        }
        printf("\n");
    }
}

void free_dict(CustomDict *dict)
{
    int i = 0;
    for (int i = 0; i < dict->size; i++)
    {
        free(dict->items[i].key);
        free(dict->items[i].value);
        free(dict->items[i].dtype);
    }
    free(dict->items);
    free(dict);
}

int read_csv(CustomDict *dict, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        return 0;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        char *type = strtok(line, ",");
        char *key = strtok(NULL, ",");
        Value value;

        char *token;
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            if (strcmp(type, "int") == 0)
            {
                value.i = atoi(token);
            }
            else if (strcmp(type, "float") == 0)
            {
                value.f = atof(token);
            }

            else if (strcmp(type, "double") == 0)
            {
                value.d = atof(token);
            }
            else if (strcmp(type, "char") == 0)
            {
                value.c = token[0];
            }
            add_item(dict, key, &value, type);
        }
    }
    fclose(file);
    return 1;
}

#endif