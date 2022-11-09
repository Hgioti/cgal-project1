#include <fstream>
#include "Polygon.h"
#include <sstream>
#include <string>
#include <fstream>

Polygon::Polygon(string inputFileName)
{

        std::ifstream infile(inputFileName);

        string name;
        int a,b,d;

        string line;
        while (std::getline(infile, line))
        {
            std::istringstream iss(line);

            if(line.at(0) != '#'){
                
                iss >> d;
                iss >> a >> b;
                initialPoints.push_back(Point_2(a,b));
            }
        }
}

void Polygon::printInfo(string output)
{
    ofstream myfile;
    myfile.open (output);

    for(const Point_2& p : initialPoints)
            myfile << p << std::endl;

    for(const Point_2& v : result.vertices())
           myfile << v << std::endl;


    for(const Segment_2& e  : result.edges())
           myfile << e << std::endl;

    myfile << "Incremental Algorithm" << std::endl;
    
    /*  Polygon area  */
    Polygon_2 p,chull;
    for(auto it = result.begin(); it!= result.end();++it)
            p.push_back(*it);
    myfile << "area " << p.area() << std::endl;

    /*   Ratio   */
    const Polygon_2::Vertices& range = result.vertices();
    vector<K::Point_2> cvector;

    CGAL::convex_hull_2(range.begin(), range.end(), std::back_inserter(cvector));
    for(auto it = cvector.begin(); it!= cvector.end();++it)
        chull.push_back(*it);
    myfile << "Ratio: " << (double)(p.area()/chull.area()) << std::endl;

    myfile.close();
}




bool Polygon::edgeVisible(const Segment_2& edge, Point_2 point,Polygon_2 pol)
{
           //Returns true if edge is visible from point:

            Segment_2 s1(point,edge.source());
            Segment_2 s2(point,edge.target());
            Segment_2 s3(point,CGAL::midpoint(edge));


            for(const Segment_2& e  : pol.edges()){

                     if(e!=edge){

                                 //if edge1 DOESN'T intersect with e OR if edge1 intersects with e and edge.source is not common point
                                const auto inter1 = intersection(e, s1);
                                if (inter1){

                                                  if(   (s1.target() != e.source()) && (s1.target() != e.target())      ){
                                                    //    std::cout << "intersection at start " << edge.source() << std::endl;
                                                        return false;
                                                  }                     
                                }

                                //if edge2 DOESN'T intersect with e OR if edge2 intersects with e and edge.target is not common point
                                const auto inter2 = intersection(e, s2);
                                if (inter2){

                                                if(     (s2.target() != e.source()) && (s2.target() != e.target())   ){
                                                        //    std::cout  << "intersection at end " << edge.target() << std::endl;
                                                            return false;
                                                }                                   
                                }

                                //if edge3 DOESN'T intersect with e
                                const auto inter3 = intersection(e, s3);
                                if (inter3){

                                               //    std::cout << "intersection at mid " << std::endl;
                                                   return false;
                                }
                     }
            }

    return true;
}

string Polygon::simpleOrNot()
{
    if (result.is_simple())
        return "Simple Polygon";
    else
        return "Not Simple Polygon";
}