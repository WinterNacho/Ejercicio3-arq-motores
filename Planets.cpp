#include "MonaEngine.hpp"

void CreateBasicCameraWithMusicAndLight(Mona::World& world)
{
	auto camera = world.CreateGameObject<Mona::GameObject>();
	auto transform = world.AddComponent<Mona::TransformComponent>(camera, glm::vec3(0.0f, 12.0f, 40.0f));
	transform->Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 1.57f);
	world.SetMainCamera(world.AddComponent<Mona::CameraComponent>(camera));
	world.SetAudioListenerTransform(transform);
	auto& audioClipManager = Mona::AudioClipManager::GetInstance();
	Mona::SourceDirectoryData::SetSourceDirectory("C:/Proyectos/cpp/MonaEngineProject/assets/");
	auto audioClipPtr = audioClipManager.LoadAudioClip(Mona::SourceDirectoryData::SourcePath("audio/mewmew.wav"));
	auto audioSource = world.AddComponent<Mona::AudioSourceComponent>(camera, audioClipPtr);
	audioSource->SetIsLooping(true);
	audioSource->SetVolume(0.3f);
	audioSource->Play();

	world.AddComponent<Mona::DirectionalLightComponent>(camera, glm::vec3(1.0f));

}
class Planets : public Mona::Application
{
public:
	Planets() = default;
	~Planets() = default;
	virtual void UserStartUp(Mona::World &world) noexcept override{
        world.SetGravity(glm::vec3(0.0f, 0.0f, 0.0f));
        world.SetAmbientLight(glm::vec3(0.2f, 0.2f, 0.2f));
        CreateBasicCameraWithMusicAndLight(world);
	}

	virtual void UserShutDown(Mona::World& world) noexcept override {
	}
	virtual void UserUpdate(Mona::World& world, float timeStep) noexcept override {
	}
};
int main()
{	
	Planets app;
	Mona::Engine engine(app);
	engine.StartMainLoop();
	
}