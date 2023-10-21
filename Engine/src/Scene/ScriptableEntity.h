#pragma once

#include "Entity.h"

namespace Kaydee {
    /**
     * @brief Entity that is scriptable by the user
     */
    class ScriptableEntity
    {
    public:
        virtual ~ScriptableEntity() = default;

        template<typename T>
        T& getComponent()
        {
            return entity.getComponent<T>();
        }

    protected:
        virtual void onCreate() {}
        virtual void onDestroy() {}
        virtual void onUpdate(Timestep ts) {}

    private:
        friend class Scene;
        Entity entity;
    };
}