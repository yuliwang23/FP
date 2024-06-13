#include <allegro5/allegro.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <vector>
#include <queue>
#include <string>
#include <memory>

#include "Engine/AudioHelper.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "UI/Component/Label.hpp"
#include "Engine/Resources.hpp"

#include "Scene/FarmScene.hpp"
#include "Plant/Plant.hpp"
#include "Plant/PlantButton.hpp"
#include "Plant/WheatPlant.hpp"
#include "Plant/VegetablePlant.hpp"
#include "Plant/ApplePlant.hpp"
#include "Plant/FlowerPlant.hpp"

#include <iostream>
#include <fstream>
using namespace std;

const int FarmScene::FieldWidth = 3, FarmScene::FieldHeight = 3;
const int FarmScene::MapWidth = 20, FarmScene::MapHeight = 13;
const int FarmScene::BlockSize = 64;
const Engine::Point FarmScene::SpawnGridPoint = Engine::Point(-1, 0);
const Engine::Point FarmScene::EndGridPoint = Engine::Point(FieldWidth, FieldHeight - 1);
Engine::Point FarmScene::GetClientSize() {
	return Engine::Point(FieldWidth * BlockSize, FieldHeight * BlockSize);
}
int First;

void FarmScene::Initialize() {
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
	//cout << "!!!" << endl;
    fieldState.clear();
    ticks = 0;
    AddNewObject(TileFieldGroup = new Group());
	AddNewObject(GroundEffectGroup = new Group());
	AddNewObject(PlantGroup = new Group());
	AddNewObject(EffectGroup = new Group());
	AddNewControlObject(UIGroup = new Group());
	ReadField();
	ReadTime();
    ConstructUI(); 
	imgTarget = new Engine::Image("play/target.png", 0, 0);
	imgTarget->Visible = false;
	preview = nullptr;
	UIGroup->AddNewObject(imgTarget);

	if (First) {
		First = 0;
		//al_create_timer();
	} else {
		//al_stop_timer();
	}

	if (FieldId == 1) {
		AddNewObject(new Engine::Label("Player 1", "pirulen.ttf", 38, 1320, 48));
	} else {
		AddNewObject(new Engine::Label("Player 2", "pirulen.ttf", 38, 1320, 48));
	}

	Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 1310, halfH + 270 , 260, 90);
    btn->SetOnClickCallback(std::bind(&FarmScene::BackOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 46, 1445, halfH + 315, 0, 0, 0, 255, 0.5, 0.5));
}
void FarmScene::Terminate() {
	//AudioHelper::StopBGM(bgmId);
	//AudioHelper::StopSample(deathBGMInstance);
	//deathBGMInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void FarmScene::Update(float deltaTime) {


}

void FarmScene::BackOnClick() {
	//al_start_timer();
	WritetoField();
	WritetoTime();
	Engine::GameEngine::GetInstance().ChangeScene("farm-select");
}

void FarmScene::WritetoField() {
	std::ofstream fout;
	string filename = string("Resource/farmfield") + std::to_string(FieldId) + ".txt";
	/*if (fout.good()) {
		remove();
	}*/
	fout.open(filename);
	cout << "Write1" << endl;
	//刪掉裡面的資料

	char c;
	for (int i = 0; i < FieldWidth; i++) {
		for (int j = 0; j < FieldHeight; j++) {
			switch (fieldState[i][j]) {
				case TILE_DIRT: c = 'd'; break;
				case TILE_WHEAT: c = 'w'; break;
				case TILE_VEGETABLE: c = 'v'; break;
				case TILE_APPLE: c = 'a'; break;
				case TILE_FLOWER: c = 'f'; break;
			}
			fout << c;
			cout << "Write2" << endl;
		}
		fout << '\n';
	}
	cout << "Write3" << endl;
	fout.close();
	cout << "Write4" << endl;
}
void FarmScene::WritetoTime() {
	std::ofstream fout;
	string filename = string("Resource/farmfield") + std::to_string(FieldId) + ".txt";
	fout.open(filename);
	cout << "Write1" << endl;
	//刪掉
	char c;
	for (int i = 0; i < FieldWidth; i++) {
		for (int j = 0; j < FieldHeight; j++) {
			switch (fieldState[i][j]) {
				case TILE_DIRT: c = 'd'; break;
				case TILE_WHEAT: c = 'w'; break;
				case TILE_VEGETABLE: c = 'v'; break;
				case TILE_APPLE: c = 'a'; break;
				case TILE_FLOWER: c = 'f'; break;
			}
			fout << c;
			cout << "Write2" << endl;
		}
		fout << '\n';
	}
	cout << "Write3" << endl;
	fout.close();
	cout << "Write4" << endl;

}

void FarmScene::Draw() const {
	IScene::Draw();
	/*if (FieldId) {
		for (int i = 0; i < FieldHeight; i++) {
			for (int j = 0; j < FieldWidth; j++) {
				// Not elegant nor efficient, but it's quite enough for debugging.
				Engine::Label label(std::to_string(mapDistance[i][j]), "pirulen.ttf", 32, (j + 0.5) * BlockSize, (i + 0.5) * BlockSize);
				label.Anchor = Engine::Point(0.5, 0.5);
				label.Draw();
			}
		}
	}*/
}

