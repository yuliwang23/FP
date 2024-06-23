#ifndef FARMSCENE_HPP
#define FARMSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"

class Plant;
namespace Engine {
	class Group;
	class Image;
	class Label;
	class Sprite;
}  // namespace Engine

class FarmScene final : public Engine::IScene {
private:
	//ALLEGRO_SAMPLE_ID bgmId;
	//std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;
protected:
	//int lives;
	//int money;
	//int SpeedMult;
	FarmScene* getFarmScene();
public:
	enum TileType {
		TILE_DIRT,
		TILE_WHEAT,
		TILE_VEGETABLE,
        TILE_APPLE, 
        TILE_FLOWER
	};
	static const std::vector<Engine::Point> directions;
	static const int FieldWidth, FieldHeight;
	static const int MapWidth, MapHeight;
	static const int BlockSize;
	static const Engine::Point SpawnGridPoint;
	static const Engine::Point EndGridPoint;
	int FieldId;
	float ticks;
	// Map tiles.
	Group* TileFieldGroup;
	Group* GroundEffectGroup;
	Group* UIGroup;
	Group* PlantGroup;
	Group* EffectGroup;
	Group* UpGroup;
	Engine::Label* UIMoney;
	Engine::Image* imgTarget;
	Plant* preview;
	std::vector<std::vector<TileType>> fieldState;
	std::vector<std::vector<int>> mapDistance;
	std::vector<float> timeData;
	std::vector<float> timer;
	std::vector<bool> tf;
	static Engine::Point GetClientSize();
	explicit FarmScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
	void OnMouseUp(int button, int mx, int my) override;
	void EarnMoney(int money);
	int GetMoney();
	void ReadTime();
	void ReadField();
	void ConstructUI();
	void UIBtnClicked(int id);
	bool CheckSpaceValid(int x, int y);
	//std::vector<std::vector<int>> CalculateBFSDistance();
	void BackOnClick();
	void WritetoField();
	void WritetoTime();
	float getTimeData (int i, int j);
};
#endif // FARMSCENE_HPP