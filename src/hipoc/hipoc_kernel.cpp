
#include <mlopen/hipoc_kernel.hpp>
#include <mlopen/errors.hpp>

namespace mlopen {

void HIPOCKernelInvoke::run(void* args, std::size_t size) const
{
    void *config[] = {
        HIP_LAUNCH_PARAM_BUFFER_POINTER, args,
        HIP_LAUNCH_PARAM_BUFFER_SIZE, &size,
        HIP_LAUNCH_PARAM_END
    };

    auto status = hipModuleLaunchKernel(fun, gdims[0], gdims[1], gdims[2], ldims[0], ldims[1], ldims[2], 0, stream, nullptr, (void**)&config);
    if(status != hipSuccess) MLOPEN_THROW_HIP_STATUS(status, "Failed to launch kernel");
}

HIPOCKernelInvoke HIPOCKernel::Invoke(hipStream_t stream)
{
    return HIPOCKernelInvoke{stream, fun, ldims, gdims};
}
}