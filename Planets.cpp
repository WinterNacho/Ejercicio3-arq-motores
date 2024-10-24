#include "MonaEngine.hpp"
#include "Rendering/DiffuseFlatMaterial.hpp"
#include "Utilities/BasicCameraControllers.hpp"

Mona::TransformHandle planet(Mona::World& world, auto& meshManager, float radius, glm::vec3 material) {
    auto planet = world.CreateGameObject<Mona::GameObject>();
    //float solRadius = 5.5f;
    Mona::TransformHandle planetTransform = world.AddComponent<Mona::TransformComponent>(planet, glm::vec3(0.0f, 0.0f, 0.0f));
    planetTransform->SetScale(glm::vec3(radius));
    auto Material = std::static_pointer_cast<Mona::DiffuseFlatMaterial>(world.CreateMaterial(Mona::MaterialType::DiffuseFlat));
    Material->SetDiffuseColor(material);
    world.AddComponent<Mona::StaticMeshComponent>(planet, meshManager.LoadMesh(Mona::Mesh::PrimitiveType::Sphere), Material);
    return planetTransform;
}

void worldSetup(Mona::World& world)
{
    Mona::GameObjectHandle<Mona::BasicPerspectiveCamera_2> m_camera = world.CreateGameObject<Mona::BasicPerspectiveCamera_2>();

    world.SetGravity(glm::vec3(0.0f, 0.0f, 0.0f));
    world.SetAmbientLight(glm::vec3(0.2f, 0.2f, 0.2f));
    world.SetAmbientLight(glm::vec3(4.0f));
    m_camera = world.CreateGameObject<Mona::BasicPerspectiveCamera_2>();
    //world.SetBackgroundColor(0.5, 0.2, 0.8);
    world.SetAmbientLight(glm::vec3(4.0f));
    world.SetMainCamera(world.GetComponentHandle<Mona::CameraComponent>(m_camera));
    Mona::SourceDirectoryData::SetSourceDirectory(".");
    world.AddComponent<Mona::DirectionalLightComponent>(m_camera, glm::vec3(10.0f, 10.0f, 0.0f));
}
class Planets : public Mona::Application
{
public:
	Planets() = default;
	~Planets() = default;
	virtual void UserStartUp(Mona::World &world) noexcept override{

        worldSetup(world);
        auto& meshManager = Mona::MeshManager::GetInstance();

        // sol
        Mona::TransformHandle solTransform = planet(world, meshManager, 5.5f, glm::vec3(0.10f, 0.1f, 0.1f));
        
        // planet 1
        m_planet1Transform = planet(world, meshManager, 2.5f, glm::vec3(0.75f, 0.5f, 0.3f));
        
        // planet 2
        m_planet2Transform = planet(world, meshManager, 3.5f, glm::vec3(0.75f, 0.5f, 0.3f));

	}

	virtual void UserShutDown(Mona::World& world) noexcept override {
	}

    float time =0,time2=0;
	virtual void UserUpdate(Mona::World& world, float timeStep) noexcept override {
        auto& input = world.GetInput();
        auto& window = world.GetWindow();

        time += timeStep;
        time2 += timeStep*1.2;
        float RPlanet1 = 25.0f;
        float RPlanet2 = 55.0f;
        float xp1 = RPlanet1 * cos(time), zp1 = RPlanet1 * sin(time);
        float xp2 = RPlanet2 * cos(time2), zp2 = RPlanet2 * sin(time2);

        m_planet1Transform->SetTranslation(glm::vec3(xp1, 0.0f, zp1));
        m_planet2Transform->SetTranslation(glm::vec3(xp2, 0.0f, zp2));

    }
private:
    Mona::TransformHandle m_transform;

    Mona::TransformHandle m_planet1Transform;
    glm::vec3 m_planet1Position;

    Mona::TransformHandle m_planet2Transform;
    glm::vec3 m_planet2Position;

    Mona::GameObjectHandle<Mona::BasicPerspectiveCamera_2> m_camera;
};
int main()
{	
	Planets app;
	Mona::Engine engine(app);
	engine.StartMainLoop();
	
}