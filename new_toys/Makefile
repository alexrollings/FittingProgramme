all:
	c++ -std=c++14 -O3 -march=native -Wall -Wextra -lTreePlayer -lFoam -lXMLIO -lRooFitCore -lRooFit -lMinuit `root-config --cflags --libs` CommonFunctions.cpp SimToy2D_SaveDataSet_old.cpp -o SimToy2D_SaveDataSet_old -lstdc++fs 
	c++ -std=c++14 -O3 -march=native -Wall -Wextra -lTreePlayer -lFoam -lXMLIO -lRooFitCore -lRooFit -lMinuit `root-config --cflags --libs` CommonFunctions.cpp SimToy1D_ReadDataSet_old.cpp -o SimToy1D_ReadDataSet_old -lstdc++fs 
