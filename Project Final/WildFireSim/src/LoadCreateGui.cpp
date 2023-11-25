#include "LoadCreateGui.h"

LoadCreateGui::LoadCreateGui()
{
    window = new GWindow(400, 300);
    window->setExitOnClose(false);
    const char *headerText = R""""(
Welcome to the Wildfire Simulator.
This simulation will demonstrate how a wildfile
spreads through an environment of fuel sources
including grass, young forest, and old forest.
Firefighting countermeasures have been deployed
in the simulated environment to slow the spread
of the fire, these countermeasures include fire
retardant and fire breaks.
)"""";
    headerLabel = new GLabel(headerText);
    sizeLabel = new GLabel("Size for new Map:");
    sizeChooser = new GChooser();
    sizeChooser->addItems({"16", "24", "32", "48", "64"});
    createButton = new GButton("&Create New Map txt");
    loadButton = new GButton("&Load Existing Map txt");
    contents = new GContainer(GContainer::LAYOUT_GRID, 3, 2);
    contents->addToGrid(headerLabel,0,0,1,2);
    contents->addToGrid(sizeLabel,1,0);
    contents->addToGrid(sizeChooser,1,1);
    contents->addToGrid(loadButton,2,0);
    contents->addToGrid(createButton,2,1);

    loadButton->setActionListener([this] {
        string fileName = GFileChooser::showOpenDialog();
        FireSimModel *model = new FireSimModel(fileName);
        FireSimGui *gui = new FireSimGui(model);
        this->window->close();
    });
    createButton->setActionListener([this] {
        string fileName = GFileChooser::showSaveDialog();
        NewMap nm(fileName, stoi(this->sizeChooser->getSelectedItem()));
        FireSimModel *model = new FireSimModel(fileName);
        FireSimGui *gui = new FireSimGui(model);
        this->window->close();
    });


    window->addToRegion(contents, sgl::GWindow::Region::REGION_CENTER);
    //window->pack();
}
