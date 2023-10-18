#include <Kaydee/Kaydee.h>
#include "EditorLayer.h"

namespace Kaydee {
    class KaydeeEditor : public Application
    {
    public:
        KaydeeEditor()
          : Application("Kaydee Editor")
        {
            pushLayer(new EditorLayer());
        }

        virtual ~KaydeeEditor() {}
    };

    Application* createApplication()
    {
        return new KaydeeEditor();
    }
}
