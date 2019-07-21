#ifndef PIZZADELIVERY_H_INCLUDED
#define PIZZADELIVERY_H_INCLUDED

class pizzadelivery
{
private:
    int x_position;
    int y_position;
    int cluster;
    pizzadelivery  *next;
public:
    pizzadelivery(int x_position,int y_position)
    {
        this->x_position = x_position;
        this->y_position = y_position;
    }
    int getcluster()
    {
        return cluster;
    }
    int getx()
    {
        return x_position;
    }
    int gety()
    {
        return y_position;
    }
    void setcluster(int cluster)
    {
        this->cluster = cluster;
    }
    void setnext(pizzadelivery *next)
    {
        this->next = next;
    }
    pizzadelivery* getnext()
    {
        return this->next;
    }
};


#endif // PIZZADELIVERY_H_INCLUDED
