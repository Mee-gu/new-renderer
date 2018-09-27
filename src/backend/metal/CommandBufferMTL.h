#pragma once

#include "../CommandBuffer.h"
#include "DeviceMTL.h"

CC_BACKEND_BEGIN

class RenderPipelineMTL;

class CommandBufferMTL : public CommandBuffer
{
public:
    CommandBufferMTL(id<MTLDevice> mtlDevice);
    ~CommandBufferMTL();
    
    virtual void beginRenderPass(RenderPass* renderPass) override;
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) override;
    virtual void setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;
    virtual void setVertexBuffer(uint32_t index, Buffer* buffer) override;
    virtual void setBindGroup(BindGroup* bindGroup) override;
    virtual void setIndexBuffer(uint32_t index, Buffer* buffer) override;
    virtual void drawArrays(PrimitiveType primitiveType, uint32_t start,  uint32_t count) override;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, uint32_t count) override;
    virtual void endRenderPass() override;
    
private:
    id<MTLCommandBuffer> _mtlCommandBuffer = nil;
    id<MTLCommandQueue> _mtlCommandQueue = nil;
    id<MTLRenderCommandEncoder> _mtlRenderEncoder = nil;
    
    RenderPipelineMTL* _renderPipelineMTL = nullptr;
};

CC_BACKEND_END
