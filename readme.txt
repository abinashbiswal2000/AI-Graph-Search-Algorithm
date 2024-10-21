1.  Name    - Abinash Biswal
    UTA ID  - 1002175520

2.  Programming Language Used = C++

3.  How code is Structured?
    -   There are two c++ files
        -   find_route.cpp
        -   myFunctionsAndClasses.cpp
    
    -   In the main function, depending on the number of arguments, either
        Uniform Cost search or Heuristic Search is executed.
    -   There is a uniformCostSearch function, which takes 3 arguments.
    -   The first two arguments are the city names, the third argument is the 
        data structure(Cities information).
        The datastructure is a map with the structure given below
        {
            ParentCityName: {
                ChildCityName: DistanceFromParent
            },
            ParentCityName: {
                ChildCityName: DistanceFromParent
            }......
        }
    -   In the myFunctionsAndClasses.cpp, there is a class called Node, which
        has a method called goToNextNode(), whenever necessary.
        
    -   There is an 80 line gap between the heuristicSearch function and rest of the functions.
    -   There is a heuristicSearch function which takes 4 arguments. 
        There first three are the same as the uniformCostSearch, the last argument
        is the data from the heuristic file.
        The heuristic file is stored in a datastructure like the one given below
        {
            CityName: HeuristicValue,
            CityName: HeuristicValue,
            ........
        }
    -   For the heuristic search, I have used a while loop, which
        moves to the next node whenever necessary.
        
    
4.  How to run the code?
    -   Install a c++ complier like minGW for windows.
        Youtube Video Link for Installation: https://www.youtube.com/watch?v=FEeFG9OR-QU
        Watch from 0:00 - 4:50
    -   Open command prompt (windows) in the folder(directory) where the program files are located.
    -   Type: g++ find_route.cpp -o find_route
        The step above will generate the executable file with the name 'find_route'
    -   Now you may type the following command and see the results
        Command: 
        .\find_route.exe inputFileName.txt City1Name City2Name heuristicFileName.txt
        example - .\find_route.exe input1.txt Luebeck Stuttgart h1.txt
        or
        .\find_route.exe inputFileName.txt City1Name City2Name
        example - .\find_route.exe input1.txt Bremen Kassel

5.  Important Points
    **  Ensure that all the files are in the same folder 
        -   find_route.cpp
        -   myFunctionsAndClasses.cpp
        -   Input file (txt file)
        -   Heuristic File (txt file)
        -   find_route.exe
    
    **  The inputs have to be entered in a particular order.
        Executable_find_route inputFileName.txt City1Name City2Name heuristicFileName.txt

    **  Ensure that you type the name of the city exactly as present in the input file.
        i.e the capitalisation must be matching
        example - London can't we written as london.

    **  Please ensure that the the .txt extension is not missing.
        i.e The input file and the Heuristic file should have a .txt at the end.
        Example - inputFileName.txt, heuristicFileName.txt

    **  Please ensure that the preceeded by '.\'
        Example - .\find_route.exe