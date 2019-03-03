//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     David Sedlák <xsedla1d@stud.fit.vutbr.cz>
// $Date:       $2019-03-02
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author David Sedlák
 *
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    first = NULL;
}

PriorityQueue::~PriorityQueue()
{
    Element_t *iter = first;

    while (iter) {
        iter = first->pNext;
        free(first);
        first = iter;
    }

    iter = NULL;
}

void PriorityQueue::Insert(int value)
{
    Element_t *new_elem = (Element_t *)malloc(sizeof(*new_elem));
    Element_t *iter = first;
    new_elem->value = value;
    new_elem->pPrev = NULL;
    new_elem->pNext = NULL;

    if (first == NULL) {
        first = new_elem;
    } else {
        if (new_elem->value <= first->value) {
            new_elem->pNext = first;
            new_elem->pPrev = NULL;
            first->pPrev = new_elem;
            first = new_elem;
            return;
        }
        while (iter->pNext) {
            if (iter->pNext->value >= new_elem->value) {
                new_elem->pNext = iter->pNext;
                new_elem->pPrev = iter;
                iter->pNext->pPrev = new_elem;
                iter->pNext = new_elem;
                return;
            }
            iter = iter->pNext;
        }
        new_elem->pNext = NULL;
        new_elem->pPrev = iter;
        iter->pNext = new_elem;
    }
}

bool PriorityQueue::Remove(int value)
{
    Element_t *iter = first;
    Element_t *to_delete;

    if (!iter) {
        return false;
    }

    if (first->value == value) {
        to_delete = first;
        first = first->pNext;
        free(to_delete);
        return true;
    }

    while (iter) {
        if (iter->value == value) {
            if (iter->pPrev) {
                iter->pPrev->pNext = iter->pNext;
            }
            if (iter->pNext) {
                iter->pNext->pPrev = iter->pPrev;
            }
            free(iter);
            return true;
        }
        iter = iter->pNext;
    }

    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    Element_t *iter = first;

    while (iter) {
        if (iter->value == value) {
            return iter;
        }
        iter = iter->pNext;
    }

    return NULL;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return first;
}

/*** Konec souboru tdd_code.cpp ***/
