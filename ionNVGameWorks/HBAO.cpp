
#include "HBAO.h"

#include <ionGraphicsGL/CTexture.h>
#include <ionGraphicsGL/CFrameBuffer.h>
#include <GFSDK_SSAO.h>
#include <glm/gtc/type_ptr.hpp>


GFSDK_SSAO_GLFunctions ionGLFunctions();


namespace ion
{
	namespace Nvidia
	{

		void HBAO::Init()
		{
			GFSDK_SSAO_CustomHeap CustomHeap;
			CustomHeap.new_ = ::operator new;
			CustomHeap.delete_ = ::operator delete;

			GFSDK_SSAO_Status status;
			GFSDK_SSAO_GLFunctions functions = ionGLFunctions();
			status = GFSDK_SSAO_CreateContext_GL(&Context, &functions, &CustomHeap);
			assert(status == GFSDK_SSAO_OK);
		}

		void HBAO::Draw()
		{
			SharedPointer<ion::Graphics::GL::CTexture2D> DepthTextureRaw = std::dynamic_pointer_cast<ion::Graphics::GL::CTexture2D>(DepthTexture);

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

			GFSDK_SSAO_InputData_GL Input;
			Input.DepthData.DepthTextureType = GFSDK_SSAO_HARDWARE_DEPTHS;
			Input.DepthData.FullResDepthTexture.Target = GL_TEXTURE_2D;
			Input.DepthData.FullResDepthTexture.TextureId = DepthTextureRaw->Handle;
			Input.DepthData.ProjectionMatrix.Data = glm::value_ptr(Camera->GetProjectionMatrix());
			Input.DepthData.ProjectionMatrix.Layout = GFSDK_SSAO_ROW_MAJOR_ORDER;
			Input.DepthData.MetersToViewSpaceUnits = MetersToViewSpaceUnits;

			if (NormalTexture)
			{
				SharedPointer<ion::Graphics::GL::CTexture2D> NormalTextureRaw = std::dynamic_pointer_cast<ion::Graphics::GL::CTexture2D>(NormalTexture);

				Input.NormalData.Enable = true;
				Input.NormalData.FullResNormalTexture.Target = GL_TEXTURE_2D;
				Input.NormalData.FullResNormalTexture.TextureId = NormalTextureRaw->Handle;
				Input.NormalData.WorldToViewMatrix.Data = glm::value_ptr(Camera->GetViewMatrix());
				Input.NormalData.WorldToViewMatrix.Layout = GFSDK_SSAO_ROW_MAJOR_ORDER;
			}


			GFSDK_SSAO_Output_GL Output;
			if (FrameBuffer)
			{
				SharedPointer<ion::Graphics::GL::CFrameBuffer> FrameBufferRaw = std::dynamic_pointer_cast<ion::Graphics::GL::CFrameBuffer>(FrameBuffer);
				Output.OutputFBO = FrameBufferRaw->Handle;
			}

			GFSDK_SSAO_Status status;
			status = Context->RenderAO(Input, Params, Output);
		}

	}
}
