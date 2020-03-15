#ifndef CABINET_H
#define CABINET_H


class Cabinet
{
private:
    static bool validation(int id, int number, int floor, int building);
public:
    int id;
    int number;
    int floor;
    int building;

    Cabinet(int id, int number, int floor, int building);
    ~Cabinet();
};

#endif // CABINET_H
