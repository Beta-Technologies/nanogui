#!/bin/bash
# run the script (using python 3 only) to autogen the py_doc.h file.
# this is required if you add new python bindings or change the nannogui classes and existing bindings.
echo 'running py_doc autogen'
./mkdoc_rst.py \
-I../include/  \
-I../include/nanogui \
-I../ext/eigen \
-I../ext/glfw/include \
-I../ext/nanovg/src/ \
-I../ext/pybind11/include/pybind1/ \
../include/nanogui/*.h \
../include/nanogui/extended/*.h > ../python/py_doc.h
echo 'py_doc autogen completed'
