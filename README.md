#Follow these three steps below to get the program compiled successfully in microsoft visual studio 2017 and run:  

  1.Install the extension of Qt VS Tools and make it set right with including the Qt version path which in my computer is
"C:\Qt\5.14.2\msvc2017_64".  

  2.Set the windows system environment path which in my computer is "C:\Qt\5.14.2\msvc2017_64\bin" that contains all the
dynamic libraries our Qt program needs while it is running.  

  3.Compile source files. It is worth noting that maybe the expression of including header files in the files which your user interface
compiler automaticaly output is '#include <MyButton.h>',try changng it to '#include "MyButton.h"' if you encounter fails in compilation.
