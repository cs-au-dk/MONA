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
#include "offsets.h"

#include <time.h>
/*#warning USING RANDOM ORDERING*/

void
Offsets::insert()
{
  offsetMap.push_back(offsetMap.size());
  max_offset = offsetMap.size();
}

void
Offsets::reorder()
{
  ////// reorder offsets using BDD heuristics ///////

  /*
#warning USING RANDOM ORDERING
  ///////////// test /////////
  
  srandom(time(0));
  for (unsigned i=0; i<offsetMap.size(); i++) {
    unsigned j = ((unsigned) random()) % offsetMap.size();
    unsigned t = offsetMap.get(j);
    offsetMap.set(j, offsetMap.get(i));
    offsetMap.set(i, t);
  }
  ////////////////////////////
  */
  max_offset = offsetMap.size();
}
