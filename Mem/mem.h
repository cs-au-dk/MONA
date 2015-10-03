/*
 * MONA
 * Copyright (C) 1997-2013 Aarhus University.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the  Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA 02110-1335,
 * USA.
 */

#ifndef __MEM_H
#define __MEM_H

#include <stdlib.h>
#include "gnuc.h"

extern int memlimit;

#ifdef MAXALLOCATED
extern int maxallocated;
#endif

void mem_error();
void *mem_alloc(size_t);
void mem_free(void *);
void *mem_resize(void *, size_t);
void mem_copy(void *, void *, size_t);
void mem_zero(void *, size_t);
unsigned int mem_allocated();

#endif
