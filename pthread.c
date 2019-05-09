#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define BUFFER_SIZE 10

typedef struct {
  char type; // 1 for Mec , 2 for BMW
  int amount; // number cars
  char unit; // 0 for USD, 1 for Euro
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) {
  while ((first + 1) % BUFFER_SIZE == last) {}
  memcpy(&buffer[first], i, sizeof(item));
  first = (first + 1) % BUFFER_SIZE;
}

item *consume() {
  item *i = malloc(sizeof(item));
  while (first == last) {}
  memcpy(i, &buffer[last], sizeof(item));
  last = (last + 1) % BUFFER_SIZE;
  return i;
}

item* initItem(char type, int amount, char unit){
  item* i = malloc(sizeof(item));
  i->type = type;
  i->amount = amount;
  i->unit = unit;
  return i;
}

void *producer(void *para) {
	item *order1=initItem('1',2,'1');
  item *order2=initItem('1',5,'0');
  item *order3=initItem('2',10,'1');
	   produce(order1);
	   produce(order2);
     produce(order3);
}

void display(item* i) {
	printf("Type: %c Amount(s): %d Unit: %c\n",i->type,i->amount,i->unit);
}

void *consumer(void *para) {
	   display(consume());
     display(consume());
}

int main() {
	pthread_t tid1,tid2;
	pthread_create(&tid1, NULL, producer, NULL);
	pthread_join(tid1, NULL);
 	pthread_create(&tid2, NULL, consumer, NULL);
	pthread_join(tid2, NULL);
        printf("After produce: First: %d Last %d \n", first, last);
        consume();
        printf("After consume: First: %d Last %d \n", first, last);
	return 0;
}
