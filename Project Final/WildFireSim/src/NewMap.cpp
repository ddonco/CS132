#include "NewMap.h"

NewMap::NewMap(string fileName, int size) {
    srand(time(0));

    PerlinNoise pn = PerlinNoise(time(0));

    ofstream mapFile;
    mapFile.open(fileName, ios::trunc);
    mapFile << size << endl;

    int zoomFactor = size/4;
    int fireX = rand()%(size - 1);
    int fireY = rand()%(size - 1);

    for(int y = 0; y < size; y++) {
        for(int x = 0; x < size; x++) {
            if ((x == fireX || x == fireX + 1) &&
                (y == fireY || y == fireY + 1)) {
                mapFile << "FI";//fire
            } else if (false) {

            } else {
                double noiseVal = pn.valAtPos(x, y, zoomFactor);
                if (noiseVal < 0.53)
                    mapFile << "GS";//grass
                else if (noiseVal < 0.65)
                    mapFile << "YF";//Young Forest
                else
                    mapFile << "OF";//old forest
            }
            if (x < size - 1)
                mapFile << " ";
        }
        if (y < size - 1)
            mapFile << endl;
    }
    mapFile.close();

}
