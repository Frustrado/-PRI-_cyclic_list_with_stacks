#ifndef HEADER_H
#define HEADER_H
#define MAX_NAME 100
typedef struct CakesStackElement
{
	time_t created;
	struct CakesStackElement* next;
} CakesStackElement;

typedef struct CakesStack
{
	char name[MAX_NAME];
	int count;
	struct CakesStackElement* topOfStack;
	struct CakesStack* next;
} CakesStack;

CakesStack* head;
void addToStack(CakesStack* stack);
void removeFromStack(CakesStack* stack);
void refill(CakesStack* iter);
void create(char* name);
void eat(char* name, int count);
void print(int val);
void clear();
void save(char* name);
void read(char* name);


#endif
