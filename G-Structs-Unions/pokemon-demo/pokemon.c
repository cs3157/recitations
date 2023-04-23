#include "stdio.h"

struct Pokemon
{
        void (*speak)();
        int level;
};

void pikaspeak()
{
        printf("PIKA PIKA");
}

void squirtlespeak()
{
        printf("SQUUIIIRTLE!");
}

void jaespeak()
{
        printf("jae jae!");
}

void yell(struct Pokemon p)
{
        for(int i = 0; i<p.level; i++)
        {
                p.speak();
        }
}

void levelup(struct Pokemon *p)
{
    p->level++;
}


int main()
{
       struct Pokemon parray[] = {
               {&jaespeak, 1},
               {&squirtlespeak, 10},
               {&pikaspeak, 5}
       };
       for(int i = 0; i < sizeof(parray)/sizeof(struct Pokemon); i++)
       {
                yell(parray[i]);
       }
}
