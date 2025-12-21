#ifndef POSITION_H
#define POSITION_H

class Position {
    public:
        int row;
        int column;
    
        Position(int, int);
    
        void setPosition(int, int);
    
        bool operator==(const Position&) const;
    
        bool operator!=(const Position&) const;
    };

#endif // POSITION_H