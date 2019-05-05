#include <iostream>

class IStream {
public:
    virtual void read() = 0;
};

class IStreamDerator : public IStream{
public:
    IStreamDerator(IStream *s) : stream(s) {}
protected:
    IStream *stream;
};

class FileStream : public IStreamDerator {
public:
    FileStream(IStream *s) : IStreamDerator(s) {}
    virtual void read() {
        if (stream != nullptr)
            stream->read();
        printf("File Stream Read.\n");
    }
};

class CrotStream : public IStreamDerator {
public:
    CrotStream(IStream *s) : IStreamDerator(s) {}
    virtual void read() {
        if (stream != nullptr)
            stream->read();
        printf("Crot Stream Read.\n");
    }
};


int main(int argc, char *argv[]) {
    IStream *f = new FileStream(nullptr);
    IStream *c = new CrotStream(f);
    IStream *ff = new FileStream(c);

    ff->read();

    return 0;
}