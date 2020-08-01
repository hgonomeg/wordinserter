# Word Inserter

A simple demo program in C++/Qt demonstrating the usage of Qt Widgets with some simple integration with an sqlite3 database using Qt SQL

### Functionality

The program is very simple and does one thing: It reads text from the input field and writes it to the output field after processing. Like the name of the project suggests, text gets processed by performing random insertions of words read from an sqlite3 database (`default.db` by default). Words are inserted with a given probability between each word from the input text. 

The source database can be modified in a dedicated dialog window. User may also choose to load a different database (compatible with the simple schema; with a table named `phrases` containing two columns: `phrase` and `frequency` storing strings and floating-point numbers accordingly).

### Building

Build using the qmake build system.
Run `qmake` to generate build files for your setup and then use your local make system.
