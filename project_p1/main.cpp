#include <iostream>
#include <sys/types.h>
#include <sys/time.h>
#include "includes/Incremental.h"
#include "includes/ConvexHull.h"
#include "includes/Polygon.h"


using namespace std;

int main(int argc, char** argv)
{
    //Read arguments from user and check them
    string inputFileName,outputFileName,edgeSelection,algorithm,sort;
   
    inputFileName = argv[2];
    outputFileName = argv[4];
    algorithm = argv[6];
    edgeSelection = argv[8];
    sort = argv[10];



    if(algorithm != "incremental")
        algorithm = "incremental";

    //Allocate memory for polygon, depending on algorithm
    Polygon *polygon = NULL;
    if (algorithm == "incremental")
        polygon = new Incremental(inputFileName, sort);
    
    else if (algorithm == "convex_hull")
        polygon = new ConvexHull(inputFileName, algorithm);



    //Start timer
    timeval start;
    gettimeofday(&start, NULL);

    //Calculate result
    polygon->calculateResult();

    //Stop timer
    timeval stop;
    gettimeofday(&stop, NULL);

    //Print information
    polygon->printInfo(outputFileName);

    double elapsedTime = (stop.tv_sec - start.tv_sec) * 1000.0 + (stop.tv_usec - start.tv_usec) / 1000.0;
    cout << "construction time: " << (int)elapsedTime << endl;

    if (polygon)
        delete polygon;
    
    return 0;
}