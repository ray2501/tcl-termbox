#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include <tcl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "termbox.h"

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#define NS "termbox"

static int INIT_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int INIT_FILE_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int SHUTDOWN_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int WIDTH_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int HEIGHT_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int CLEAR_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int SET_CLEAR_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int PRESENT_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int SET_CURSOR_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int CHANGE_CELL_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int SELECT_INPUT_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int SELECT_OUTPUT_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int PEEK_EVENT_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int POLL_EVENT_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int TO_UNICODE_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);

static int TO_UTF8_CMD(ClientData clientData, Tcl_Interp *interp,
        int onjc, Tcl_Obj *const objv[]);


/*
 * Initializes the termbox library.
 */
static int INIT_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    int ret = 0;

    if( objc != 1 ){
      Tcl_WrongNumArgs(interp, 1, objv, NULL);
      return TCL_ERROR;
    }

    ret = tb_init();
    if (ret < 0) {
        return TCL_ERROR;
    }

    return TCL_OK;
}


/*
 * Initializes the termbox library.
 */
static int INIT_FILE_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    int ret = 0;
    char *file_string = NULL;
    Tcl_Size file_len = 0;

    if( objc != 2 ){
      Tcl_WrongNumArgs(interp, 1, objv, "filename");
      return TCL_ERROR;
    }

    file_string = (char *) Tcl_GetStringFromObj(objv[1], &file_len);
    if( !file_string || file_len < 1 ){
        return TCL_ERROR;
    }

    ret = tb_init_file(file_string);
    if (ret < 0) {
        return TCL_ERROR;
    }

    return TCL_OK;
}


/*
 * After successful initialization, the library must be
 * finalized using the tb_shutdown() function.
 */
static int SHUTDOWN_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    if( objc != 1 ){
      Tcl_WrongNumArgs(interp, 1, objv, NULL);
      return TCL_ERROR;
    }

    tb_shutdown();
    return TCL_OK;
}


static int WIDTH_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    int result = 0;

    if( objc != 1 ){
      Tcl_WrongNumArgs(interp, 1, objv, NULL);
      return TCL_ERROR;
    }

    result = tb_width();
    if (result < 0) {
        return TCL_ERROR;
    }

    Tcl_SetObjResult(interp, Tcl_NewIntObj( result ));
    return TCL_OK;
}


static int HEIGHT_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    int result = 0;

    if( objc != 1 ){
      Tcl_WrongNumArgs(interp, 1, objv, NULL);
      return TCL_ERROR;
    }

    result = tb_height();
    if (result < 0) {
        return TCL_ERROR;
    }

    Tcl_SetObjResult(interp, Tcl_NewIntObj( result ));
    return TCL_OK;
}


static int CLEAR_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    if( objc != 1 ){
      Tcl_WrongNumArgs(interp, 1, objv, NULL);
      return TCL_ERROR;
    }

    tb_clear();
    return TCL_OK;
}


static int SET_CLEAR_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    int fg = 0, bg = 0;
    if( objc != 3 ){
      Tcl_WrongNumArgs(interp, 1, objv, "fg bg");
      return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, objv[1], &fg) != TCL_OK) {
        return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, objv[2], &bg) != TCL_OK) {
        return TCL_ERROR;
    }

    tb_set_clear_attributes((uint16_t) fg, (uint16_t) bg);
    return TCL_OK;
}


/*
 * Synchronizes the internal back buffer with the terminal.
 */
static int PRESENT_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    if( objc != 1 ){
      Tcl_WrongNumArgs(interp, 1, objv, NULL);
      return TCL_ERROR;
    }

    tb_present();
    return TCL_OK;
}


/*
 * Sets the position of the cursor.
 */
static int SET_CURSOR_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    int cx = 0, cy = 0;

    if( objc != 3 ){
      Tcl_WrongNumArgs(interp, 1, objv, "cx cy");
      return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, objv[1], &cx) != TCL_OK) {
        return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, objv[2], &cy) != TCL_OK) {
        return TCL_ERROR;
    }

    tb_set_cursor(cx, cy);
    return TCL_OK;
}


