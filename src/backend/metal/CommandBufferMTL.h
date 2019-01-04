#pragma once

#include "../CommandBuffer.h"
#include "DeviceMTL.h"
#include <unordered_map>

CC_BACKEND_BEGIN

class RenderPipelineMTL;

class CommandBufferMTL : public CommandBuffer
{
public:
    CommandBufferMTL(DeviceMTL* deviceMTL);
    ~CommandBufferMTL();
    
    virtual void beginFrame() override;
    virtual void beginRenderPass(const RenderPassDescriptor& descriptor) override;
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) override;
    virtual void setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;
    virtual void setCullMode(CullMode mode) override;
    virtual void setVertexBuffer(uint32_t index, Buffer* buffer) override;
    virtual void setIndexBuffer(Buffer* buffer) override;
    virtual void drawArrays(PrimitiveType primitiveType, uint32_t start,  uint32_t count) override;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, uint32_t count) override;
    virtual void endRenderPass() override;
    virtual void endFrame() override;
    
private:
    void prepareDrawing() const;
    void setTextures() const;
    void doSetTextures(const std::vector<std::string>& textures, bool isVertex) const;
    void setUniformBuffer() const;
    void afterDraw();
    
    id<MTLCommandBuffer> _mtlCommandBuffer = nil;
    id<MTLCommandQueue> _mtlCommandQueue = nil;
    id<MTLRenderCommandEncoder> _mtlRenderEncoder = nil;
    id<MTLBuffer> _mtlIndexBuffer = nil;
    
    DeviceMTL* _deviceMTL = nullptr;
    RenderPipelineMTL* _renderPipelineMTL = nullptr;
    RenderPassDescriptor _renderPassDescriptor;
};

CC_BACKEND_END
