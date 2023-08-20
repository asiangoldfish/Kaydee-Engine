#ifndef __GRAPHICS_CONTEXT_H__
#define __GRAPHICS_CONTEXT_H__

class GraphicsContext
{
public:
    virtual void init() = 0;
    virtual void swapBuffers() = 0;

private:
};

#endif