/*
 * Changes cell's parameters in the internal back buffer at the specified
 * position.
 */
static int CHANGE_CELL_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    int x = 0, y = 0;
    long uchar = 0;
    int fg =0, bg = 0;

    if( objc != 6 ){
      Tcl_WrongNumArgs(interp, 1, objv, "x y unicode_char fg bg");
      return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, objv[1], &x) != TCL_OK) {
        return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, objv[2], &y) != TCL_OK) {
        return TCL_ERROR;
    }

    if(Tcl_GetLongFromObj(interp, objv[3], &uchar) != TCL_OK) {
        return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, objv[4], &fg) != TCL_OK) {
        return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, objv[5], &bg) != TCL_OK) {
        return TCL_ERROR;
    }

    tb_change_cell(x, y, (uint32_t) uchar, (uint16_t) fg, (uint16_t) bg);
    return TCL_OK;
}


/*
 * Sets the termbox input mode.
 */
static int SELECT_INPUT_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    int mode = 0;
    int result = 0;

    if( objc != 2 ){
      Tcl_WrongNumArgs(interp, 1, objv, "mode");
      return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, objv[1], &mode) != TCL_OK) {
        return TCL_ERROR;
    }

    result = tb_select_input_mode(mode);
    Tcl_SetObjResult(interp, Tcl_NewIntObj( result ));
    return TCL_OK;
}


/*
 * Sets the termbox output mode.
 */
static int SELECT_OUTPUT_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    int mode = 0;
    int result = 0;

    if( objc != 2 ){
      Tcl_WrongNumArgs(interp, 1, objv, "mode");
      return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, objv[1], &mode) != TCL_OK) {
        return TCL_ERROR;
    }

    result = tb_select_output_mode(mode);
    Tcl_SetObjResult(interp, Tcl_NewIntObj( result ));
    return TCL_OK;
}


/*
 * Wait for an event up to 'timeout' milliseconds and fill the 'event'
 * structure with it, when the event is available.
 */
static int PEEK_EVENT_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    int timeout = 0;
    struct tb_event event;
    int result = 0;
    Tcl_Obj *pResultStr = NULL;

    if( objc != 2 ){
      Tcl_WrongNumArgs(interp, 1, objv, "timeout");
      return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, objv[1], &timeout) != TCL_OK) {
        return TCL_ERROR;
    }

    result = tb_peek_event(&event, timeout);

    if (result < 0) {
        return TCL_ERROR;
    }

    pResultStr = Tcl_NewListObj(0, NULL);
    if (result > 0) {
        Tcl_ListObjAppendElement(interp, pResultStr, Tcl_NewLongObj(event.type));
        Tcl_ListObjAppendElement(interp, pResultStr, Tcl_NewLongObj(event.mod));
        Tcl_ListObjAppendElement(interp, pResultStr, Tcl_NewLongObj(event.key));
        Tcl_ListObjAppendElement(interp, pResultStr, Tcl_NewLongObj(event.ch));
        Tcl_ListObjAppendElement(interp, pResultStr, Tcl_NewLongObj(event.x));
        Tcl_ListObjAppendElement(interp, pResultStr, Tcl_NewLongObj(event.y));
    }

    Tcl_SetObjResult(interp, pResultStr);
    return TCL_OK;
}


/*
 * Wait for an event forever and fill the 'event' structure with it, when the
 * event is available.
 */
