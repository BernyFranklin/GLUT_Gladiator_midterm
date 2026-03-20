Hello team,
To get this project started:
--------- Powershell ---------
-- Via powershell navigate to a directory where you want the repo
-- Execute "git clone https://github.com/BernyFranklin/GLUT_Gladiator_midterm.git"
--------- Code::Blocks ---------
-- Select "Open an existing project", triggers file explorer
-- Select the "GULT_Gladiator_Midterm.cbp", empty project tree displayed
-- Right-click the project name and select "Add files recursively"
-- Select the project folder, triggers selection
-- Make this window big, make sure the only files deselected are the CMake at the top, the gitignore, the common folder, and anything with .lib, .a, .dll
-- Go to the top menu and select Project->Properties...
-- Select the "Build Targets" tab\
-- Make sure the "Execution working dir" is the GULT_Gladiator_Midterm folder inside the directory where you cloned the repo. 
-- Go to the top menu and select Project->BuildOptions
-- Go to the "Linker Settings" tab and make the link libraries look like this:
    common\lib\libSoil.a
    common\libglew32.lib
    common\lib\freeglut.lib
    freeglut
    opengl32
    glu32
    winmm
    gdi32
    common\liblibirrKlang.a
-- Go to the "Search Directories" tab in build options, select the common/include folder inside the project: "~\GLUT_Gladiator_midterm\common\include"
-- Build and run.
