# -*- tcl -*-
# Tcl package index file, version 1.1
#
if {[package vsatisfies [package provide Tcl] 9.0-]} {
    package ifneeded termbox 0.4 \
	    [list load [file join $dir libtcl9termbox0.4.so] [string totitle termbox]]
} else {
    package ifneeded termbox 0.4 \
	    [list load [file join $dir libtermbox0.4.so] [string totitle termbox]]
}
