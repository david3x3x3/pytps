#include <Python.h>
#include <tcl.h>

Tcl_Interp *pyinterp;

static PyObject*
emb_msgget(PyObject *self, PyObject *args) {
  char cmd[256], *arg1;
  PyArg_ParseTuple(args, "s", &arg1);
  //sprintf(buf, "msgget %s", PyString_AsString(object));
  sprintf(cmd, "msgget %s", arg1);
  Tcl_Eval(pyinterp, cmd);
  return Py_BuildValue("s", Tcl_GetStringResult(pyinterp));
}

static PyMethodDef EmbMethods[] = {
  {"msgget", emb_msgget, METH_VARARGS, "Cloverleaf API call msgget"},
  {NULL, NULL, 0, NULL}
};

static PyModuleDef EmbModule = {
  PyModuleDef_HEAD_INIT, "emb", NULL, -1, EmbMethods, NULL, NULL, NULL, NULL
};

static PyObject*
PyInit_emb(void)
{
  return PyModule_Create(&EmbModule);
}

 static int 
 PyTps_Proc_Init_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
 {
   /* int i; */
   /* printf("Py_Tps_Proc_Init_Cmd objc = %d\n", objc); */
   /* for(i=0;i<objc;i++) { */
   /*   printf("Py_Tps_Proc_Init_Cmd arg %d = %s\n", i, Tcl_GetString(objv[i])); */
   /* } */
   FILE *file = fopen(Tcl_GetString(objv[1]),"r");
   // load the Python script; should define the function
   PyRun_SimpleFile(file, Tcl_GetString(objv[1]));

   //Py_Finalize();
   Tcl_SetObjResult(interp, Tcl_NewStringObj("ignore me", -1));
   return TCL_OK;
 }

 static int 
 PyTps_Proc_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
 {
   /* int i; */
   /* printf("Py_Tps_Proc_Cmd objc = %d\n", objc); */
   /* for(i=0;i<objc;i++) { */
   /*   printf("Py_Tps_Proc_Cmd arg %d = %s\n", i, Tcl_GetString(objv[i])); */
   /* } */
   PyObject *py_main = PyImport_AddModule("__main__");

   char *c = malloc(strlen(Tcl_GetString(objv[1]))+256);
   Tcl_ObjSetVar2(interp, Tcl_NewStringObj("PyTpsVar", -1), NULL, objv[2], 0);

   Tcl_Eval(interp, "keylget PyTpsVar CONTEXT");
   PyModule_AddStringConstant(py_main, "py_tps_proc_context", Tcl_GetStringResult(interp));

   Tcl_Eval(interp, "keylget PyTpsVar MODE");
   PyModule_AddStringConstant(py_main, "py_tps_proc_mode", Tcl_GetStringResult(interp));

   Tcl_Eval(interp, "keylget PyTpsVar ARGS.ARGS");
   PyModule_AddStringConstant(py_main, "py_tps_proc_args", Tcl_GetStringResult(interp));

   Tcl_Eval(interp, "keylget PyTpsVar MSGID");
   PyModule_AddStringConstant(py_main, "py_tps_proc_msgid", Tcl_GetStringResult(interp));

   sprintf(c, "%s(context=py_tps_proc_context, mode=py_tps_proc_mode, args=py_tps_proc_args, msgid=py_tps_proc_msgid)", Tcl_GetString(objv[1]));
   PyRun_SimpleString(c);
   free(c);

   //Py_Finalize();
   Tcl_SetObjResult(interp, Tcl_NewStringObj("ignore me", -1));
   return TCL_OK;
 }

 int DLLEXPORT
 Pytps_Init(Tcl_Interp *interp)
 {
     if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
         return TCL_ERROR;
     }
     /* changed this to check for an error - GPS */
     if (Tcl_PkgProvide(interp, "PyTps", "1.0") == TCL_ERROR) {
         return TCL_ERROR;
     }
     Tcl_CreateObjCommand(interp, "py_tps_proc", PyTps_Proc_Cmd, NULL, NULL);
     Tcl_CreateObjCommand(interp, "py_tps_proc_init", PyTps_Proc_Init_Cmd, NULL, NULL);
     pyinterp = interp;
     PyImport_AppendInittab("emb", &PyInit_emb);
     Py_Initialize();
     return TCL_OK;
 }
