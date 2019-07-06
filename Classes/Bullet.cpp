#include "Bullet.h"

using namespace cocos2d;

bool Bullet::init() {
	return BoxSprite::initWithFile("Game/fire.png");
}

void Bullet::setVelocity(const Vec2& v) {
	auto body = this->getPhysicsBody();
	body->setVelocity(Vec2(v.x * speed, v.y * speed));
}