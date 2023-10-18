#pragma once

#include "Renderer/Framebuffer.h"

namespace Kaydee {
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFramebuffer();

        virtual void resize(uint32_t width, uint32_t height);

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
        uint32_t rendererID = 0;
        uint32_t colorAttachment = 0, depthAttachment = 0;
        FramebufferSpecification specification;
    };
}