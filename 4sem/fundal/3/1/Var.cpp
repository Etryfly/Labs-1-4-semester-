


#include <string>
#include "MemoryCell.cpp"

class Var {
public:
    int size;
    std::string name;
    MemoryCell* memoryCell;
    bool operator < (const Var& b) const
    {
        return (memoryCell->ptr <= b.memoryCell->ptr);
    }

    Var(MemoryCell *m) {
        size = 0;
        memoryCell = m;
    }


};