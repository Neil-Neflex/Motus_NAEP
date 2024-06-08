#include <libsx.h>
#include "callback.h"

void create_display(int argc, char *argv[]) {
    if (OpenDisplay(argc, argv) == 0) {
        fprintf(stderr, "Can't open display\n");
        return;
    }

    Widget quit_btn = MakeButton("Quit", quit_cb, NULL);
    Widget help_btn = MakeButton("Help", help_cb, NULL);
    Widget reset_btn = MakeButton("Reset", reset_cb, NULL);
    
    Widget input_field = MakeStringEntry(NULL, 100, NULL, NULL);
    Widget submit_btn = MakeButton("Submit", submit_cb, (void*)input_field);

    SetWidgetPos(help_btn, PLACE_RIGHT, quit_btn, NO_CARE, NULL);
    SetWidgetPos(reset_btn, PLACE_RIGHT, help_btn, NO_CARE, NULL);
    SetWidgetPos(input_field, PLACE_UNDER, quit_btn, NO_CARE, NULL);
    SetWidgetPos(submit_btn, PLACE_RIGHT, input_field, NO_CARE, NULL);
    
    ShowDisplay();
}

int main(int argc, char *argv[]) {
    create_display(argc, argv);
    MainLoop();
    return 0;
}
