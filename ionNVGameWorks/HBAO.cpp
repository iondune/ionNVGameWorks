
#include "HBAO.h"

#include <ionGraphicsD3D11/CTexture.h>
#include <ionGraphicsD3D11/CFrameBuffer.h>
#include <glm/gtc/type_ptr.hpp>

#ifdef ION_CONFIG_WINDOWS
#include <GFSDK_SSAO.h>
#endif


namespace ion
{
	namespace Nvidia
	{

		void HBAO::Init(IGraphicsImplementation * Implementation)
		{
			this->Implementation = Implementation;

#ifdef ION_CONFIG_WINDOWS

			GFSDK_SSAO_CustomHeap CustomHeap;
			CustomHeap.new_ = ::operator new;
			CustomHeap.delete_ = ::operator delete;

			Graphics::CD3D11Implementation * D3D11 = dynamic_cast<Graphics::CD3D11Implementation *>(Implementation);

			GFSDK_SSAO_Status status;
			status = GFSDK_SSAO_CreateContext_D3D11(D3D11->GetDevice(), & Context, & CustomHeap);
			assert(status == GFSDK_SSAO_OK);

#endif
		}

		void HBAO::Draw()
		{
#ifdef ION_CONFIG_WINDOWS
			SharedPointer<ion::Graphics::D3D11::CTexture2D> DepthTextureRaw = std::dynamic_pointer_cast<ion::Graphics::D3D11::CTexture2D>(DepthTexture);

			GFSDK_SSAO_Parameters Params;
			Params.Radius = Radius;
			Params.Bias = Bias;
			Params.PowerExponent = PowerExponent;

			Params.Blur.Enable = Blur;
			Params.Blur.Radius = GFSDK_SSAO_BLUR_RADIUS_4;
			Params.Blur.Sharpness = BlurSharpness;

			Params.ForegroundAO.Enable = ForegroundEnable;
			Params.ForegroundAO.ForegroundViewDepth = ForegroundViewDepth;

			Params.BackgroundAO.Enable = BackgroundEnable;
			Params.BackgroundAO.BackgroundViewDepth = BackgroundViewDepth;

			GFSDK_SSAO_InputData_D3D11 Input;
			Input.DepthData.DepthTextureType = GFSDK_SSAO_HARDWARE_DEPTHS;
			Input.DepthData.pFullResDepthTextureSRV = DepthTextureRaw->ShaderResourceView;
			Input.DepthData.ProjectionMatrix.Data = glm::value_ptr(Camera->GetProjectionMatrix());
			Input.DepthData.ProjectionMatrix.Layout = GFSDK_SSAO_ROW_MAJOR_ORDER;
			Input.DepthData.MetersToViewSpaceUnits = MetersToViewSpaceUnits;

			if (NormalTexture)
			{
				SharedPointer<ion::Graphics::D3D11::CTexture2D> NormalTextureRaw = std::dynamic_pointer_cast<ion::Graphics::D3D11::CTexture2D>(NormalTexture);

				Input.NormalData.Enable = true;
				Input.NormalData.pFullResNormalTextureSRV = NormalTextureRaw->ShaderResourceView;
				Input.NormalData.WorldToViewMatrix.Data = glm::value_ptr(Camera->GetViewMatrix());
				Input.NormalData.WorldToViewMatrix.Layout = GFSDK_SSAO_ROW_MAJOR_ORDER;
			}


			GFSDK_SSAO_Output_D3D11 Output;
			if (OutputTarget)
			{
				SharedPointer<ion::Graphics::D3D11::CRenderTarget> FrameBufferRaw = std::dynamic_pointer_cast<ion::Graphics::D3D11::CRenderTarget>(OutputTarget);
				Output.pRenderTargetView = FrameBufferRaw->RenderTargetViews[0];
				Output.Blend.Mode = GFSDK_SSAO_OVERWRITE_RGB;
			}


			Graphics::CD3D11Implementation * D3D11 = dynamic_cast<Graphics::CD3D11Implementation *>(Implementation);

			GFSDK_SSAO_Status status = Context->RenderAO(D3D11->GetImmediateContext(), Input, Params, Output);
			if (status != GFSDK_SSAO_OK)
			{
				Log::Error("RenderAO Failed.");
			}

#else
			if (FrameBuffer)
			{
				FrameBuffer->SetClearColor(color4f(1.0));
				FrameBuffer->ClearColor();
			}
#endif
		}

	}
}
