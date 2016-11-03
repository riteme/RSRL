//
// Copyright 2016 riteme
//

#ifndef RSRL_TEXTURE_H_
#define RSRL_TEXTURE_H_

#include "Defs.h"

class Texture {
    Texture(const size_t width, const size_t height);

    UB

        protected : UByte *_memory;
};

#endif
