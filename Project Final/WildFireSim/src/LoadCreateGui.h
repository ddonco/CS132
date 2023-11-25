#ifndef LOADCREATEGUI_H
#define LOADCREATEGUI_H

#include "gbutton.h"
#include "gchooser.h"
#include "glabel.h"
#include "gwindow.h"
#include "gfilechooser.h"
#include "gcontainer.h"
#include "NewMap.h"
#include "FireSimGui.h"
#include "FireSimModel.h"

using namespace sgl;
using namespace std;

class LoadCreateGui {
public:
    /**
     * @brief LoadCreateGui Displays a gui with options for creating or loading a map file
     */
    LoadCreateGui();
private:
    // Font face used in the window.
    const string FONT_FAMILY = "Arial";
    // Font size used in the window.
    const int FONT_SIZE = 6;
    GButton *createButton;
    GButton *loadButton;
    GLabel *headerLabel;
    GLabel *sizeLabel;
    GChooser *sizeChooser;
    GContainer *contents;
    GWindow *window;
};

#endif // LOADCREATEGUI_H
