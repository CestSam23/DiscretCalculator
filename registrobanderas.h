#ifndef REGISTROBANDERAS_H
#define REGISTROBANDERAS_H


class RegistroBanderas{

private:
    bool oneClickArrow;
    bool twoClickArrow;
    bool changesOnVertices;

public:
    RegistroBanderas();
    bool getOneClickArrow();
    bool getTwoClickArrow();
    bool getChangesOnVertices();
    void setOneClickArrow(bool oneClickArrow);
    void setTwoClickArrow(bool twoClickArrow);
    void setChangesOnVertices(bool changesOnVertices);



};

#endif // REGISTROBANDERAS_H
