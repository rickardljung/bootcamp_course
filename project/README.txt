Documents:

Contains common documentation of the project such as MVP definition, coding conventions, demo material and doxygen documentation.

Source code:

Contains the complete code for the project divided into following functions areas:
- Drivetrain: Engine and gearbox simulation.
- Input handler: Reading and interpreting user inputs.
- Output handler: Printing status of drivetrain to user.
- Utils: Utilities used by more than one of the above functions.
         For example CAN buffer, CAN i/o thread, output visualization provided by Alten and googletest folder.
         Run SetupVCAN.sh to set up the virtual CAN network used.
- CMakeList for the complete project.
- run.sh: Bash script used to build and run, generate doxygen documentation, run code checks (cppcheck, clang analyzer and clang tidy) and run unit tests.
          Run bash run.sh for complete list of usage.

Each folder has the following structure (if applicable):
- include: container for header files.
- src: container for cpp files.
- test: container for unit tests.
- CMakeList

System overview:

Contains some activity diagrams, component diagrams and MVP definition to give a basic overview of the system.