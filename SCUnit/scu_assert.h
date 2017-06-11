/*
 *  SCUnit - A Simple C Unit testing framework
 * 
 *  Copyright 2017 Remco van Maanen
 *
 *  This file is part of the SCUnit framework
 * 
 *  SCUnit is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SCUnit is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. (see file COPYING)
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SCU_ASSERT_H
#define SCU_ASSERT_H

#include "scu_types.h"
#include "scu_errors.h"

#define SCU_ASSERT(EQUATION, VALUE) SCU_assert(__LINE__, (EQUATION), #EQUATION, (unsigned long)(VALUE))

extern SCU_error SCU_assert(int lineNo, SCU_bool assertion, const char *pMessage, unsigned long realValue);

#endif