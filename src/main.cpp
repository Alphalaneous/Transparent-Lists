#include <Geode/Geode.hpp>
#include <alphalaneous.alphas_geode_utils/include/NodeModding.h>

using namespace geode::prelude;

class $nodeModify(GJListLayer) {
	void modify() {
		GJListLayer* self = reinterpret_cast<GJListLayer*>(this);\
		if(self->getColor() == ccColor3B{191,114,62}){
			self->setColor({0,0,0});
			self->setOpacity(50.0f);
		}
	}
};

#define makeTransparent(className)\
class $nodeModify(My##className, className) {\
	struct Fields {\
		ccColor3B m_lastBG;\
	};\
	void modify() {\
		checkBG(0);\
		schedule(schedule_selector(My##className::checkBG));\
	}\
	void checkBG(float dt) {\
		TableViewCell* self = reinterpret_cast<TableViewCell*>(this);\
		auto& bg = self->m_backgroundLayer;\
		auto fields = m_fields.self();\
		if(fields->m_lastBG != bg->getColor()){\
			fields->m_lastBG = bg->getColor();\
			if(bg->getColor() == ccColor3B{161,88,44}){\
				bg->setColor({0,0,0});\
			}\
			else if(bg->getColor() == ccColor3B{194,114,62}){\
				bg->setColor({80,80,80});\
			}\
			bg->setOpacity(50.0f);\
		}\
	}\
}

makeTransparent(LevelCell);
makeTransparent(LevelListCell);
makeTransparent(GJScoreCell);
makeTransparent(MapPackCell);

