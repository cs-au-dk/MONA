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

#include <stdio.h>
#include <stdlib.h>
#include "dfa.h"
#include "../BDD/bdd_external.h"
#include "../Mem/mem.h"

/* EXPORT */

int dfaExport(DFA *a, char *filename, int num, char *vars[], char orders[])
{
  Table *table = tableInit(); 
  int i;
  FILE *file;

  if (filename) {
    if ((file = fopen(filename, "w")) == 0) 
      return 0;
  }
  else
    file = stdout;
  
  /* remove all marks in a->bddm */
  bdd_prepare_apply1(a->bddm); 
  
  /* build table of tuples (idx,lo,hi) */
  for (i = 0; i < a->ns; i++)  
    export(a->bddm, a->q[i], table);

  /* renumber lo/hi pointers to new table ordering */
  for (i = 0; i < table->noelems; i++) {
    if (table->elms[i].idx != -1) {
      table->elms[i].lo = bdd_mark(a->bddm, table->elms[i].lo) - 1;
      table->elms[i].hi = bdd_mark(a->bddm, table->elms[i].hi) - 1;
    }
  }

  /* write to file */
  fprintf(file,
          "MONA DFA\n"
	  "number of variables: %u\n"
	  "variables:", num);
  for (i = 0; i < num; i++)
    fprintf(file, " %s", vars[i]);
  fprintf(file, "\n"
	  "orders:");
  for (i = 0; i < num; i++)
    fprintf(file, " %u", (unsigned) orders[i]);
  fprintf(file, "\n"
          "states: %u\n"
          "initial: %u\n"
          "bdd nodes: %u\n"
          "final:",
	  a->ns, a->s, table->noelems); 
  for (i = 0; i < a->ns; i++)
    fprintf(file, " %d", a->f[i]);
  fprintf(file, "\nbehaviour:");
  for (i = 0; i < a->ns; i++)
    fprintf(file, " %u", bdd_mark(a->bddm, a->q[i]) - 1);
  fprintf(file, "\nbdd:\n");
  for (i = 0; i < table->noelems; i++) 
    fprintf(file, " %i %u %u\n", 
	    table->elms[i].idx, table->elms[i].lo, table->elms[i].hi);
  fprintf(file, "end\n");

  tableFree(table);
  if (filename)
    fclose(file);
  return 1;
}

/* IMPORT */

extern BddNode *table;
extern bdd_manager *import_bddm;

DFA *dfaImport(char* filename, char ***vars, int **orders)
{
  unsigned int i, numvars, bdd_nodes, ns, s;
  FILE *file;
  DFA *a;
  char ts[100];
  int ti;

  /* Read file */
  if ((file = fopen(filename, "r")) == 0) 
    return 0;

  if (fscanf(file,
	 "MONA DFA\n"
	 "number of variables: %u\n"
         "variables: ", &numvars) != 1) {
    fclose(file);
    return 0;
  }
  if (vars) {
    *vars = (char **) mem_alloc(sizeof(char *) * (numvars + 1));
    (*vars)[numvars] = 0;
    for (i = 0; i < numvars; i++) {
      (*vars)[i] = (char *) mem_alloc(100);
      if (fscanf(file, " %s ", (*vars)[i]) != 1) {
	fclose(file);
	return 0;
      }
    }
  }
  else {
    for (i = 0; i < numvars; i++)
      if (fscanf(file, " %s ", ts) != 1) {
	fclose(file);
        return 0;
      }
  }
  if (fscanf(file, "orders: ") != 0) {
    fclose(file);
    return 0;
  }
  if (orders) {
    *orders = (int *) mem_alloc(sizeof(int) * numvars);
    for (i = 0; i < numvars; i++)
      if (fscanf(file, " %d ", &((*orders)[i])) != 1) {
	fclose(file);
	return 0;
      }
  }
  else
    for (i = 0; i < numvars; i++)
      if (fscanf(file, " %d ", &ti) != 1) {
	fclose(file);
	return 0;
      }	
  if (fscanf(file,
             "states: %u\n"
             "initial: %u\n"
             "bdd nodes: %u\n"
             "final:", 
             &ns, &s, &bdd_nodes) != 3) {
    fclose(file);
    return 0;
  }
  a = dfaMake(ns);
  a->s = s;

  for (i = 0; i<a->ns; i++)
    if (fscanf(file, " %d", &a->f[i]) != 1) {
      fclose(file);
      return 0;
    }

  if (fscanf(file, "\nbehaviour:") != 0) {
    fclose(file);
    return 0;
  }
  for (i = 0; i < a->ns; i++)
    if (fscanf(file, " %u", &a->q[i]) != 1) {
      fclose(file);
      return 0;
    }

  if (fscanf(file, "\nbdd:\n") != 0) {
    fclose(file);
    return 0;
  }
  table = (BddNode *) mem_alloc(sizeof(BddNode)*bdd_nodes);
  
  for (i = 0; i < bdd_nodes; i++) {
    table[i].p = -1;
    if (fscanf(file, "%i %u %u\n", 
           &table[i].idx,
           &table[i].lo,
	   &table[i].hi) != 3) {
      fclose(file);
      return 0;
    }
  }
  
  if (fgetc(file) != 'e' ||
      fgetc(file) != 'n' ||
      fgetc(file) != 'd') {
    fclose(file);
    return 0;
  }
  fclose(file);

  /* fill bdd-manager */
  import_bddm = a->bddm;
  for (i = 0; i < a->ns; i++) 
    a->q[i] = make_node(a->q[i]);

  mem_free(table);
  return a;
}
