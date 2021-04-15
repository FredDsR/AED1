#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int BOOL;

/* program to illustrate insertion into, and deletion from, a linked list 
 using the "triple ref" technique which was rediscovered in Algol 68 some 40 
years ago having (allegedly) been known to assembler programmers since the 
dawn of time .... 
 
Note that "tracer"  has a content type of "ref ref THING" in Algol 68, or
`THING ** ' in C, which means that the memory location of "tracer"  itself
is one `ref' higher i.e. "ref ref ref THING" in A68, or "THING ***" in C.  
It's therefore easy to appreciate why this techniques became known as `tripleref'

As its name implies, `tracer' is used to locate a place in the list. And, 
by using casts, to singly or doubly dereference it, one can inspect the 
contents of either the current element or the next element along.

The nice thing is that although the InsertThing and RemoveThing routines using 
this technique will generally be handling something in the middle of a list 
but the routines are also robust against the following special cases;
 
 1) inserting/deleting to/from a null list
 2) inserting/deleting to/from a single-member list
 3) inserting/deleting at the end of a list
 4) inserting/deleting at the front of a list 

All of the above take place with no need for additional `special case' coding. The timely
detection of NULL and the updating (if needed) of the pointer to the start of the list happen
quite automatically.

Use is made, in the routines below,  of the commonplace C shorthand of `while (*tracer) ' rather than 
the more general `while (*tracer != NULL) '. But do be clear that this short-cut relies on 
boolean values being represented as 0 and 1 and the NULL pointer as 0.   It's possible to envisage 
exotic C implementations where this might not be the case.

NOTE CAREFULLY: this is a tutorial example. The insertion and deletion
routines have been deliberately constructed so as to deliver `void'. This is to
illustrate that they do not need to deliver a formal THING * result for the purpose of 
updating the list head (say).

Instead, the content of the incoming formal parameter called `head'
points at the global variable `start' in these examples.  The effect is that the content of
 `start' gets updated, automatically and correctly, in all
special cases where "insert at front of list" takes place.  Your reaction
to this behaviour may vary from "That's cool!" to "That's appalling!".

So, it is NOT necessary for the routines to deliver back a traditional
THING* pointer to the new list head -- to enable updating to be done
manually in a separate operation.  However it is easy to alter the
InsertThing and RemoveThing routines to deliver back just such a THING*
result, if this is required for some reason. The `return' statements in these procedures
would then need to be replaced by `return *head' */


typedef struct _thing 
{ 
	char *item;
	struct _thing *next;
} THING;

THING *start = NULL;

// create new list element of type THING from the supplied text string
THING *NewElement(char *text)
{
        THING *newp;
        newp = (THING *) malloc (sizeof(THING));
        newp -> item = (char *)malloc(strlen(text) + 1);
        strcpy(newp -> item, text);
        newp -> next = NULL;
        return newp;
}  



//Insert a new element into a singly-linked list
// Note -- duplicate entries are not checked for 
void InsertThing(THING **head, THING *newp)
{
	THING **tracer = head;

	while((*tracer) && 
		  strcmp((*tracer)->item, newp -> item) < 1)
	{
		tracer = &(*tracer)->next;
	}

	newp -> next = *tracer;
	*tracer = newp;
}

// Delete first element on list whose item field matches the given text
// NOTE!! delete requests for elements not in the list are silently ignored :-)
void RemoveThing(THING **head, char *text)
{
	BOOL present = FALSE;
	THING *old;
	THING **tracer = head;
	
	while((*tracer) && !(present = (strcmp(text,(*tracer)->item) == 0 )  ))
		tracer = &(*tracer)->next;

	if(present)
	{
		old = *tracer;
		*tracer = (*tracer)->next;
		free(old -> item); // free off space used by text string
		free(old); // free up remainder of list element 
	}
}

void PrintList(THING **head)
{
	THING **tracer = head;
	while (*tracer) {
		printf("%s \n",(*tracer)->item);
		tracer = &(*tracer)->next;
	}
}


int main(int argc, char **argv)
{
        InsertThing(&start, NewElement("chips"));
        InsertThing(&start, NewElement("wine"));
        InsertThing(&start, NewElement("burgers"));
        InsertThing(&start, NewElement("beer"));
        InsertThing(&start, NewElement("pizza"));
        InsertThing(&start, NewElement("zucchini"));
        InsertThing(&start, NewElement("burgers"));
        InsertThing(&start, NewElement("slaw"));
        printf("\nINITIAL LIST\n");
        PrintList (&start);
        RemoveThing(&start, "pizza");
        RemoveThing(&start, "zucchini");
        RemoveThing(&start, "burgers");
        printf("\nALTERED LIST\n");
        PrintList(&start);
                
}                  
