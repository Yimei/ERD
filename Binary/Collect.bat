SET PATH=c:\Program Files (x86)\Microsoft Visual Studio 10.0\Team Tools\Performance Tools\
vsinstr @CommandOption.txt
vsperfcmd -start:coverage -output:102598058_ERD_UnitTesting.coverage
102598058_ERD_UnitTesting.exe
vsperfcmd -shutdown
echo Complete!
pause