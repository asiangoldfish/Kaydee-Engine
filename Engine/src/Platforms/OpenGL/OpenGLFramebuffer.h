#pragma once

#include "Renderer/Framebuffer.h"

namespace Kaydee {
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFramebuffer();

        /**
         * @brief The framebuffer's state is invalid. It therefore needs to be
         * evaluated again.
         */
        void invalidate();

        virtual const FramebufferSpecification& getSpecification()
          const override
        {
            return specification;
        }

        void bind() override;
        void unbind() override;

        virtual uint32_t getColorAttachmentRendererID() const override
        {
            return colorAttachment;
        }

    private:
        uint32_t rendererID;
        uint32_t colorAttachment, depthAttachment;
        FramebufferSpecification specification;
    };
}