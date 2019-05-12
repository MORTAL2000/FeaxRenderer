//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard 
//

#pragma once

struct D3D12_SAMPLER_DESC;
struct GraphicsContext;

namespace Graphics
{
    extern D3D12_SAMPLER_DESC SamplerLinearWrapDesc;
    extern D3D12_SAMPLER_DESC SamplerAnisoWrapDesc;
    extern D3D12_SAMPLER_DESC SamplerShadowDesc;
    extern D3D12_SAMPLER_DESC SamplerLinearClampDesc;
    extern D3D12_SAMPLER_DESC SamplerVolumeWrapDesc;
    extern D3D12_SAMPLER_DESC SamplerPointClampDesc;
    extern D3D12_SAMPLER_DESC SamplerPointBorderDesc;
    extern D3D12_SAMPLER_DESC SamplerLinearBorderDesc;

    extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerLinearWrap;
    extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerAnisoWrap;
    extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerShadow;
    extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerLinearClamp;
    extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerVolumeWrap;
    extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerPointClamp;
    extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerPointBorder;
    extern D3D12_CPU_DESCRIPTOR_HANDLE SamplerLinearBorder;

    extern D3D12_RASTERIZER_DESC RasterizerDefault;
    extern D3D12_RASTERIZER_DESC RasterizerDefaultMsaa;
    extern D3D12_RASTERIZER_DESC RasterizerDefaultCw;
    extern D3D12_RASTERIZER_DESC RasterizerDefaultCwMsaa;
    extern D3D12_RASTERIZER_DESC RasterizerTwoSided;
    extern D3D12_RASTERIZER_DESC RasterizerTwoSidedMsaa;
    extern D3D12_RASTERIZER_DESC RasterizerShadow;
    extern D3D12_RASTERIZER_DESC RasterizerShadowCW;
    extern D3D12_RASTERIZER_DESC RasterizerShadowTwoSided;

    extern D3D12_BLEND_DESC BlendNoColorWrite;        // XXX
    extern D3D12_BLEND_DESC BlendDisable;            // 1, 0
    extern D3D12_BLEND_DESC BlendPreMultiplied;        // 1, 1-SrcA
    extern D3D12_BLEND_DESC BlendTraditional;        // SrcA, 1-SrcA
    extern D3D12_BLEND_DESC BlendAdditive;            // 1, 1
    extern D3D12_BLEND_DESC BlendTraditionalAdditive;// SrcA, 1

    extern D3D12_DEPTH_STENCIL_DESC DepthStateDisabled;
    extern D3D12_DEPTH_STENCIL_DESC DepthStateReadWrite;
    extern D3D12_DEPTH_STENCIL_DESC DepthStateReadOnly;
    extern D3D12_DEPTH_STENCIL_DESC DepthStateReadOnlyReversed;
    extern D3D12_DEPTH_STENCIL_DESC DepthStateTestEqual;

	static const UINT FrameCount = 2;

	extern GraphicsContext Context;

    void InitializeCommonState(void);
    void DestroyCommonState(void);

	void ResourceBarrierBegin(GraphicsContext& context);
	void ResourceBarrierEnd(GraphicsContext& context);
}