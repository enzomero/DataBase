How to run this program:

    make -f mk.build all
    make -f mk.build run
    
The rules for using database:

'Add' - command for puting envent with particular date into database.
Input example:
    Add YYYY-MM-dd <event> - where <event> is a string without spaces or eof.
    
'Find' - command for finding all events in particular date and print them.
Input example:
    Find YYYY-MM-dd - output will be empty if event with the date was not finding.
    
'Del' - command for removing one event or all events with particular date.
Input example:
    Del YYYY-MM-dd <event> - this way for removing only one event from database.
    Del YYYY-MM-dd - this commad will be remove all events with that date.
    
'Print' - command for print rows of database.
Input example:
    Print - output will be empty if database is empty.