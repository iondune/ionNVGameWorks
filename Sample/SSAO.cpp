
#include <ionWindow.h>
#include <ionGraphics.h>
#include <ionGraphicsGL.h>
#include <ionScene.h>
#include <ionApplication.h>
#include <ionGUI.h>
#include <ionNvidiaGameWorks.h>

#include <random>

using namespace ion;
using namespace ion::Scene;
using namespace ion::Graphics;


float lerp(float const a, float const b, float const f)
{
	return a + f * (b - a);
}

int main()
{
	////////////////////
	// ionEngine Init //
	////////////////////

	Log::AddDefaultOutputs();

	SingletonPointer<CGraphicsAPI> GraphicsAPI;
	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CTimeManager> TimeManager;
	SingletonPointer<CSceneManager> SceneManager;
	SingletonPointer<CAssetManager> AssetManager;
	SingletonPointer<CGUIManager> GUIManager;
	SingletonPointer<ion::Nvidia::HBAO> HBAO;


	GraphicsAPI->Init(new Graphics::COpenGLImplementation());
	WindowManager->Init(GraphicsAPI);
	TimeManager->Init(WindowManager);
	SceneManager->Init(GraphicsAPI);
	AssetManager->Init(GraphicsAPI);

	CWindow * Window = WindowManager->CreateWindow(vec2i(1600, 900), "Nvidia GameWorks HABO+ ionEngine Sample", EWindowType::Windowed);

	GUIManager->Init(Window);

	AssetManager->AddAssetPath("Assets/");
	AssetManager->SetShaderPath("Shaders/");
	AssetManager->SetTexturePath("Images/");

	SharedPointer<IGraphicsContext> Context = GraphicsAPI->GetWindowContext(Window);
	SharedPointer<IRenderTarget> BackBuffer = Context->GetBackBuffer();
	BackBuffer->SetClearColor(color3f(0.3f));

	HBAO->Init();

	SharedPointer<IFrameBuffer> FrameBuffer = Context->CreateFrameBuffer();

	SharedPointer<ITexture2D> SceneColor = GraphicsAPI->CreateTexture2D(Window->GetSize(), ITexture::EMipMaps::False, ITexture::EFormatComponents::RGB, ITexture::EInternalFormatType::Fix8);
	SceneColor->SetMinFilter(ITexture::EFilter::Nearest);
	SceneColor->SetMagFilter(ITexture::EFilter::Nearest);
	SceneColor->SetWrapMode(ITexture::EWrapMode::Clamp);
	SharedPointer<ITexture2D> ScenePosition = GraphicsAPI->CreateTexture2D(Window->GetSize(), ITexture::EMipMaps::False, ITexture::EFormatComponents::RGBA, ITexture::EInternalFormatType::Float16);
	ScenePosition->SetMinFilter(ITexture::EFilter::Nearest);
	ScenePosition->SetMagFilter(ITexture::EFilter::Nearest);
	ScenePosition->SetWrapMode(ITexture::EWrapMode::Clamp);
	SharedPointer<ITexture2D> SceneNormal = GraphicsAPI->CreateTexture2D(Window->GetSize(), ITexture::EMipMaps::False, ITexture::EFormatComponents::RGB, ITexture::EInternalFormatType::Float16);
	SceneNormal->SetMinFilter(ITexture::EFilter::Nearest);
	SceneNormal->SetMagFilter(ITexture::EFilter::Nearest);
	SceneNormal->SetWrapMode(ITexture::EWrapMode::Clamp);
	SharedPointer<ITexture2D> SceneDepth = GraphicsAPI->CreateTexture2D(Window->GetSize(), ITexture::EMipMaps::False, ITexture::EFormatComponents::R, ITexture::EInternalFormatType::Depth);
	FrameBuffer->AttachColorTexture(SceneColor, 0);
	FrameBuffer->AttachColorTexture(ScenePosition, 1);
	FrameBuffer->AttachColorTexture(SceneNormal, 2);
	FrameBuffer->AttachDepthTexture(SceneDepth);
	if (! FrameBuffer->CheckCorrectness())
	{
		Log::Error("Frame buffer not valid!");
	}


	/////////////////
	// Load Assets //
	/////////////////

	CSimpleMesh * SphereMesh = CGeometryCreator::CreateSphere();
	CSimpleMesh * PlaneMesh = CGeometryCreator::CreatePlane(vec2f(100.f));

	SharedPointer<IShaderProgram> GeometryShader = AssetManager->LoadShader("Geometry");
	SharedPointer<IShaderProgram> QuadCopyShader = AssetManager->LoadShader("QuadCopy");


	////////////////////
	// ionScene Setup //
	////////////////////

	CRenderPass * RenderPass = new CRenderPass(Context);
	RenderPass->SetRenderTarget(FrameBuffer);
	SceneManager->AddRenderPass(RenderPass);

	CPerspectiveCamera * Camera = new CPerspectiveCamera(Window->GetAspectRatio());
	Camera->SetPosition(vec3f(0, 3, -5));
	Camera->SetFocalLength(0.4f);
	Camera->SetNearPlane(0.1f);
	Camera->SetFarPlane(5000.f);
	RenderPass->SetActiveCamera(Camera);


	CCameraController * Controller = new CCameraController(Camera);
	Controller->SetTheta(15.f * Constants32::Pi / 48.f);
	Controller->SetPhi(-Constants32::Pi / 16.f);
	Window->AddListener(Controller);
	TimeManager->MakeUpdateTick(0.02)->AddListener(Controller);


	/////////////////
	// Add Objects //
	/////////////////

	CSimpleMeshSceneObject * Sphere1 = new CSimpleMeshSceneObject();
	Sphere1->SetMesh(SphereMesh);
	Sphere1->SetShader(GeometryShader);
	Sphere1->SetPosition(vec3f(0, 0, 0));
	Sphere1->SetScale(2.f);
	Sphere1->GetMaterial().Diffuse *= color3f(1.0, 0.8f, 0.8f);
	RenderPass->AddSceneObject(Sphere1);

	CSimpleMeshSceneObject * Sphere2 = new CSimpleMeshSceneObject();
	Sphere2->SetMesh(SphereMesh);
	Sphere2->SetShader(GeometryShader);
	Sphere2->SetPosition(vec3f(4, 0, 0));
	Sphere2->SetScale(3.f);
	Sphere2->GetMaterial().Diffuse *= color3f(0.8f, 1, 0.8f);
	RenderPass->AddSceneObject(Sphere2);

	CSimpleMeshSceneObject * Sphere3 = new CSimpleMeshSceneObject();
	Sphere3->SetMesh(SphereMesh);
	Sphere3->SetShader(GeometryShader);
	Sphere3->SetPosition(vec3f(12, 0, 0));
	Sphere3->SetScale(4.f);
	Sphere3->GetMaterial().Diffuse *= color3f(0.8f, 0.9f, 1);
	RenderPass->AddSceneObject(Sphere3);

	CSimpleMeshSceneObject * Sphere4 = new CSimpleMeshSceneObject();
	Sphere4->SetMesh(SphereMesh);
	Sphere4->SetShader(GeometryShader);
	Sphere4->SetPosition(vec3f(3, 0, 6));
	Sphere4->GetMaterial().Diffuse *= color3f(0.9f, 1, 1);
	RenderPass->AddSceneObject(Sphere4);

	vector<CSimpleMesh *> Meshes = CGeometryCreator::LoadOBJFile("terrain.obj");
	for (auto Mesh : Meshes)
	{
		CSimpleMeshSceneObject * PlaneObject = new CSimpleMeshSceneObject();
		PlaneObject->SetMesh(Mesh);
		PlaneObject->SetShader(GeometryShader);
		RenderPass->AddSceneObject(PlaneObject);
	}

	CPointLight * Light1 = new CPointLight();
	Light1->SetPosition(vec3f(0, 6, 0));
	RenderPass->AddLight(Light1);

	HBAO->DepthTexture = SceneDepth;
	HBAO->Camera = Camera;
	HBAO->MetersToViewSpaceUnits = 3.28084f;


	///////////////
	// Main Loop //
	///////////////

	TimeManager->Init(WindowManager);
	while (WindowManager->Run())
	{
		TimeManager->Update();

		GUIManager->NewFrame();
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiSetCond_Once);
		if (ImGui::Begin("Settings"))
		{
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Camera position: %.3f %.3f %.3f", Camera->GetPosition().X, Camera->GetPosition().Y, Camera->GetPosition().Z);
			ImGui::Text("Camera rotation: %.3f %.3f", Controller->GetTheta(), Controller->GetPhi());

			ImGui::Separator();

			ImGui::Text("HBAO+ Params");

			ImGui::SliderFloat("Radius", &HBAO->Radius, 0.5f, 6.f);
			ImGui::SliderFloat("Bias", &HBAO->Bias, 0.0f, 1.f);
			ImGui::SliderFloat("Power", &HBAO->PowerExponent, 0.1f, 4.f);
			ImGui::Checkbox("Blur", &HBAO->Blur);
			ImGui::SliderFloat("Blur.Sharpness", &HBAO->BlurSharpness, 0.0f, 16.f);

			ImGui::End();
		}

		FrameBuffer->ClearColorAndDepth();
		BackBuffer->ClearColorAndDepth();

		SceneManager->DrawAll();
		BackBuffer->Bind();

		HBAO->Draw();

		GUIManager->Draw();
		Window->SwapBuffers();
	}

	return 0;
}
