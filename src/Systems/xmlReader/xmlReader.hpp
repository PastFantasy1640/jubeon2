#pragma once

#ifndef JUBEON_SYSTEM_XMLREADER_HPP
#define JUBEON_SYSTEM_XMLREADER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <memory>

namespace jubeat_online {
	namespace system {
		class xmlReader {
		private:
			const std::string filename;

			//leafの0番目はその要素、
			//leafの1番目以降は属性
			//leafの要素が0なら、valueが0
			struct Element{
				typedef std::unique_ptr<Element> UPElement;

				std::string value;
				std::vector<UPElement> leafs;
			};


			xmlReader();
		public:
			xmlReader(const std::string filename);
			virtual ~xmlReader();

			bool update(void);

			std::string get(const std::string key);
		};
	}
}

#endif