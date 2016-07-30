#pragma once

#ifndef TEMP_JUBEAT_ONLINE_BACKGROUND_LAYER_HPP
#define TEMP_JUBEAT_ONLINE_BACKGROUND_LAYER_HPP

#include <memory>
#include <random>

#include "../../Graphics/Layer/LayerBase.hpp"
#include <SFML/Graphics.hpp>
#include "../../Theme/Drop.hpp"

namespace jubeat_online {
	namespace game {
		namespace layers {
			class BackgroundLayer : public jubeat_online::graphics::layer::LayerBase{
			private:

				sf::Int32 born_time;
				sf::Int32 times;

				std::random_device rnd;

				std::vector<
					std::unique_ptr<
						Theme::Drop<5>
					>
				> dropping;

				//void setRebornTime(void);

				void update(void);
				void createDrop(void);
				void createDrop2(void);
				float getRandom(void);
				
				//画面の外か調べる
				bool isOutOfScreen(
					const std::vector<
						std::unique_ptr<
							Theme::Drop<5>
						>
					>::const_iterator & p) const;

				//定数群
				const static sf::Int32 REBORN_TIME;
				const static unsigned int BEZIER_RESOLUTION;
				const static unsigned int BORN_R_SIZE;
				const static sf::Color COLOR_NORMAL_BLUE;
				const static sf::Color COLOR_NORMAL_PINK;
				const static sf::Vector2f BORN_POSITION_LEFT;
				const static sf::Vector2f BORN_POSITION_RIGHT;
				const static sf::Vector2f BORN_POSITION_TOP;


			public:
				BackgroundLayer();
				virtual void Init() override;
				virtual void Draw() override;
				virtual void Exit() override;

				template<std::size_t S>
				static std::array<sf::Vector2f, S> genRandomPoints(unsigned int r);
			};
		}
	}
}


#endif