static int POLL_EVENT_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    struct tb_event event;
    int result = 0;
    Tcl_Obj *pResultStr = NULL;

    if( objc != 1 ){
      Tcl_WrongNumArgs(interp, 1, objv, NULL);
      return TCL_ERROR;
    }

    result = tb_poll_event(&event);
    if (result < 0) {
        return TCL_ERROR;
    }

    pResultStr = Tcl_NewListObj(6, NULL);
    Tcl_ListObjAppendElement(interp, pResultStr, Tcl_NewLongObj(event.type));
    Tcl_ListObjAppendElement(interp, pResultStr, Tcl_NewLongObj(event.mod));
    Tcl_ListObjAppendElement(interp, pResultStr, Tcl_NewLongObj(event.key));
    Tcl_ListObjAppendElement(interp, pResultStr, Tcl_NewLongObj(event.ch));
    Tcl_ListObjAppendElement(interp, pResultStr, Tcl_NewLongObj(event.x));
    Tcl_ListObjAppendElement(interp, pResultStr, Tcl_NewLongObj(event.y));

    Tcl_SetObjResult(interp, pResultStr);
    return TCL_OK;
}


static int TO_UNICODE_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    int ret = 0;
    char *string = NULL;
    Tcl_Size len = 0;
    uint32_t out;

    if( objc != 2 ){
      Tcl_WrongNumArgs(interp, 1, objv, "utf8_chars");
      return TCL_ERROR;
    }

    string = (char *) Tcl_GetStringFromObj(objv[1], &len);
    if( !string || len < 1 ){
        return TCL_ERROR;
    }

    ret = tb_utf8_char_to_unicode(&out, string);
    if (ret < 0) {
        return TCL_ERROR;
    }

    Tcl_SetObjResult(interp, Tcl_NewLongObj( (long) out ));
    return TCL_OK;
}


static int TO_UTF8_CMD(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    long out;
    char str[7];
    int str_len;
    Tcl_Obj *pResultStr;

    if( objc != 2 ){
      Tcl_WrongNumArgs(interp, 1, objv, "unicode_char");
      return TCL_ERROR;
    }

    if(Tcl_GetLongFromObj(interp, objv[1], &out) != TCL_OK) {
      return TCL_ERROR;
    }

    if (out <= 0) {
      return TCL_ERROR;
    }

    str_len = tb_utf8_unicode_to_char(str, out);
    if (str_len <= 0) {
        return TCL_ERROR;
    }

    pResultStr = Tcl_NewStringObj( str,  str_len );
    Tcl_SetObjResult(interp, pResultStr);
    return TCL_OK;
}


/*
 *----------------------------------------------------------------------
 *
 * Termbox_Init --
 *
 *  Initialize the new package.
 *
 * Results:
 *  A standard Tcl result
 *
 * Side effects:
 *  The Termbox package is created.
 *
 *----------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */
