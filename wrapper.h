#ifndef WRAPPER_H
#define WRAPPER_H

#include <iostream>
#include <unistd.h>
using namespace std;

class DesWrapper {
public:
    DesWrapper(int d = -1) : descriptor_(d) {}
    ~DesWrapper() {
        if (descriptor_ > 0) {
            close(descriptor_);
            cout << "descriptor " << descriptor_ << " closed success..."
                 << endl;
        }
    }

    int get() {
        return descriptor_;
    }

private:
    int descriptor_;
};

#endif 