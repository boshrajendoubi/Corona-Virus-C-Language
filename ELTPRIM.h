#ifndef ELTPRIM_H
#define ELTPRIM_H
#include"ELTSDD.h"
ELEMENT elementCreer(void) ;
void elementLire(ELEMENT*);
void elementDetruire (ELEMENT);
void elementAfficher(ELEMENT);
void elementAfficher2(ELEMENT);
void elementAffecter(ELEMENT*, ELEMENT);
void elementCopier(ELEMENT *, ELEMENT) ;
int elementComparer(ELEMENT, ELEMENT);

#endif // ELTPRIM_H_INCLUDED