DLLEXPORT int
Termbox_Init(Tcl_Interp *interp)
{
    Tcl_Namespace *nsPtr; /* pointer to hold our own new namespace */

    if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
        return TCL_ERROR;
    }

    if (Tcl_PkgProvide(interp, PACKAGE_NAME, PACKAGE_VERSION) != TCL_OK) {
        return TCL_ERROR;
    }

    /*
     * Create the namespace named re2.
     * re2 command is too short, we need a namespace.
     */
    nsPtr = Tcl_CreateNamespace(interp, "::" NS, NULL, NULL);
    if (nsPtr == NULL) {
        return TCL_ERROR;
    }

    Tcl_CreateObjCommand(interp, "::termbox::init", INIT_CMD, NULL, NULL);
    Tcl_CreateObjCommand(interp, "::termbox::init_file", INIT_FILE_CMD, NULL, NULL);
    Tcl_CreateObjCommand(interp, "::termbox::shutdown", SHUTDOWN_CMD, NULL, NULL);

    Tcl_CreateObjCommand(interp, "::termbox::width", WIDTH_CMD, NULL, NULL);
    Tcl_CreateObjCommand(interp, "::termbox::height", HEIGHT_CMD, NULL, NULL);

    Tcl_CreateObjCommand(interp, "::termbox::clear", CLEAR_CMD, NULL, NULL);
    Tcl_CreateObjCommand(interp, "::termbox::set_clear_attributes", SET_CLEAR_CMD, NULL, NULL);

    Tcl_CreateObjCommand(interp, "::termbox::present", PRESENT_CMD, NULL, NULL);

    Tcl_CreateObjCommand(interp, "::termbox::set_cursor", SET_CURSOR_CMD, NULL, NULL);

    Tcl_CreateObjCommand(interp, "::termbox::change_cell", CHANGE_CELL_CMD, NULL, NULL);

    Tcl_CreateObjCommand(interp, "::termbox::select_input_mode", SELECT_INPUT_CMD, NULL, NULL);

    Tcl_CreateObjCommand(interp, "::termbox::select_output_mode", SELECT_OUTPUT_CMD, NULL, NULL);

    Tcl_CreateObjCommand(interp, "::termbox::peek_event", PEEK_EVENT_CMD, NULL, NULL);
    Tcl_CreateObjCommand(interp, "::termbox::poll_event", POLL_EVENT_CMD, NULL, NULL);

    Tcl_CreateObjCommand(interp, "::termbox::utf8_char_to_unicode", TO_UNICODE_CMD, NULL, NULL);
    Tcl_CreateObjCommand(interp, "::termbox::utf8_unicode_to_char", TO_UTF8_CMD, NULL, NULL);

   /*
    * Key constants
    */
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_F1", NULL, Tcl_NewIntObj(TB_KEY_F1), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_F2", NULL, Tcl_NewIntObj(TB_KEY_F2), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_F3", NULL, Tcl_NewIntObj(TB_KEY_F3), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_F4", NULL, Tcl_NewIntObj(TB_KEY_F4), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_F5", NULL, Tcl_NewIntObj(TB_KEY_F5), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_F6", NULL, Tcl_NewIntObj(TB_KEY_F6), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_F7", NULL, Tcl_NewIntObj(TB_KEY_F7), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_F8", NULL, Tcl_NewIntObj(TB_KEY_F8), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_F9", NULL, Tcl_NewIntObj(TB_KEY_F9), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_F10", NULL, Tcl_NewIntObj(TB_KEY_F10), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_F11", NULL, Tcl_NewIntObj(TB_KEY_F11), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_F12", NULL, Tcl_NewIntObj(TB_KEY_F12), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_INSERT", NULL, Tcl_NewIntObj(TB_KEY_INSERT), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_DELETE", NULL, Tcl_NewIntObj(TB_KEY_DELETE), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_HOME", NULL, Tcl_NewIntObj(TB_KEY_HOME), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_END", NULL, Tcl_NewIntObj(TB_KEY_END), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_PGUP", NULL, Tcl_NewIntObj(TB_KEY_PGUP), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_PGDN", NULL, Tcl_NewIntObj(TB_KEY_PGDN), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_ARROW_UP", NULL, Tcl_NewIntObj(TB_KEY_ARROW_UP), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_ARROW_DOWN", NULL,
                  Tcl_NewIntObj(TB_KEY_ARROW_DOWN), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_ARROW_LEFT", NULL,
                  Tcl_NewIntObj(TB_KEY_ARROW_LEFT), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_ARROW_RIGHT", NULL,
                  Tcl_NewIntObj(TB_KEY_ARROW_RIGHT), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_MOUSE_LEFT", NULL,
                  Tcl_NewIntObj(TB_KEY_MOUSE_LEFT), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_MOUSE_RIGHT", NULL,
                  Tcl_NewIntObj(TB_KEY_MOUSE_RIGHT), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_MOUSE_MIDDLE", NULL,
                  Tcl_NewIntObj(TB_KEY_MOUSE_MIDDLE), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_MOUSE_RELEASE", NULL,
                  Tcl_NewIntObj(TB_KEY_MOUSE_RELEASE), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_MOUSE_WHEEL_UP", NULL,
                  Tcl_NewIntObj(TB_KEY_MOUSE_WHEEL_UP), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_MOUSE_WHEEL_DOWN", NULL,
                  Tcl_NewIntObj(TB_KEY_MOUSE_WHEEL_DOWN), 0);

   /*
    * These are all ASCII code points below SPACE character and a BACKSPACE key
    */
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_TILDE", NULL, Tcl_NewIntObj(TB_KEY_CTRL_TILDE), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_2", NULL, Tcl_NewIntObj(TB_KEY_CTRL_2), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_A", NULL, Tcl_NewIntObj(TB_KEY_CTRL_A), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_B", NULL, Tcl_NewIntObj(TB_KEY_CTRL_B), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_C", NULL, Tcl_NewIntObj(TB_KEY_CTRL_C), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_D", NULL, Tcl_NewIntObj(TB_KEY_CTRL_D), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_E", NULL, Tcl_NewIntObj(TB_KEY_CTRL_E), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_F", NULL, Tcl_NewIntObj(TB_KEY_CTRL_F), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_G", NULL, Tcl_NewIntObj(TB_KEY_CTRL_G), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_BACKSPACE", NULL, Tcl_NewIntObj(TB_KEY_BACKSPACE), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_H", NULL, Tcl_NewIntObj(TB_KEY_CTRL_H), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_TAB", NULL, Tcl_NewIntObj(TB_KEY_TAB), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_I", NULL, Tcl_NewIntObj(TB_KEY_CTRL_I), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_J", NULL, Tcl_NewIntObj(TB_KEY_CTRL_J), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_K", NULL, Tcl_NewIntObj(TB_KEY_CTRL_K), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_L", NULL, Tcl_NewIntObj(TB_KEY_CTRL_L), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_ENTER", NULL, Tcl_NewIntObj(TB_KEY_ENTER), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_M", NULL, Tcl_NewIntObj(TB_KEY_CTRL_M), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_N", NULL, Tcl_NewIntObj(TB_KEY_CTRL_N), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_O", NULL, Tcl_NewIntObj(TB_KEY_CTRL_O), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_P", NULL, Tcl_NewIntObj(TB_KEY_CTRL_P), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_Q", NULL, Tcl_NewIntObj(TB_KEY_CTRL_Q), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_R", NULL, Tcl_NewIntObj(TB_KEY_CTRL_R), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_S", NULL, Tcl_NewIntObj(TB_KEY_CTRL_S), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_T", NULL, Tcl_NewIntObj(TB_KEY_CTRL_T), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_U", NULL, Tcl_NewIntObj(TB_KEY_CTRL_U), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_V", NULL, Tcl_NewIntObj(TB_KEY_CTRL_V), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_W", NULL, Tcl_NewIntObj(TB_KEY_CTRL_W), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_X", NULL, Tcl_NewIntObj(TB_KEY_CTRL_X), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_Y", NULL, Tcl_NewIntObj(TB_KEY_CTRL_Y), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_Z", NULL, Tcl_NewIntObj(TB_KEY_CTRL_Z), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_ESC", NULL, Tcl_NewIntObj(TB_KEY_ESC), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_LSQ_BRACKET", NULL,
                  Tcl_NewIntObj(TB_KEY_CTRL_LSQ_BRACKET), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_3", NULL, Tcl_NewIntObj(TB_KEY_CTRL_3), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_4", NULL, Tcl_NewIntObj(TB_KEY_CTRL_4), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_BACKSLASH", NULL,
                  Tcl_NewIntObj(TB_KEY_CTRL_BACKSLASH), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_5", NULL, Tcl_NewIntObj(TB_KEY_CTRL_5), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_RSQ_BRACKET", NULL,
                  Tcl_NewIntObj(TB_KEY_CTRL_RSQ_BRACKET), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_6", NULL, Tcl_NewIntObj(TB_KEY_CTRL_6), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_7", NULL, Tcl_NewIntObj(TB_KEY_CTRL_7), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_SLASH", NULL,
                  Tcl_NewIntObj(TB_KEY_CTRL_SLASH), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_UNDERSCORE", NULL,
                  Tcl_NewIntObj(TB_KEY_CTRL_UNDERSCORE), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_SPACE", NULL, Tcl_NewIntObj(TB_KEY_SPACE), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_BACKSPACE2", NULL,
                  Tcl_NewIntObj(TB_KEY_BACKSPACE2), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_KEY_CTRL_8", NULL, Tcl_NewIntObj(TB_KEY_CTRL_8), 0);

   /*
    * Alt modifier constant
    */
    Tcl_SetVar2Ex(interp, "::termbox::TB_MOD_ALT", NULL, Tcl_NewIntObj(TB_MOD_ALT), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_MOD_MOTION", NULL, Tcl_NewIntObj(TB_MOD_MOTION), 0);

   /*
    * Colors
    */
    Tcl_SetVar2Ex(interp, "::termbox::TB_DEFAULT", NULL, Tcl_NewIntObj(TB_DEFAULT), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_BLACK", NULL, Tcl_NewIntObj(TB_BLACK), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_RED", NULL, Tcl_NewIntObj(TB_RED), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_GREEN", NULL, Tcl_NewIntObj(TB_GREEN), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_YELLOW", NULL, Tcl_NewIntObj(TB_YELLOW), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_BLUE", NULL, Tcl_NewIntObj(TB_BLUE), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_MAGENTA", NULL, Tcl_NewIntObj(TB_MAGENTA), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_CYAN", NULL, Tcl_NewIntObj(TB_CYAN), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_WHITE", NULL, Tcl_NewIntObj(TB_WHITE), 0);

   /*
    * Attributes
    */
    Tcl_SetVar2Ex(interp, "::termbox::TB_BOLD", NULL, Tcl_NewIntObj(TB_BOLD), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_UNDERLINE", NULL, Tcl_NewIntObj(TB_UNDERLINE), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_REVERSE", NULL, Tcl_NewIntObj(TB_REVERSE), 0);

   /*
    * Event type
    */
    Tcl_SetVar2Ex(interp, "::termbox::TB_EVENT_KEY", NULL, Tcl_NewIntObj(TB_EVENT_KEY), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_EVENT_RESIZE", NULL, Tcl_NewIntObj(TB_EVENT_RESIZE), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_EVENT_MOUSE", NULL, Tcl_NewIntObj(TB_EVENT_MOUSE), 0);

   /*
    * Sets the termbox input mode. Termbox has two input modes:
    * 1. Esc input mode.
    *    When ESC sequence is in the buffer and it doesn't match any known
    *    ESC sequence => ESC means TB_KEY_ESC.
    * 2. Alt input mode.
    *    When ESC sequence is in the buffer and it doesn't match any known
    *    sequence => ESC enables TB_MOD_ALT modifier for the next keyboard event.
    */
    Tcl_SetVar2Ex(interp, "::termbox::TB_INPUT_CURRENT", NULL, Tcl_NewIntObj(TB_INPUT_CURRENT), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_INPUT_ESC", NULL, Tcl_NewIntObj(TB_INPUT_ESC), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_INPUT_ALT", NULL, Tcl_NewIntObj(TB_INPUT_ALT), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_INPUT_MOUSE", NULL, Tcl_NewIntObj(TB_INPUT_MOUSE), 0);

   /* Sets the termbox output mode. Termbox has three output options:
    * 1. TB_OUTPUT_NORMAL     => [1..8]
    * 2. TB_OUTPUT_256        => [0..256]
    * 3. TB_OUTPUT_216        => [0..216]
    * 4. TB_OUTPUT_GRAYSCALE  => [0..23]
    *    This mode supports the 4th range of the 256 mode only.
    */
    Tcl_SetVar2Ex(interp, "::termbox::TB_OUTPUT_CURRENT", NULL, Tcl_NewIntObj(TB_OUTPUT_CURRENT), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_OUTPUT_NORMAL", NULL, Tcl_NewIntObj(TB_OUTPUT_NORMAL), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_OUTPUT_256", NULL, Tcl_NewIntObj(TB_OUTPUT_256), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_OUTPUT_216", NULL, Tcl_NewIntObj(TB_OUTPUT_216), 0);
    Tcl_SetVar2Ex(interp, "::termbox::TB_OUTPUT_GRAYSCALE", NULL, Tcl_NewIntObj(TB_OUTPUT_GRAYSCALE), 0);

    return TCL_OK;
}
#ifdef __cplusplus
}
#endif  /* __cplusplus */
