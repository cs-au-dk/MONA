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

#ifndef __SIGNATURE_H
#define __SIGNATURE_H

#include "ident.h"

class Signature {
public:
  Signature();
  Signature(IdentList &idents);
  ~Signature();

  void make(IdentList &idents);
  void dump(char *to);
  int operator==(const Signature &);

  unsigned  size;
  int      *sign;
  int       hashvalue;
};

#endif
