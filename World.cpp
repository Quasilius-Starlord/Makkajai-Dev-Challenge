#include <vector>
#include "Point.cpp"

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
public:
    World(std::vector<std::vector<int>>& vec){
        this->worldgrid=NULL;
        for (int i = 0; i < vec.size(); i++){
            std::cout << vec[i][0] << ", " << vec[i][1] << "\n";
            this->addPoint(vec[i][0],vec[i][1]);
        }
        this->worldgeneration();
    };

    ~World(){
        for (int i = 0; i < this->row; i++)
            delete[] worldgrid[i];
        delete[] worldgrid;
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
