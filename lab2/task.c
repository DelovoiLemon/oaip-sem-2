#include <stdio.h>
#include <stdlib.h>

struct Stack {
	double data;
	struct Stack *next;	
};

void push(struct Stack **s, double val)
{
	struct Stack *t = malloc(sizeof(struct Stack));
	t->next = *s;
	t->data = val;
	*s = t;
}

double pop(struct Stack **s, double *val)
{
	struct Stack *t;
	if(*s == NULL) return -1;
	*val = (*s)->data;
	t = *s;
	*s = t->next;
	free(t);
	return 0;
}

void sort_p(struct Stack **s)
{
	double tmp;
	struct Stack *t = NULL, *t1, *r;
	push(s, 0);
	if((*s)->next->next == NULL) return;
	do {
		for(t1 = *s; t1->next->next != t; t1 = t1->next)
			if(t1->next->data > t1->next->next->data) {
				r = t1->next->next;
				t1->next->next = r->next;
				r->next = t1->next;
				t1->next = r;
			}
		t = t1->next;
	} while((*s)->next->next != t);
	pop(s, &tmp);
	
}

void sort_data(struct Stack *s)
{
	struct Stack *t = NULL, *t1; double r;
	do {
		for(t1 = s; t1->next != t; t1 = t1->next)
			if(t1->data > t1->next->data) {
				r = t1->data;
				t1->data = t1->next->data;
				t1->next->data = r;
			}
		t = t1;
	} while(s->next != t);
}

int print_stack(struct Stack *s) {
	int i;
	for(i = 0; s; s = s->next, i++)
		printf("%i: %lf\n", i, s->data);
	puts("\n");
	return i;
}

void del_all(struct Stack **s)
{
	struct Stack *t;
	while(*s != NULL)
	{
		t = *s;
		*s = t->next;
		free(t);
	}
}

double avg_calc(struct Stack *s)
{
	int i; double sum = 0;
	for(i = 0; s; i++, s = s->next)
		sum += s->data;
	return sum / i;
}

void task(struct Stack *s) {
	if(!s) return;

	s->data = avg_calc(s);
}

int main() 
{
	struct Stack *begin = NULL;

	for(int i = 1; i <= 10; i++)
		push(&begin, rand() % 100);
	
	puts("Исходный стек:\n");
	print_stack(begin);
	sort_data(begin);
	puts("Отсортированный стек:\n");
	print_stack(begin);
	del_all(&begin);

	for(int i = 1; i <= 25; i++)
		push(&begin, rand() % 100);


	puts("Исходный стек:\n");
	print_stack(begin);
	sort_p(&begin);
	puts("Отсортированный стек:\n");
	print_stack(begin);

	task(begin);
	puts("Задание:\n");
	print_stack(begin);

	del_all(&begin);
}
