#include <unordered_map>
#include <set>
#include <array>
#include <string>
#include <raylib.h>

namespace Game{
	class Debug{
		private:	
			std::unordered_map<std::string, Vector3> data;
			int edit_toggle_option=0;
		public:
			Debug();
			~Debug();
			void update();

			void save();
			void load();

			std::unordered_map<std::string, Vector3> collected_data();
	};
}
