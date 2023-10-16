#pragma once

#include "Core/Core.h"

namespace Kaydee {
    /**
     * Allows specifying data for the framebuffer, like upscaling texture
     * resolution to the final window.
     */
    struct FramebufferSpecification
    {
        uint32_t width, height;
        // FramebufferFormat format = 
        uint32_t samples = 1;

        bool swapChainTarget = false; // Enables renderpasses
    };

    class Framebuffer
    {
    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual uint32_t getColorAttachmentRendererID() const = 0;

        virtual const FramebufferSpecification& getSpecification() const = 0;

        static ref<Framebuffer> create(const FramebufferSpecification& spec);
    };
}