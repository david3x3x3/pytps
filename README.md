This code is at the "proof of concept" phase and not ready to do
anything useful.

Recent versions of Cloverleaf allow you to call Python scripts using a
Java wrapper around Jython (Python 2). This code takes a different
approach and provides a TCL wrapper around CPython 3.

Type "make" to compile the shared library and copy it to
$HCISITEDIR/bin.

Copy tps_cpython_script.tcl to your tclprocs folder and add it to
tclIndex (mktclindex).

The test.sh script will run the code.
