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
#include <stdio.h>
#include <string.h>
#include "../Mem/mem.h"
#include "gta.h"

#define MAX_EXCEPTION 50
#define MAX_VARIABLES 10
/* #warning INTERNAL LIMITS */

typedef struct {
  unsigned value;
  char path[MAX_VARIABLES+1];
} Path;

static GTA *gta;
static unsigned numExceptions, nextException, exp;
static Path exception[MAX_EXCEPTION];
static State left, right; /* current left and right state */
static State defState;
static SsId s; /* current state space */
static unsigned sortedIndex[MAX_VARIABLES];
static int *offs;
static unsigned numOffs;
static char sortedPath[MAX_VARIABLES]; /* current exception path, sorted according to offsets */
static bdd_ptr bddPath[MAX_EXCEPTION];
static bdd_ptr def;

/*  USAGE:
 *
 *  gtaSetup(number of states in root state space)
 *  for each state space s do
 *    gtaSetupDelta(s, size of left successor, size of right successor,
 *                  offset array, size of offset array)
 *    for each pair (l,r) do
 *      gtaAllocExceptions(l, r, number of exceptions)
 *      gtaStoreException(state, path) [for each exception]
 *      gtaStoreDefault(state)
 *    gtaBuildDelta(initial state)
 *  gtaBuild(final state array) 
 */

/* auxiliary functions */

int offsCmp(const void *i1, const void *i2)
{
  unsigned o1 = offs[*((unsigned *) i1)], o2 = offs[*((unsigned *) i2)];

  if (o1 < o2)
    return -1;
  if (o1 > o2)
    return 1;
  return 0;
}

unsigned fn_unite(unsigned p, unsigned q)
{
  if (p == q || q == defState)
    return p;
  invariant(p == defState);
  return q;
}

/* make path ..... */
bdd_ptr makePath(bdd_manager *bddm, unsigned leafValue)
{
  int n;
  bdd_ptr p;
  
  /* insert leaf node */
  p = bdd_find_leaf_hashed_add_root(bddm, leafValue);

  /* build path bottom-up */
  for (n = numOffs - 1; n >= 0; n--)
    switch (sortedPath[n]) {
    case '0':
      p = bdd_find_node_hashed_add_root(bddm, p, def, 
					offs[sortedIndex[n]]);
      break;
    case '1':
      p = bdd_find_node_hashed_add_root(bddm, def, p, 
					offs[sortedIndex[n]]);
      break;
    case 'X': /* do nothing */
      break;
    }
  return p;
}

/* unite bddPaths */
bdd_ptr unitePaths(bdd_manager *bddm)
{
  int n;
  bdd_ptr p = bddPath[0];

  bdd_make_cache(bddm, 8, 4);
  for (n = 1; n < numExceptions; n++)
    p = bdd_apply2_hashed(bddm, p, bddm, bddPath[n],
			  bddm, &fn_unite);
  bdd_kill_cache(bddm);

  return p;
}

/* main functions */

/* prepare construction of a new GTA */
void gtaSetup(unsigned rootsize) 
{
  gta = gtaMake();
  gta->ss[0].size = rootsize;
}

void gtaSetupDelta(SsId d, unsigned lsize, unsigned rsize, 
		   int *offsets, unsigned numOffsets)
{
  int n;

  s = d;
  gta->ss[guide.muLeft[s]].size = lsize;
  gta->ss[guide.muRight[s]].size = rsize;

  /* prepare behaviour matrix and BDD manager */
  gta->ss[s].ls = lsize;
  gta->ss[s].rs = rsize;
  gta->ss[s].behaviour = (bdd_handle *) mem_alloc(sizeof(bdd_handle)*
						  gta->ss[s].ls*
						  gta->ss[s].rs);
  gta->ss[s].bddm = bdd_new_manager(8, 4);

  /* sort offsets */
  numOffs = numOffsets;
  offs = offsets;
  for (n = 0; n < numOffs; n++)
    sortedIndex[n] = n;
  qsort(sortedIndex, numOffs, sizeof(int), offsCmp);
}

/* prepare some exceptions from the (l,r) state pair 
   to the default result state */
void gtaAllocExceptions(SsId l, SsId r, unsigned n) 
{
  invariant(n <= MAX_EXCEPTION);
  numExceptions = n;
  nextException = 0;
  left = l;
  right = r;
}

/* store an exception to the default rule */
void gtaStoreException(unsigned value, char *path) 
{
  exception[nextException].value = value;
  invariant(strlen(path) <= MAX_VARIABLES);
  strcpy(exception[nextException++].path, path);
}

/* set default state and make BDD for current state pair */
void gtaStoreDefault(unsigned p) 
{
  bdd_ptr united;
  int n;
  bdd_manager *tmpBddm;

  invariant(numExceptions == nextException);
  defState = p;

  tmpBddm = bdd_new_manager(100, 10); /* large enough to avoid rehashing??? */
  /* COULD AN ASSERTION CHECK THAT REHASHING DOES NOT OCCUR???????? */

  /* insert default state as leaf */
  def = bdd_find_leaf_hashed_add_root(tmpBddm, defState);

  /* insert paths for exceptions */
  for (exp = 0; exp < numExceptions; exp++) {
    for (n = 0; n < numOffs; n++)
      sortedPath[n] = exception[exp].path[sortedIndex[n]];

    bddPath[exp] = makePath(tmpBddm, exception[exp].value);
  }

  /* unite path roots */
  if (numExceptions == 0)
    united = def;
  else if (numExceptions == 1)
    united = bddPath[0];
  else
    united = unitePaths(tmpBddm);

  /* insert into result BDD manager */
  bdd_prepare_apply1(tmpBddm);
  bdd_apply1(tmpBddm, united, gta->ss[s].bddm, &fn_identity);
  bdd_kill_manager(tmpBddm);
  
  /* set behaviour entry */
  BEH(gta->ss[s], left, right) = BDD_LAST_HANDLE(gta->ss[s].bddm);
}

void gtaBuildDelta(State initial)
{
  gta->ss[s].initial = initial; /* this could be moved to gtaSetupDelta!! */
}

GTA *gtaBuild(char *final)
{
  int n;

  invariant(strlen(final) == gta->ss[0].size);

  /* set final status */
  gta->final = (int *) mem_alloc(sizeof(int)*gta->ss[0].size);
  for (n = 0; n < gta->ss[0].size; n++)
    gta->final[n] = (final[n] == '-') ? -1 : (final[n] == '+' ? 1 : 0);

  return gtaReachable(gta);
}

