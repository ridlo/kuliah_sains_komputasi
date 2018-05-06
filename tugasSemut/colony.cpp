#include <iostream>
#include <stdlib.h>
using namespace std;


class Map{
    public: 
        int length;
    private: 
        float[] mapVals;
        int mapW;
        int mapH;
        float MAXVAL = 100;
        float EVAPORATIONRATE = 0.999;

    Map (int w, int h){
        mapW = w;
        mapH = h;
        length = mapW*mapH;
        mapVals = new float[length];
        for (int i=0;i<mapVals.length;i++){
            mapVals[i] = 0.0;
        }
    }

    void step(){
        for (int i=0;i<mapVals.length;i++){
            mapVals[i] = mapVals[i]*EVAPORATIONRATE;
        }
    }

    /*void setValue(int x, int y, float val){
        try{
            int index = y*mapW + x;
            float oldVal = mapVals[index];
                mapVals[index] = (oldVal + val)/2;
            if (val > oldVal){
                mapVals[index] = val;
            }
        }
        //catch (Throwable t){
        //    return -1;
        //}
    }*/

    int[] getStrongest(int x, int y){
        float compare = 0;
        float strongestVal = 0;
        int[] strongest = {0, 0};
        compare = getValue(x-1, y-1);
        if (compare > strongestVal){ 
            strongest[0] = -1;
            strongest[1] = -1;
            strongestVal = compare;
        }
        compare = getValue(x, y-1);
        if (compare > strongestVal){ 
            strongest[0] = 0;
            strongest[1] = -1;
            strongestVal = compare;
        }
        compare = getValue(x+1, y-1);
        if (compare > strongestVal){ 
            strongest[0] = 1;
            strongest[1] = -1;
            strongestVal = compare;
        }
        compare = getValue(x-1, y);
        if (compare > strongestVal){ 
            strongest[0] = -1;
            strongest[1] = 0;
            strongestVal = compare;
        }
        compare = getValue(x+1, y);
        if (compare > strongestVal){ 
            strongest[0] = 1;
            strongest[1] = 0;
            strongestVal = compare;
        }
        compare = getValue(x-1, y+1);
        if (compare > strongestVal){ 
            strongest[0] = -1;
            strongest[1] = 1;
            strongestVal = compare;
        }
        compare = getValue(x, y+1);
        if (compare > strongestVal){ 
            strongest[0] = 0;
            strongest[1] = 1;
            strongestVal = compare;
        }
        compare = getValue(x+1, y+1);
        if (compare > strongestVal){ 
            strongest[0] = 1;
            strongest[1] = 1;
            strongestVal = compare;
        }        
        return strongest;
    }
}

int main(){
    cout << "Ants Colony\n";

    return 0;
}
