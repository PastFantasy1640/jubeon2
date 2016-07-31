#include "BackgroundLayer.hpp"
#include <math.h>
#define PI 3.1415926535
#include <random>

//�萔�錾
//�����œ�����`
const sf::Int32 jubeat_online::game::layers::BackgroundLayer::REBORN_TIME = 580;
const unsigned int jubeat_online::game::layers::BackgroundLayer::BEZIER_RESOLUTION = 10;
const unsigned int jubeat_online::game::layers::BackgroundLayer::BORN_R_SIZE = 80;
const sf::Color jubeat_online::game::layers::BackgroundLayer::COLOR_NORMAL_BLUE(0x45D5FEff);
const sf::Color jubeat_online::game::layers::BackgroundLayer::COLOR_NORMAL_PINK(0xff3a7dff);
const sf::Vector2f jubeat_online::game::layers::BackgroundLayer::BORN_POSITION_LEFT(-100, 0);
const sf::Vector2f jubeat_online::game::layers::BackgroundLayer::BORN_POSITION_RIGHT(820, 0);
const sf::Vector2f jubeat_online::game::layers::BackgroundLayer::BORN_POSITION_TOP(384, -100);


jubeat_online::game::layers::BackgroundLayer::BackgroundLayer()
{
}

void jubeat_online::game::layers::BackgroundLayer::Init()
{

	//�N���b�N�����X�^�[�g
	this->times = 0;
	for (int i = 0; i < 1500; i++) this->update();

}


void jubeat_online::game::layers::BackgroundLayer::update(void)
{
	//���b���Ƃɐ�������
	if (times >= this->REBORN_TIME) {
		this->createDrop();

		this->times = 0;
	}

	if (times == this->REBORN_TIME / 2) this->createDrop2();

	for (auto p = this->dropping.begin(); p != this->dropping.end(); p++){

		//�S���̃o�l�𓮂���
		(*p)->applyForce(sf::Vector2f((this->getRandom() - 0.5f) * 10.0f, (this->getRandom() - 0.5f) * 10.0f));
		
	}

	this->times++;
}

void jubeat_online::game::layers::BackgroundLayer::createDrop(void)
{
	//����

	//�܂������牺�֗����Ă������
	//����͐�΂ɐ�
	std::unique_ptr<Theme::Drop<5>> tmp(new Theme::Drop<5>(this->genRandomPoints<5>(this->BORN_R_SIZE), this->BEZIER_RESOLUTION));

	tmp->setFillColor(this->COLOR_NORMAL_BLUE);
	tmp->setPosition(this->BORN_POSITION_LEFT);
	tmp->move2(sf::Vector2f(0.3 + this->getRandom() * 0.1, 1.5 + this->getRandom() * 0.1), sf::Vector2f(1.0008f, 1.0008f));
	this->dropping.push_back(std::move(tmp));

	//���ɉE���牺�֗����Ă������
	//����͐�
	tmp.reset(new Theme::Drop<5>(this->genRandomPoints<5>(this->BORN_R_SIZE), this->BEZIER_RESOLUTION));

	tmp->setFillColor(this->COLOR_NORMAL_PINK);
	tmp->setPosition(this->BORN_POSITION_RIGHT);
	tmp->move2(sf::Vector2f(-0.33 + this->getRandom() * 0.1, 1.5 + this->getRandom() * 0.1), sf::Vector2f(1.0008f, 1.0008f));
	this->dropping.push_back(std::move(tmp));


}

void jubeat_online::game::layers::BackgroundLayer::createDrop2(void)
{
	//�^�񒆂��牺��
	std::unique_ptr<Theme::Drop<5>> tmp;
	tmp.reset(new Theme::Drop<5>(this->genRandomPoints<5>(this->BORN_R_SIZE), this->BEZIER_RESOLUTION));

	tmp->setFillColor(this->COLOR_NORMAL_BLUE);
	tmp->setPosition(this->BORN_POSITION_TOP);
	tmp->move2(sf::Vector2f(this->getRandom() * 0.1 + 0.05, 0.8 + this->getRandom() * 0.1), sf::Vector2f(1.0008f, 1.0008f));
	this->dropping.push_back(std::move(tmp));

	tmp.reset(new Theme::Drop<5>(this->genRandomPoints<5>(this->BORN_R_SIZE), this->BEZIER_RESOLUTION));

	tmp->setFillColor(this->COLOR_NORMAL_PINK);
	tmp->setPosition(this->BORN_POSITION_TOP);
	tmp->move2(sf::Vector2f(this->getRandom() * -0.1 - 0.05, 0.8 + this->getRandom() * 0.1), sf::Vector2f(1.0008f, 1.0008f));
	this->dropping.push_back(std::move(tmp));
}

float jubeat_online::game::layers::BackgroundLayer::getRandom(void)
{
	return static_cast<float>(this->rnd()) / 0xffffffff;
}

bool jubeat_online::game::layers::BackgroundLayer::isOutOfScreen(const std::vector<std::unique_ptr<Theme::Drop<5>>>::const_iterator & p) const
{
	return !(sf::FloatRect(-100, -100, 1000, 2000).contains((*p)->getPosition()));
}

void jubeat_online::game::layers::BackgroundLayer::Draw()
{

	//�A�b�v�f�[�g
	this->update();

	this->clear(sf::Color::White);

	//�`��
	for (auto p = this->dropping.begin(); p != this->dropping.end(); ) {
		this->draw(*(*p),sf::BlendMultiply);
		if (this->isOutOfScreen(p)) {
			p = this->dropping.erase(p);
		}
		else p++;	//��������Ȃ��Ȃ玟��
	}

}

void jubeat_online::game::layers::BackgroundLayer::Exit()
{

}

template<std::size_t S>
std::array<sf::Vector2f, S> jubeat_online::game::layers::BackgroundLayer::genRandomPoints(unsigned int r)
{
	// �܊p�`�̊e���_�𐶐�
	std::array<sf::Vector2f, S> points;
	std::random_device rnd;
	for (int i = 0; i < points.size(); i++) {

		float degree = i * 360 / static_cast<float>(S);
		float scale = 1 - (static_cast<double>(rnd()) / 0xffffffff) / 3.0f;
		float tx = cos(degree * PI / 180.0f) * r;
		float ty = sin(degree * PI / 180.0f) * r;
		points[i] = (sf::Vector2f(scale * tx, scale * ty));
	}
	return points;
}