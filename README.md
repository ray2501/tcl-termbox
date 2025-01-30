tcl-termbox
=====

This package is Tcl bindings for [termbox](https://github.com/termbox/termbox).

termbox is a minimal, legacy-free alternative to ncurses,
suitable for building text-based user interfaces.

The main idea is viewing terminals as a table of fixed-size
cells and input being a stream of structured messages.
The abstraction itself is not perfect and it may create
problems in certain areas. The most sensitive ones are
copy & pasting and wide characters (mostly Chinese, Japanese,
Korean (CJK) characters). When it comes to copy & pasting,
the notion of cells is not really compatible with the idea of
text.


UNIX BUILD
=====

I only test at openSUSE LEAP 15.2.

Building under most UNIX systems is easy, just run the configure script
and then run make. For more information about the build process, see
the tcl/unix/README file in the Tcl src dist. The following minimal
example will install the extension in the /opt/tcl directory.

    $ cd tcl-termbox
    $ ./configure --prefix=/opt/tcl
    $ make
    $ make install

If you need setup directory containing tcl configuration (tclConfig.sh),
below is an example:

    $ cd tcl-termbox
    $ ./configure --with-tcl=/opt/activetcl/lib
    $ make
    $ make install


Commands
=====

::termbox::init  
::termbox::init_file filename  
::termbox::shutdown  
::termbox::width  
::termbox::height  
::termbox::clear  
::termbox::set_clear_attributes fg bg  
::termbox::present  
::termbox::set_cursor cx cy  
::termbox::change_cell x y unicode_char fg bg  
::termbox::select_input_mode mode  
::termbox::select_output_mode mode  
::termbox::peek_event timeout  
::termbox::poll_event  
::termbox::utf8_char_to_unicode utf8_chars  
::termbox::utf8_unicode_to_char unicode_char  


Variable
=====

::termbox::TB_KEY_F1  
::termbox::TB_KEY_F2  
::termbox::TB_KEY_F3  
::termbox::TB_KEY_F4  
::termbox::TB_KEY_F5  
::termbox::TB_KEY_F6  
::termbox::TB_KEY_F7  
::termbox::TB_KEY_F8  
::termbox::TB_KEY_F9  
::termbox::TB_KEY_F10  
::termbox::TB_KEY_F11  
::termbox::TB_KEY_F12  
::termbox::TB_KEY_INSERT  
::termbox::TB_KEY_DELETE  
::termbox::TB_KEY_HOME  
::termbox::TB_KEY_END  
::termbox::TB_KEY_PGUP  
::termbox::TB_KEY_PGDN  
::termbox::TB_KEY_ARROW_UP  
::termbox::TB_KEY_ARROW_DOWN  
::termbox::TB_KEY_ARROW_LEFT  
::termbox::TB_KEY_ARROW_RIGHT  
::termbox::TB_KEY_MOUSE_LEFT  
::termbox::TB_KEY_MOUSE_RIGHT  
::termbox::TB_KEY_MOUSE_MIDDLE  
::termbox::TB_KEY_MOUSE_RELEASE  
::termbox::TB_KEY_MOUSE_WHEEL_UP  
::termbox::TB_KEY_MOUSE_WHEEL_DOWN  

::termbox::TB_KEY_CTRL_TILDE  
::termbox::TB_KEY_CTRL_2  
::termbox::TB_KEY_CTRL_A  
::termbox::TB_KEY_CTRL_B  
::termbox::TB_KEY_CTRL_C  
::termbox::TB_KEY_CTRL_D  
::termbox::TB_KEY_CTRL_E  
::termbox::TB_KEY_CTRL_F  
::termbox::TB_KEY_CTRL_G  
::termbox::TB_KEY_BACKSPACE  
::termbox::TB_KEY_CTRL_H  
::termbox::TB_KEY_TAB  
::termbox::TB_KEY_CTRL_I  
::termbox::TB_KEY_CTRL_J  
::termbox::TB_KEY_CTRL_K  
::termbox::TB_KEY_CTRL_L  
::termbox::TB_KEY_ENTER  
::termbox::TB_KEY_CTRL_M  
::termbox::TB_KEY_CTRL_N  
::termbox::TB_KEY_CTRL_O  
::termbox::TB_KEY_CTRL_P  
::termbox::TB_KEY_CTRL_Q  
::termbox::TB_KEY_CTRL_S  
::termbox::TB_KEY_CTRL_T  
::termbox::TB_KEY_CTRL_U  
::termbox::TB_KEY_CTRL_V  
::termbox::TB_KEY_CTRL_W  
::termbox::TB_KEY_CTRL_X  
::termbox::TB_KEY_CTRL_Y  
::termbox::TB_KEY_CTRL_Z  
::termbox::TB_KEY_ESC  
::termbox::TB_KEY_CTRL_LSQ_BRACKET  
::termbox::TB_KEY_CTRL_3  
::termbox::TB_KEY_CTRL_4  
::termbox::TB_KEY_CTRL_BACKSLASH  
::termbox::TB_KEY_CTRL_5  
::termbox::TB_KEY_CTRL_RSQ_BRACKET  
::termbox::TB_KEY_CTRL_6  
::termbox::TB_KEY_CTRL_7  
::termbox::TB_KEY_CTRL_SLASH  
::termbox::TB_KEY_CTRL_UNDERSCORE  
::termbox::TB_KEY_SPACE  
::termbox::TB_KEY_BACKSPACE2  
::termbox::TB_KEY_CTRL_8  

::termbox::TB_MOD_ALT  
::termbox::TB_MOD_MOTION  

::termbox::TB_DEFAULT  
::termbox::TB_BLACK  
::termbox::TB_RED  
::termbox::TB_GREEN  
::termbox::TB_YELLOW  
::termbox::TB_BLUE  
::termbox::TB_MAGENTA  
::termbox::TB_CYAN  
::termbox::TB_WHITE  

::termbox::TB_BOLD  
::termbox::TB_UNDERLINE  
::termbox::TB_REVERSE  

::termbox::TB_EVENT_KEY  
::termbox::TB_EVENT_RESIZE  
::termbox::TB_EVENT_MOUSE  

::termbox::TB_INPUT_CURRENT  
::termbox::TB_INPUT_ESC  
::termbox::TB_INPUT_ALT  
::termbox::TB_INPUT_MOUSE  

::termbox::TB_OUTPUT_CURRENT  
::termbox::TB_OUTPUT_NORMAL  
::termbox::TB_OUTPUT_256  
::termbox::TB_OUTPUT_216  
::termbox::TB_OUTPUT_GRAYSCALE  


Example
=====

Below is a simple example:

    package require termbox
    
    ::termbox::init
    ::termbox::change_cell 1 1 [scan "@" %c] $::termbox::TB_WHITE 0
    ::termbox::present
    ::termbox::peek_event -1
    ::termbox::shutdown

