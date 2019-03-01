#!/bin/bash
hcitpstest -r run -a -x ASCII -f nl -S -c sms_ib_data -e "hcitpstestshowbydisp " /opt/cloverleaf/cis6.2/integrator/js_and_python/data/cpython/pytps/msg.txt "tps_cpython_script { SCRIPT tps_test1.py } { FUNCTION tps_test1 } { ARGS testarg }"
