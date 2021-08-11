class Point{
private:
    int x,y;
    int neighbour;
public:
    int presence;
    bool visited;
    Point(int x,int y){
        this->x=x;
        this->y=y;
        this->visited=false;
        this->presence=-1;
    };
    Point(){}

    int getx(){
        return this->x;
    };
    
    int gety(){
        return this->y;
    };
};