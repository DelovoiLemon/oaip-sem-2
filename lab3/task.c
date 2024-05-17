#include <stdio.h>
#include <stdlib.h>

typedef struct List {
	double data;
	struct List *next, *prev;	
} list;

list *create_list(double data)
{
    list *t = malloc(sizeof(list));
    t->data = data;
    t->prev = t->next = NULL;
    return t;
}

void init(list **b, list **e, double val)
{
    *b = *e = create_list(val);
}


// derection (0 - start, anything - end);
void add(int direction, list **b, list **e, double val)
{
    list *t = malloc(sizeof(list));
    t->data = val;
    if(direction) { // start
        t->prev = NULL;
        t->next = *b;
        (*b)->prev = t;
        *b = t;
    } else { // end
        t->next = NULL;
        t->prev = *e;
        (*e)->next = t;
        (*e) = t;
    }
}

int del_all(list **b)
{
    int i; list *t;
    for(i = 0; *b; i++)
    {
        t = *b;
        *b = t->next;
        free(t);
    }
    return i;
}


void swap_data(list *p1, list *p2) {
    double tmp;
    if(!p1 || !p2) return;
    tmp = p1->data;
    p1->data = p2->data;
    p2->data = tmp;
}

void sort_data(list *s)
{
	list *t = NULL, *t1; double r;
	do {
		for(t1 = s; t1->next != t; t1 = t1->next)
			if(t1->data < t1->next->data) {
				swap_data(t1, t1->next);
			}
		t = t1;
	} while(s->next != t);
}

int print_list(int direction, list *b, list *e) {
	int i;
    if(direction) for(i = 0; b; b = b->next, i++)
            printf("%i: %lf\n", i, b->data);
    else for(i = 0; e; e = e->prev, i++)
            printf("%i: %lf\n", i, e->data);
    
 	return i;
}

double avg_calc(list *s)
{
	int i; double sum = 0;
	for(i = 0; s; i++, s = s->next)
		sum += s->data;
	return sum / i;
}

void task(list *b, list *e) {
	if(!b) return;
	e->data = avg_calc(b);
}

int main() 
{
	list *begin = NULL, *end = NULL;

    init(&begin, &end, rand() % 1000);

	for(int i = 0; i < 9; i++)
		add(0, &begin, &end, rand() % 100);
	
	puts("Исходный стек:\n");
	print_list(0, begin, end);
	sort_data(begin);
	puts("Отсортированный стек:\n");
	print_list(0, begin, end);

	task(begin, end);
	puts("Задание:\n");
	print_list(0, begin, end);

	del_all(&begin);
}