######################################################################
# Name:      tps_cpython_script
# Purpose:   <description>
# UPoC type: tps
# Args:      tps keyedlist containing the following keys:
#            MODE    run mode ("start", "run", "time" or "shutdown")
#            MSGID   message handle
#            CONTEXT tps caller context
#            ARGS    user-supplied arguments:
#                    <describe user-supplied args here>
#
# Returns:   tps disposition list:
#            <describe dispositions used here>
#
# Notes:     <put your notes here>
#
# History:   <date> <name> <comments>
#                 

proc tps_cpython_script { args } {
    global HciConnName                             ;# Name of thread
    
    keylget args MODE mode                         ;# Fetch mode
    set ctx ""   ; keylget args CONTEXT ctx        ;# Fetch tps caller context
    set uargs {} ; keylget args ARGS uargs         ;# Fetch user-supplied args

    set debug 0  ;                                 ;# Fetch user argument DEBUG and
    catch {keylget uargs DEBUG debug}              ;# assume uargs is a keyed list

    set module "tps_david/$HciConnName/$ctx" ;# Use this before every echo/puts,
                                                   ;# it describes where the text came from

    set dispList {}                                ;# Nothing to return

    switch -exact -- $mode {
        start {
            # Perform special init functions
            # N.B.: there may or may not be a MSGID key in args
            
            if { $debug } {
                puts stdout "$module: Starting in debug mode..."
            }
	    load $::HciSiteDir/bin/libpytps[info sharedlibextension]
	    set uargs [keylget args ARGS]
	    set script [keylget uargs SCRIPT]
	    keyldel uargs SCRIPT
	    keylset args ARGS $uargs
	    #echo calling py_tps_proc_init $script $args
	    py_tps_proc_init $script $args
        }

        run {
            # 'run' mode always has a MSGID; fetch and process it
            
            keylget args MSGID mh
	    
	    set uargs [keylget args ARGS]
	    set script [keylget uargs FUNCTION]
	    keyldel uargs SCRIPT
	    keyldel uargs FUNCTION
	    keylset args ARGS $uargs
	    echo calling py_tps_proc $script $args
	    return [py_tps_proc $script $args]
        }

        time {
            # Timer-based processing
            # N.B.: there may or may not be a MSGID key in args
            
        }
        
        shutdown {
            # Doing some clean-up work 
            
        }
        
        default {
            error "Unknown mode '$mode' in $module"
        }
    }

    return $dispList
}
