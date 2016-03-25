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

#include <stdlib.h>
#include "dlmalloc.h" /* (must be before stdio/string) */
#include <stdio.h>
#include <string.h>
#include "mem.h"

#ifdef MAXALLOCATED
int maxallocated = 0;

void updatemaxallocated()
{
  int t = mem_allocated();
  if (t>maxallocated)
    maxallocated = t;
}
#endif

int memlimit = 0;

void mem_error()
{
  if (memlimit)
    printf("\n\n-----\n"
           "Interactive Demo memory limit exceeded, execution stopped.\n");
  else
    printf("\n*** out of memory, execution aborted ***\n");
  exit(-1);
}

void *mem_alloc(size_t s)
{
#ifdef USE_DLMALLOC
  void *x = dlmalloc(s);
#else
  void *x = malloc(s);
#endif
  if (!x)
    mem_error();
#ifdef MAXALLOCATED
  updatemaxallocated();
#endif
  return x;
}

void mem_free(void *x)
{
#ifdef USE_DLMALLOC
  dlfree(x);
#else
  free(x);
#endif
}

void *mem_resize(void *x, size_t s)
{
#ifdef USE_DLMALLOC
  void *y = dlrealloc(x, s);
#else
  void *y = realloc(x, s);
#endif
  if (!y)
    mem_error();
#ifdef MAXALLOCATED
  updatemaxallocated();
#endif
  return y;
}

void mem_copy(void *dst, void *src, size_t s)
{
  memcpy(dst, src, s);
}

void mem_zero(void *x, size_t s)
{
  memset(x, 0, s);
}

unsigned int mem_allocated()
{
#ifdef USE_DLMALLOC
  struct mallinfo m = dlmallinfo();
  return (unsigned) m.uordblks+m.hblkhd;
#else
  return -1;
#endif
}
