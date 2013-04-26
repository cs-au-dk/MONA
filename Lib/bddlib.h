/* bddlib.h - BDD definitions for external automaton library */
 
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

#ifndef __BDDLIB_H
#define __BDDLIB_H

typedef unsigned mNode; /* index into BDD array */
typedef char *mA; /* alphabet element, 0/1 array */

typedef struct mBdd {
  int idx;  /* variable index, -1 iff leaf */
  mNode lo; /* low pointer, if idx==-1 then lo contains state number */
  mNode hi; /* high pointer */
} mBdd;

#endif
