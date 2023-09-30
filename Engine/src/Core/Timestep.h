#ifndef __TIMESTEP_H__
#define __TIMESTEP_H__

namespace Kaydee {
    class Timestep
    {
    public:
        Timestep(float time = 0.0f)
          : time(time)
        {
        }

        operator float() const { return time; }

        float getSeconds() const { return time; }
        float getMilliseconds() const { return time * 1000.f; }

        float getElapsedTimeInSeconds() const;
        float getElapsedTimeInMilliseconds() const;

    private:
        float time;
    };
}

#endif // __TIMESTEP_H__