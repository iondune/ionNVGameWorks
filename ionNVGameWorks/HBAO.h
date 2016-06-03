
#pragma once

#include <ionEngine.h>


class GFSDK_SSAO_Context_GL;

namespace ion
{
	namespace Nvidia
	{

		class HBAO : public Singleton<HBAO>
		{

		public:

			void Init();
			void Draw();

			SharedPointer<ion::Graphics::ITexture2D> DepthTexture;
			ion::Scene::CPerspectiveCamera * Camera = nullptr;

			float Radius = 2.f;
			float Bias = 0.1f;
			float PowerExponent = 2.f;
			bool Blur = true;
			float BlurSharpness = 16.f;
			float MetersToViewSpaceUnits = 1.f;

		protected:

			GFSDK_SSAO_Context_GL * Context = nullptr;

		};

	}
}
