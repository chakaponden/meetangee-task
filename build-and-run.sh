#!/bin/bash
# dependencies libs folder names
project_path=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
# build project
cd $project_path/build
cmake ..
make
# generate doxygen documentation
cd $project_path/doc
doxygen Doxyfile
# generate latex pdf documentation to refman.pdf file
cd $project_path/doc/latex
make
# output info
echo "Generated documentation location: $project_path/doc"
echo "Generated pdf documentation file: $project_path/doc/latex/refman.pdf"
echo "Program execution file: $project_path/build/itransition-task"
# run program
echo "Execute program: $project_path/build/itransition-task http://www.meetangee.com"
$project_path/build/itransition-task http://www.meetangee.com