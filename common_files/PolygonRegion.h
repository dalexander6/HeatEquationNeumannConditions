//
//#####################################################################
//                       PolygonRegion.h 
//
//                     triangle region Class  
//
//
//	describes a triangle in 2d
//#####################################################################
//
//
#ifndef __PolygonRegion__
#define __PolygonRegion__

#include "Region.h"
#include "Point2D.h"
#include <cmath>

using namespace std;
class PolygonRegion : public Region
{
public:
	/** Pass in the vertices.  Must go CLOCKWISE!!!
	 * */
	PolygonRegion(vector<Point2D>& vertices) {
		this->vertices = vertices;
		
		//these are points perpendicular to line from v[i] to v[ip1]
		//thru v[i]
		for(unsigned int i = 0; i < vertices.size(); i++){
			int ip1 = (i+1) % vertices.size();
			double dx = vertices[i].getx() - vertices[ip1].getx();
			double dy = vertices[i].gety() - vertices[ip1].gety();
			double newx = vertices[i].getx() - dy;
			double newy = vertices[i].gety() + dx;
			
			perpPointsUp.push_back(Point2D(newx, newy));
		}

		//these are points perpendicular to line from v[i] to v[im1]
		//thru v[i]
		for(unsigned int i = 0; i < vertices.size(); i++){
			int im1 = (i-1) % vertices.size();
			double dx = vertices[i].getx() - vertices[im1].getx();
			double dy = vertices[i].gety() - vertices[im1].gety();
			double newx = vertices[i].getx() - dy;
			double newy = vertices[i].gety() + dx;
			
			perpPointsDown.push_back(Point2D(newx, newy));
		}
	}

	/** returns distance of v to line thru p1 and p2
	 */
	double distToLine(const Point2D& v,const  Point2D& p1,const  Point2D& p2) const{
		//use formula dist to ax + by + c = 0 is
		//|ax_0 + by_0 + c| / \sqrt{a^2 + b^2}

		double dx = p1.getx() - p2.getx();
		double dy = p1.gety() - p2.gety();
		double a = dy;
		double b = dx;
		double c = -p1.getx() * dy - p1.gety() * dx;
	
		return abs(a*v.getx() + b*v.gety() + c) / pow(a*a + b*b,2);
	}

	/** returns > 0 if p is to right of line thru v1 and v2
	 * < 0 if to left
	 * and 0 if on
	 * if line is horizontal, >0 if above
	 * and < 0 if below
	 */
	double edgeEqn(const Point2D& p, const Point2D& v1,const Point2D& v2) const{
		double dy = v1.gety() - v2.gety();
		double dx = v1.getx() - v2.getx();


		double e = (p.getx() - v1.getx())*dy - (p.gety() - v1.gety())*dx;
		if( dy > 0 ){
			return e;
		}
		else{
			return -e;
		}
	}
	virtual double distance(double v[]) const{
		Point2D vec(v[0],v[1]);
		return distance(vec);
	}

	virtual double distance(const Point2D& v) const{
		double bestDistance = -1; 
		//compute vi vs. edge(vi,vip1) vs. edge(vi,vim1)
		for(unsigned int i = 0; i < vertices.size(); i++){
			double currentDist = 0;

			//if to right of edge (vi,vip1), then closest to that edge
			if( edgeEqn(v, vertices[i], perpPointsUp[i]) > 0 ){
				currentDist = distToLine(v, vertices[i], perpPointsUp[i]);
			}
			//if to left of edge (vi, vim1), then closest to that edge
			else if(edgeEqn(v, vertices[i], perpPointsDown[i]) < 0){
				currentDist =  distToLine(v, vertices[i], perpPointsDown[i]);
			}
			//else, closest to vertex[i]
			else{
				currentDist = v.getDistance(vertices[i]);
			}

			if(i == 0){
				bestDistance = currentDist;
			}
			else{
				bestDistance = currentDist < bestDistance ? currentDist : bestDistance;
			}

		}
	return bestDistance;
	}

	vector<Point2D> vertices;
	vector<Point2D> perpPointsUp;
	vector<Point2D> perpPointsDown;

};

#endif
