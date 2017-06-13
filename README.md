# SCUnit
<h2>Simple C Unittest framework</h2>

<p>There are a lot of unittest frameworks, but I wanted a very simple one for my own projects (written in C). I've looked at a couple of other frameworks, most notably the <i>C Unit Testing Framework</i> (see http://cunit.sourceforge.net/index.html written by Anil Kumar, John Pye and Martin Gerhardy). But I didn't find the right (simple!)  one for me, so decided to write my own :).</p>
<p>The SCUnit framework is build around two "classes":
<ul>
<li>SCU_TestSuite</li>
<li>SCU_TestCase</li>
</ul>
A unit test comprises of one or more <i>SCU_TestSuite</i> structs which are composed of one or more <i>SCU_TestCase</i> structs. You create a <i>SCU_TestSuite</i> with the <i><b>SCU_TestSuite_create()</b></i> function, which takes a name, a StartUp function and a TearDown functions as argument. Then you add TestCases with the function <i><b>SCU_TestCase_create()</b></i>. This function is similar to de TestSuite create function in that it has the same argument and then some; a reference to the Suite tis new TestCase is added and ofcourse a TestCase function.</p>
<p>Note that TestSuites and TestCases are C structs and are linked to the next TestSuite / TestCase in a circular list. Each new item is added at the end, so the creation order is preserved. All TestSuites are in one list, with a global pointer <i>SCU_lastTestSuite</i> referencing the last in the list (therefore looping over all items is starting at the next and then check if the current pointer matches the last to decide if all items are processed). All TestCases are ofcourse part of a circular list per TestSuite, which also references the last TestCase.</p>
<p>To actually run then unittest session is nothing more than calling <i><b>SCU_executeAllTests()</b></i>, although you could run seperate TestSuites or even separate TestCases bij calling their respective execute functions. One thing to note about running is the global runmode <i>SCU_runMode</i>;
<ul>
<li>SCU_RUN_MODE_SILENT (no output),</li>
<li>SCU_RUN_MODE_NORMAL (default, only result line per Suite) and</li>
<li>SCU_RUN_MODE_VERBOSE (print everything of interrest).</li>
</ul></p>
<p>The result of every test is either a <i>SCU_SUCCESS</i> if everything went allright and all tests where succesfull, a <i>SCU_FAILED</i> if one or more tests failed or a negative error number, being some kind of <i>SCU_FATAL_ERROR()</i></p>
<p>Test case functions must use the <i><b>SCU_ASSERT(EQUATION, VALUE)</b></i> macro for assertions. First parameter (EQUATIONS) is the assertion which must hold true. The second parameter (VALUE) is the value (variable) which is asserted. All values are cast to unsigned long and printed (if run mode is SCU_RUN_MODE_VERBOSE)</p>
<hr/>
<h2>Build environment</h2>
<p>I use CodeLite (see https://codelite.org/) as the development environment. After installation, use CodeLite to download and install the GNU C compiler suite (gcc - Mingw). After installing open the .workspace file in the root of the sources. SCUnit is the library project, SCUnitTest a simple test example.</p>
<hr/>
<h2>Copyright</h2>
<p>Copyright 2017 Remco van Maanen</p>
<br/>
<p><b>SCUnit is free software:</p> you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.</p>
<p>SCUnit is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.</p>
<p>You should have received a copy of the GNU General Public License along with this program. (see file COPYING) If not, see <http://www.gnu.org/licenses/>.</p>
