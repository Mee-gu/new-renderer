#include "DeviceMTL.h"
#include "CommandBufferMTL.h"
#include "BufferMTL.h"
#include "RenderPipelineMTL.h"
#include "ShaderModuleMTL.h"
#include "DepthStencilStateMTL.h"
#include "TextureMTL.h"
#include "BlendStateMTL.h"
#include "Utils.h"
#include "ProgramMTL.h"


CC_BACKEND_BEGIN

CAMetalLayer* DeviceMTL::_metalLayer = nil;
id<CAMetalDrawable> DeviceMTL::_currentDrawable = nil;

Device* Device::getInstance()
{
    if (!_instance)
        _instance = new (std::nothrow) DeviceMTL();

    return _instance;
}

void DeviceMTL::setCAMetalLayer(CAMetalLayer* metalLayer)
{
    DeviceMTL::_metalLayer = metalLayer;
//    Utils::createDefaultRenderPassDescriptor();
}

void DeviceMTL::updateDrawable()
{
    DeviceMTL::_currentDrawable = [DeviceMTL::_metalLayer nextDrawable];
    Utils::updateDefaultColorAttachmentTexture(DeviceMTL::_currentDrawable.texture);
}

DeviceMTL::DeviceMTL()
{
    _mtlDevice = DeviceMTL::_metalLayer.device;
    _mtlCommandQueue = [_mtlDevice newCommandQueue];
    ProgramCache::getInstance();
}

DeviceMTL::~DeviceMTL()
{
    ProgramCache::destroyInstance();
}

CommandBuffer* DeviceMTL::newCommandBuffer()
{
    return new (std::nothrow) CommandBufferMTL(this);
}

Buffer* DeviceMTL::newBuffer(uint32_t size, BufferType type, BufferUsage usage)
{
    return new (std::nothrow) BufferMTL(_mtlDevice, size, type, usage);
}

Texture* DeviceMTL::newTexture(const TextureDescriptor& descriptor)
{
    return new (std::nothrow) TextureMTL(_mtlDevice, descriptor);
}

DepthStencilState* DeviceMTL::createDepthStencilState(const DepthStencilDescriptor& descriptor)
{
    auto ret = new (std::nothrow) DepthStencilStateMTL(_mtlDevice, descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

BlendState* DeviceMTL::createBlendState(const BlendDescriptor& descriptor)
{
    auto ret = new (std::nothrow) BlendStateMTL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

RenderPipeline* DeviceMTL::newRenderPipeline(const RenderPipelineDescriptor& descriptor)
{
    return new (std::nothrow) RenderPipelineMTL(_mtlDevice, descriptor);
}

Program* DeviceMTL::createProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    auto program = ProgramCache::getInstance()->getProgram(vertexShader, fragmentShader);
    if(!program)
    {
        program = new (std::nothrow) ProgramMTL(_mtlDevice, vertexShader, fragmentShader);
        if (program)
        {
            program->autorelease();
            ProgramCache::getInstance()->addProgram(program);
        }
    }
    return program;
}

CC_BACKEND_END
