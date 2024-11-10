
#include "PluginEditor.h"

class MyPlugin : public Plugin {
public:
    std::string getIdentifier()			override				 { return "MyPlugin"; }
    void serialize(std::vector<uint8_t> &outData) override		  {}
    void deserialize(const std::vector<uint8_t> &outData) override {}

    double phase = 0;

    double lfoPhase = 0;
    float lfoVal = 0;
    void process(FloatBuffer *ins, FloatBuffer *outs, int channelsPerBus)override {

        for(int i = 0; i < outs[0].size(); i++) {
            phase += 256 * M_PI * 2.f / 48000.f;
            lfoPhase += 0.2 * M_PI * 2.f / 48000.f;
            lfoVal = mapf(sinf(lfoPhase), -1, 1, 0, 1);
            outs[0][i] = 0.25f * sinf(phase) * lfoVal;
        }
    }
};

class MyApp : public PluginEditor {
public:
    MyPlugin &plug;
	MyApp(Graphics &g, ::Plugin &effect)
    : PluginEditor(g, effect), plug(dynamic_cast<MyPlugin&>(effect)) {
        
    }

    virtual std::pair<int, int> getPreferredDimensions() const {
        return {512, 512};
    }

    void draw() {
		// g.clear(0, 0, 0);
        ScopedAlphaBlend bl(g, true);

		g.setColor(0, randuf(), 0, plug.lfoVal);
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


std::shared_ptr<AudioSystem> as;
std::shared_ptr<App> instantiateApp(Graphics &g) {
    g.width	 = 512;
    g.height = 512;

//    auto app = std::make_shared<MyApp>(g);
    as = std::make_shared<AudioSystem>();
    as->setup(0, 2);
    auto app = instantiatePluginEditor(g, instantiatePlugin());
    as->bindToApp(app.get());
    as->start();
    return app;

}

