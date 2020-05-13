
class MemoryCell {
public:
    int links;
    char* ptr;

    MemoryCell(char* ptr) {
        links = 1;
        this->ptr = ptr;
    }

    MemoryCell& operator = (MemoryCell m) {
        this->links = m.links;
        ptr = m.ptr;
        return *this;
    }
};