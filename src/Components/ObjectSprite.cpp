#include "Components/ObjectSprite.h"
#include <iostream>
#include <boost/bind.hpp>
#include <stdlib.h>
#include <time.h>
#include "Object.h"
ObjectSprite::ObjectSprite(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	imagePath = go->AddProperty<std::string>("SpriteImage","../resources/sprites/default.png");
	skin = go->AddProperty<int>("Skin",0);
	randomSkin = go->AddProperty<bool>("RandomSkin",false);
	totalSkins = go->AddProperty<int>("TotalSkins",1);
	posX = go->AddProperty<float>("PosX",0);
	posY = go->AddProperty<float>("PosY",0);
	imagePosX = go->AddProperty<float>("ImagePosX",0);
	imagePosY = go->AddProperty<float>("ImagePosY",0);
	offsetX        = go->AddProperty<float>("OffsetX",0.0);
	offsetY        = go->AddProperty<float>("OffsetY",0.0);
	spriteWidth = go->AddProperty<float>("SpriteWidth",32);
	spriteHeight = go->AddProperty<float>("SpriteHeight",32);
	rotation = go->AddProperty<float>("Rotation",0);
	alpha = go->AddProperty<int>("ColorAlpha",255);

	compInitialized = false;
}

ObjectSprite::~ObjectSprite()
{

}

void ObjectSprite::Init()
{
	//Select random skin
	if(randomSkin.Get())
	{
		skin.Set( rand() % totalSkins.Get() );
	}

	texture.loadFromFile( imagePath.Get() );

	sprite.setPosition( posX.Get(),posY.Get() );
	sprite.setOrigin( spriteWidth.Get()/2,spriteHeight.Get()/2);
	sprite.setTexture( texture,true );
	float skinY = imagePosY.Get()+spriteHeight.Get()*skin.Get();
	sprite.setTextureRect(sf::IntRect(imagePosX.Get(),skinY,spriteWidth.Get(),spriteHeight.Get()));
	sprite.setColor(sf::Color(255,255,255,alpha.Get()));
	
	spritePtr = go->AddProperty<sf::Sprite*>("Sprite",&sprite);
}

void ObjectSprite::Update(int delta)
{

}

void ObjectSprite::Draw(sf::RenderWindow *window)
{
	sprite.setPosition( posX.Get() + offsetX.Get(),posY.Get() + offsetY.Get() );
	sprite.setRotation( rotation.Get() );
	window->draw(sprite);
}

void ObjectSprite::ExecuteCommand(int command, void* data )
{

}
