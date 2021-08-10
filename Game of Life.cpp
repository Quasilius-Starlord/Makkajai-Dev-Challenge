#include <iostream>
#include <vector>
#include <string>

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

class World{
private:
    Point** worldgrid;
    int column,row;
    std::vector<Point> coordcollection;
    std::vector<Point> alive;

    int getmaxX(){
        int max=0;
        for (int i = 0; i < coordcollection.size(); i++){
            max=this->coordcollection[i].getx() > max ? this->coordcollection[i].getx() : max;
        }
        return max;
    };
    int getmaxY(){
        int max=0;
        for (int i = 0; i < coordcollection.size(); i++){
            max=this->coordcollection[i].gety() > max ? this->coordcollection[i].gety() : max;
        }
        return max;
    };

    int fordeadneighboutcount(int i, int j){
        int count=0;
        if(worldgrid[i][j].visited==true)
            return 0;
        worldgrid[i][j].visited=true;
        if(i>0){
            if(worldgrid[i-1][j].presence==1)
                count++;
            if(j>0){
                if(worldgrid[i-1][j-1].presence==1)
                    count++;
            }
            if(j<this->column-1){
                if(worldgrid[i-1][j+1].presence==1)
                    count++;
            }
        }
        if(i<row-1){
            if(worldgrid[i+1][j].presence==1)
                count++;
            if(j>0){
                if(worldgrid[i+1][j-1].presence==1)
                    count++;
            }
            if(j<this->column-1){
                if(worldgrid[i+1][j+1].presence==1)
                    count++;
            }
        }
        if(j>0){
            if(worldgrid[i][j-1].presence==1)
                count++;
        }
        if(j<this->column-1){
            if(worldgrid[i][j+1].presence==1)
                count++;
        }
        // std::cout << count << "\n";
        return count;
    };

    int neighbourcount(int i,int j){
        int count=0;
        if(worldgrid[i][j].visited==true)
            return 0;
        worldgrid[i][j].visited=true;
        // if(worldgrid[i][j])
        if(i>0){
            if(worldgrid[i-1][j].presence==1)
                count++;
            else{
                int c=this->fordeadneighboutcount(i-1,j);
                if(c==3)
                    this->alive.push_back(worldgrid[i-1][j]);
            }
            if(j>0){
                if(worldgrid[i-1][j-1].presence==1)
                    count++;
                else{
                    int c=this->fordeadneighboutcount(i-1,j-1);
                    if(c==3)
                        this->alive.push_back(worldgrid[i-1][j-1]);
                }
            }
            if(j<this->column-1){
                if(worldgrid[i-1][j+1].presence==1)
                    count++;
                else{
                    int c=this->fordeadneighboutcount(i-1,j+1);
                    if(c==3)
                        this->alive.push_back(worldgrid[i-1][j+1]);
                }
            }
        }
        if(i<row-1){
            if(worldgrid[i+1][j].presence==1)
                count++;
            else{
                int c=this->fordeadneighboutcount(i+1,j);
                if(c==3)
                    this->alive.push_back(worldgrid[i+1][j]);
            }
            if(j>0){
                if(worldgrid[i+1][j-1].presence==1)
                    count++;
                else{
                    int c=this->fordeadneighboutcount(i+1,j-1);
                    if(c==3)
                        this->alive.push_back(worldgrid[i+1][j-1]);
                }
            }
            if(j<this->column-1){
                if(worldgrid[i+1][j+1].presence==1)
                    count++;
                else{
                    int c=this->fordeadneighboutcount(i+1,j+1);
                    if(c==3)
                        this->alive.push_back(worldgrid[i+1][j+1]);
                }
            }
        }
        if(j>0){
            if(worldgrid[i][j-1].presence==1)
                count++;
            else{
                int c=this->fordeadneighboutcount(i,j-1);
                if(c==3)
                    this->alive.push_back(worldgrid[i][j-1]);
            }
        }
        if(j<this->column-1){
            if(worldgrid[i][j+1].presence==1)
                count++;
            else{
                int c=this->fordeadneighboutcount(i,j+1);
                if(c==3)
                    this->alive.push_back(worldgrid[i][j+1]);
            }
        }
        // std::cout << count << "\n";
        return count;
    }
public:
    World(){
        this->worldgrid=NULL;
    };

