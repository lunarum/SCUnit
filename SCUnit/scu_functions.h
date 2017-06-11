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

#ifndef SCU_FUNCTIONS_H
#define SCU_FUNCTIONS_H

extern SCU_TestSuite *SCU_TestSuite_create(const char *pName, SCU_SetUpFunc fpSetUp, SCU_TearDownFunc fpTearDown);
extern SCU_error SCU_TestSuite_execute(SCU_TestSuite *pSuite);
extern SCU_TestCase *SCU_TestCase_create(SCU_TestSuite *pTestSuite, const char *pName, SCU_TestCaseFunc fpTest, SCU_SetUpFunc fpSetUp, SCU_TearDownFunc fpTearDown);
extern SCU_error SCU_TestCase_execute(SCU_TestCase *pTestCase);
extern SCU_error SCU_executeAllTests();

void SCU_printError(SCU_error error);

#endif