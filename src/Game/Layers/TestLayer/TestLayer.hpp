#pragma once

#include "../../Graphics/Layer/LayerBase/LayerBase.hpp"

namespace jubeat_online {
	namespace game {
		namespace layers {
			class TestLayer : public jubeat_online::graphics::layer::LayerBase{
			public:
				void			Init();						//初期化関数
				void			Update();					//処理関数
				void			Draw();						//描写関数
				void			Exit();						//終了関数
			};
		}
	}

}