    ~World(){
        for (int i = 0; i < this->row; i++)
            delete[] worldgrid[i];
        delete[] worldgrid;
    }

    void worldgeneration(){
        int y=this->getmaxY()+2;
        int x=this->getmaxX()+2;
        this->row=x;
        this->column=y;
        worldgrid=new Point*[x];
        for (int i = 0; i < x; i++)
            worldgrid[i]=new Point[y];
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < y; j++)
            {
                this->worldgrid[i][j]=Point(i,j);
                this->worldgrid[i][j].presence=-1;
                this->worldgrid[i][j].visited=false;
            }
        }

        for (int i = 0; i < this->coordcollection.size(); i++)
            worldgrid[coordcollection[i].getx()][coordcollection[i].gety()].presence=1;;
    }

    void tict(){
        int count;
        for (int i = 0; i < this->coordcollection.size(); i++){
            count=this->neighbourcount(coordcollection[i].getx(),coordcollection[i].gety());
            if(count>=2 && count<=3){
                this->alive.push_back(coordcollection[i]);
            }
        }
    }

    void addPoint(int x,int y){
        this->coordcollection.push_back(Point(x,y));
    }

    void printcoords(std::string s){
        std::cout << s << "\n";
        for (int i = 0; i < this->alive.size(); i++)
        {
            std::cout << alive[i].getx() << ", " << alive[i].gety() << "\n";
        }
    }
};

int main(){
    //block pattern
    World block;
    std::vector<std::vector<int>> blockstore={{1,1},{1,2},{2,1},{2,2}};
    std::cout << "Input A\nBlock Pattern\n";
    for (int i = 0; i < blockstore.size(); i++)
    {
        std::cout << blockstore[i][0] << ", " << blockstore[i][1] << "\n";
        block.addPoint(blockstore[i][0],blockstore[i][1]);
    }
    block.worldgeneration();
    block.tict();
    block.printcoords("Output A");

    //boat pattern
    World boat;
    std::vector<std::vector<int>> boatstore={{0,1},{1,0},{2,1},{0,2},{1,2}};
    std::cout << "Input B\nBoat Pattern\n";
    for (int i = 0; i < boatstore.size(); i++)
    {
        std::cout << boatstore[i][0] << ", " << boatstore[i][1] << "\n";
        boat.addPoint(boatstore[i][0],boatstore[i][1]);
    }
    boat.worldgeneration();
    boat.tict();
    boat.printcoords("Output B");
    
    //blinker pattern
    World blinker;
    std::vector<std::vector<int>> blinkerstore={{1,1},{1,0},{1,2}};
    std::cout << "Input C\nBlinker Pattern\n";
    for (int i = 0; i < blinkerstore.size(); i++)
    {
        std::cout << blinkerstore[i][0] << ", " << blinkerstore[i][1] << "\n";
        blinker.addPoint(blinkerstore[i][0],blinkerstore[i][1]);
    }
    blinker.worldgeneration();
    blinker.tict();
    blinker.printcoords("Output C");
    
    World toad;
    std::vector<std::vector<int>> toadstore={{1,1},{1,2},{1,3},{2,2},{2,3},{2,4}};
    std::cout << "Input D\ntoad Pattern\n";
    for (int i = 0; i < toadstore.size(); i++)
    {
        std::cout << toadstore[i][0] << ", " << toadstore[i][1] << "\n";
        toad.addPoint(toadstore[i][0],toadstore[i][1]);
    }
    toad.worldgeneration();
    toad.tict();
    toad.printcoords("Output D");
}