void FarmScene::ReadTime() {
    std::string filename = std::string("Resource/farmtime") + std::to_string(FieldId) + ".txt";
	// Read time file.
	float time;
	timeData.clear();
	std::ifstream fin(filename);
	while (fin >> time) {
		timeData.emplace_back(time);
	}
	fin.close();
}

void FarmScene::ReadField() {
	string filename = string("Resource/farmfield") + std::to_string(FieldId) + ".txt";
	// Read field file.
	char c;
	std::vector<char> fieldData;
	std::ifstream fin(filename);
	cout << "!" << endl;
    while (fin >> c) {
		cout << "!!" << endl;
		switch (c) {
		case 'd': {
			fieldData.push_back('0');
			break;
		} 
		case 'w': fieldData.push_back('1'); break;
		case 'v': fieldData.push_back('2'); break;
		case 'a': fieldData.push_back('3'); break;
		case 'f': fieldData.push_back('4'); break;
		case '\n':
		case '\r':
			//if (static_cast<int>(fieldData.size()) / Width != 0)
				//throw std::ios_base::failure("Map data is corrupted.");
			break;
		default: throw std::ios_base::failure("Map data is corrupted.");
		}
    } 
	fin.close();

	cout << "size: " << fieldData.size() << endl;
	for(int a = 0; a < fieldData.size(); a++) {
		cout << fieldData[a] << " ";
	}
	cout << endl;

	// Validate field data.
	if (static_cast<int>(fieldData.size()) != FieldWidth * FieldHeight)
		throw std::ios_base::failure("Map data is corrupted!");

	// Store field in 2d array.
	fieldState = vector<vector<TileType>>(FieldHeight, vector<TileType>(FieldWidth));
	cout << "MapHeight: " << MapHeight << endl;
	cout << "MapWidth: " << MapWidth << endl;
	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			const char type = fieldData[i * FieldWidth + j];
			if (3 < i && i < 7 && 8 < j && j < 12) {
				//fieldState[i][j] = TILE_DIRT;
            	TileFieldGroup->AddNewObject(new Engine::Image("farm/soil.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
			} else {
				//fieldState[i][j] = TILE_DIRT;
            	TileFieldGroup->AddNewObject(new Engine::Image("farm/grass.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
			}
        }
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			const char type = fieldData[i * FieldWidth + j];
			if (type == '0') {
                fieldState[i][j] = TILE_DIRT;
            } else if (type == '1') {
                fieldState[i][j] = TILE_WHEAT;
                TileFieldGroup->AddNewObject(new Engine::Image("farm/wheat.png", (j + 9) * BlockSize, (i + 4) * BlockSize, BlockSize, BlockSize));
            } else if (type == '2') {
                fieldState[i][j] = TILE_VEGETABLE;
                TileFieldGroup->AddNewObject(new Engine::Image("farm/vegetable.png", (j + 9) * BlockSize, (i + 4) * BlockSize, BlockSize, BlockSize));
            } else if (type == '3') {
                fieldState[i][j] = TILE_APPLE;
                TileFieldGroup->AddNewObject(new Engine::Image("farm/apple.png", (j + 9) * BlockSize, (i + 4) * BlockSize, BlockSize, BlockSize));
            } else if (type == '4') {
                fieldState[i][j] = TILE_FLOWER;
                TileFieldGroup->AddNewObject(new Engine::Image("farm/flower.png", (j + 9) * BlockSize, (i + 4) * BlockSize, BlockSize, BlockSize));
            } else {
                //throw std::ios_base::failure("Map data is corrupted.");
            }
		}
	}
}

void FarmScene::ConstructUI() {  
    // Background
	UIGroup->AddNewObject(new Engine::Image("play/sand.png", 1280, 0, 320, 832));
	PlantButton* btn;
	// Button 1
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1294, 136, 0, 0, 0, 0),
		Engine::Sprite("farm/wheat.png", 1294, 136 - 8, 0, 0, 0, 0)
		, 1294, 136, WheatPlant::HarvestTime);
	// Reference: Class Member Function Pointer and std::bind.
	btn->SetOnClickCallback(std::bind(&FarmScene::UIBtnClicked, this, 0));
	UIGroup->AddNewControlObject(btn);
	// Button 2
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1370, 136, 0, 0, 0, 0),
		Engine::Sprite("farm/vegetable.png", 1370, 136 - 8, 0, 0, 0, 0)
		, 1370, 136, VegetablePlant::HarvestTime);
	btn->SetOnClickCallback(std::bind(&FarmScene::UIBtnClicked, this, 1));
	UIGroup->AddNewControlObject(btn);
	// Button 3
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1446, 136, 0, 0, 0, 0),
		Engine::Sprite("farm/apple.png", 1446, 136, 0, 0, 0, 0)
		, 1446, 136, ApplePlant::HarvestTime);
	btn->SetOnClickCallback(std::bind(&FarmScene::UIBtnClicked, this, 2));
	UIGroup->AddNewControlObject(btn);
	// Button 4
	btn = new PlantButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1522, 136, 0, 0, 0, 0),
		Engine::Sprite("farm/flower.png", 1522, 136, 0, 0, 0, 0)
		, 1522, 136, FlowerPlant::HarvestTime);
	btn->SetOnClickCallback(std::bind(&FarmScene::UIBtnClicked, this, 3));
	UIGroup->AddNewControlObject(btn);
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int shift = 135 + 25;
}

