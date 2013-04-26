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

#ifndef _GNUC_H
#define _GNUC_H

#if (! defined __GNUC__) || (__GNUC__ < 2) || (__GNUC__ == 2 && __GNUC_MINOR__ < 7)
# define __attribute__(x)
# define __inline__
#endif

#define GNUC_NORETURN __attribute__ ((__noreturn__))
#define GNUC_CONST __attribute__ ((__const__))
#define GNUC_FORMAT(a,s,f) __attribute__ ((__format__ (a, s, f)))
#define GNUC_INLINE __inline__

#if (__GNUC__ > 2) || (__GNUC == 2 && __GNUC_MINOR >= 96)
# define GNUC_PURE __attribute__ ((__pure__))
# define GNUC_MALLOC __attribute__ ((__malloc__))
#else
# define GNUC_PURE
# define GNUC_MALLOC
#endif

/*
   GNUC_NORETURN:  function never returns
   GNUC_PURE:      never writes to heap
   GNUC_CONST:     never accesses heap 
   GNUC_FORMAT:    printf-like argument check
   GNUC_MALLOC:    result is a fresh pointer
   GNUC_INLINE:    inline function
 */

#endif
