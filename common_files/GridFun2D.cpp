#include "GridFun2D.h"

GridFun2D::GridFun2D(const GridParameters2D& grid) : values(grid.getXPanels()+1, grid.getYPanels()+1) {
	myGrid = grid.clone();

}

GridFun2D::GridFun2D(const GridFun2D& G){
	copy(G);
}

GridFun2D::~GridFun2D(){
	delete myGrid;
}

void GridFun2D::copy(const GridFun2D& G){
	myGrid = G.myGrid->clone();
	values = G.values;
}


GridFun2D GridFun2D::operator=(const GridFun2D& G){
	if(this != &G){
		delete myGrid;
		copy(G);
	}
	return *this;
}

GridFun2D GridFun2D::operator+=(const GridFun2D& G){
	for(long i = 0; i <= myGrid->getXPanels(); i++){
		for(long j = 0; j <= myGrid->getYPanels(); j++){
			values(i,j) += 1;//G(i,j);
		}
	}
	return *this;
}

GridFun2D GridFun2D::operator-=(const GridFun2D& G){
	for(long i = 0; i <= myGrid->getXPanels(); i++){
		for(long j = 0; j <= myGrid->getYPanels(); j++){
			values(i,j) -= G(i,j);
		}
	}
	return *this;
}


GridFun2D GridFun2D::operator*=(double alpha){
	for(long i = 0; i <= myGrid->getXPanels(); i++){
		for(long j = 0; j <= myGrid->getYPanels(); j++){
			values(i,j) *= alpha;
		}
	}
	return *this;
}


GridFun2D GridFun2D::operator/=(double alpha){
	for(long i = 0; i <= myGrid->getXPanels(); i++){
		for(long j = 0; j <= myGrid->getYPanels(); j++){
			values(i,j) /= alpha;
		}
	}
	return *this;
}

void GridFun2D::setToValue(double d){
	for(long i = 0; i <= myGrid->getXPanels(); i++){
		for(long j = 0; j <= myGrid->getYPanels(); j++){
			values(i,j) = d;
		}
	}
			return;
}

double GridFun2D::normInf(){
	double max = 0;
	for(long i = 0; i <= myGrid->getXPanels(); i++){
		for(long j = 0; j <= myGrid->getYPanels(); j++){
			if(abs(values(i,j)) > max){
				max = abs(values(i,j));
			}
		}
	}
	return max;
}

ostream& operator<<(ostream& outStream, const GridFun2D& G){
	long i; 
	for(i = 0; i <=  G.getXPanels(); i++){ 
		for(long j = 0; j <= G.getYPanels(); j++){
			outStream <<  setw(10) << G(i,j) << " ";
		}
		outStream << endl;
			
	}
	return outStream;
}

double& GridFun2D::operator()(int i, int j){
	assert(i >= 0 && i <= myGrid->getXPanels() );
	assert(j >= 0 && j <= myGrid->getYPanels() );
	
	return values(i,j);
}

const double GridFun2D::operator()(int i, int j) const{
	assert(i >= 0 && i <= myGrid->getXPanels() );// values.getIndex1Size());
	assert(j >= 0 && j <= myGrid->getYPanels() ); // values.getIndex2Size());
	
	return values(i,j);
}