void FarmScene::UIBtnClicked(int id) {
	if (preview)
		UIGroup->RemoveObject(preview->GetObjectIterator());
    // TODO: [CUSTOM-TURRET]: On callback, create the turret.
	if (id == 0/* && wheat seed > 0*/)
		preview = new WheatPlant(0, 0);
	else if (id == 1/* && vegetable seed > 0*/)
		preview = new VegetablePlant(0, 0);
	else if (id == 2 /*&& apple seed > 0*/)
		preview = new ApplePlant(0, 0);
	else if (id == 3 /*&& flower seed > 0*/)
		preview = new FlowerPlant(0, 0);
	if (!preview)
		return;
	preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
	preview->Tint = al_map_rgba(255, 255, 255, 200);
	preview->Enabled = false;
	preview->Preview = true;
	UIGroup->AddNewObject(preview);
	OnMouseMove(Engine::GameEngine::GetInstance().GetMousePosition().x, Engine::GameEngine::GetInstance().GetMousePosition().y);
}

bool FarmScene::CheckSpaceValid(int x, int y) {
	if (x < 0 || x >= FieldWidth || y < 0 || y >= FieldHeight)
		return false;
	else
		return true;
	/*auto map00 = FieldState[y][x];
	FieldState[y][x] = TILE_OCCUPIED;
	std::vector<std::vector<int>> map = CalculateBFSDistance();
	FieldState[y][x] = map00;
	if (map[0][0] == -1)
		return false;
	for (auto& it : EnemyGroup->GetObjects()) {
		Engine::Point pnt;
		pnt.x = floor(it->Position.x / BlockSize);
		pnt.y = floor(it->Position.y / BlockSize);
		if (pnt.x < 0) pnt.x = 0;
		if (pnt.x >= MapWidth) pnt.x = MapWidth - 1;
		if (pnt.y < 0) pnt.y = 0;
		if (pnt.y >= MapHeight) pnt.y = MapHeight - 1;
		if (map[pnt.y][pnt.x] == -1)
			return false;
	}*/
}
void FarmScene::OnMouseDown(int button, int mx, int my) {
	if ((button & 1) && !imgTarget->Visible && preview) {
		// Cancel plant construct.
		UIGroup->RemoveObject(preview->GetObjectIterator());
		preview = nullptr;
	}
	IScene::OnMouseDown(button, mx, my);
}
void FarmScene::OnMouseMove(int mx, int my) {
	IScene::OnMouseMove(mx, my);
	const int x = mx / BlockSize;
	const int y = my / BlockSize;
	if (!preview || x < 0 || x >= FieldWidth || y < 0 || y >= FieldHeight) {
		imgTarget->Visible = false;
		return;
	}
	imgTarget->Visible = true;
	imgTarget->Position.x = x * BlockSize;
	imgTarget->Position.y = y * BlockSize;
}

void FarmScene::OnMouseUp(int button, int mx, int my) {
	IScene::OnMouseUp(button, mx, my);
	if (!imgTarget->Visible)
		return;
	const int x = mx / BlockSize;
	const int y = my / BlockSize;
	if (button & 1) {
		if (fieldState[y][x] != TILE_DIRT) {
			if (!preview)
				return;
			// Check if valid.
			if (!CheckSpaceValid(x, y)) {
				Engine::Sprite* sprite;
				GroundEffectGroup->AddNewObject(sprite = new DirtyEffect("play/target-invalid.png", 1, x * BlockSize + BlockSize / 2, y * BlockSize + BlockSize / 2));
				sprite->Rotation = 0;
				return;
			}
			// Purchase.
			//EarnMoney(-preview->GetPrice());
			int Htime = preview->GetHarvestTime();
			// Remove Preview.
			preview->GetObjectIterator()->first = false;
			UIGroup->RemoveObject(preview->GetObjectIterator());
			// Construct real turret.
			preview->Position.x = x * BlockSize + BlockSize / 2;
			preview->Position.y = y * BlockSize + BlockSize / 2;
			preview->Enabled = true;
			preview->Preview = false;
			preview->Tint = al_map_rgba(255, 255, 255, 255);
			PlantGroup->AddNewObject(preview);
			// To keep responding when paused.
			preview->Update(0);
			// Remove Preview.
			preview = nullptr;
			if (Htime == 30) {
				fieldState[y][x] = TILE_WHEAT;
			} else if (Htime == 60) {
				fieldState[y][x] = TILE_VEGETABLE;
			} else if (Htime == 180) {
				fieldState[y][x] = TILE_APPLE;
			} else if (Htime == 300) {
				fieldState[y][x] = TILE_FLOWER;
			} else {

			}	
			OnMouseMove(mx, my);
		}
	}
}