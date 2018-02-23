/* * Copyright (C) 2017 Barcelona Supercomputing Center
 *                    Centro Nacional de Supercomputacion
 *
 * This file is part of the Data Scheduler, a daemon for tracking and managing
 * requests for asynchronous data transfer in a hierarchical storage environment.
 *
 * See AUTHORS file in the top level directory for information
 * regarding developers and contributors.
 *
 * The Data Scheduler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Data Scheduler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Data Scheduler.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __XSTRING_H__
#define __XSTRING_H__

#include <sys/types.h>
#include <stdbool.h>

#pragma GCC visibility push(hidden)

// maximum string length supported for security reasons (including '\0')
// any input strings larger than MAX_STRING_LENGTH will be truncated
// (if this becomes a problem at some point, just enlarge it)
#define XMAX_STRING_LENGTH   4096
#define XMIN(a, b) \
    (a) < (b) ? (a) : (b)

char* xstrdup(const char* str);
int xstrcnmp(const char* s1, const char* s2);

#pragma GCC visibility pop

#endif /* __XSTRING_H__ */