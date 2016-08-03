#pragma once

#ifndef JUBEON_GAME_PANELINPUT_HPP
#define JUBEON_GAME_PANELINPUT_HPP



namespace jubeon {

	namespace input {

		enum Type : bool {
			PUSH = true,
			RELEASE = false
		};

		typedef struct PanelInput {
			unsigned char panel_no;
			jubeon::input::Type t;
			unsigned int ms;				//これは曲と同期するが、offsetを加算後のもの
			PanelInput() : panel_no(0), t(RELEASE), ms(0) {}
			PanelInput(unsigned char panel_no, jubeon::input::Type t, unsigned int ms)
				: panel_no(panel_no), t(t), ms(ms) {}
		}PanelInput;
	
	};
};

#endif