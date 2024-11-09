
#include "PluginEditor.h"

class MyPlugin : public Plugin {
public:
    std::string getIdentifier()			override				 { return "MyPlugin"; }
    void serialize(std::vector<uint8_t> &outData) override		  {}
    void deserialize(const std::vector<uint8_t> &outData) override {}
};
class MyApp : public PluginEditor {
public:
	MyApp(Graphics &g, ::Plugin &effect)
		: PluginEditor(g, effect) {}

    virtual std::pair<int, int> getPreferredDimensions() const {
        return {512, 512};
    }

    void draw() {
		// g.clear(0, 0, 0);
		g.setColor(randuf(), randuf(), randuf());
		g.drawRect(randi(g.width / 2), randi(g.height / 2), g.width / 2, g.height / 2);
	}
};



bool isPlugin() {
	return true;
}

int getNumParams() {
	return 16;
}

int getNumPresets() {
	return 0;
}

// For starting as a plugin
std::shared_ptr<PluginEditor> instantiatePluginEditor(Graphics &g, std::shared_ptr<Plugin> plugin) {
	return std::make_shared<MyApp>(g, *std::dynamic_pointer_cast<MyPlugin>(plugin));
}

std::shared_ptr<Plugin> instantiatePlugin() {
	return std::make_shared<MyPlugin>();
}


std::shared_ptr<App> instantiateApp(Graphics &g) {
    g.width	 = 512;
    g.height = 512;

//    auto app = std::make_shared<MyApp>(g);
    return instantiatePluginEditor(g, instantiatePlugin());

}