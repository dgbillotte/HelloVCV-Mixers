#include "plugin.hpp"


struct UnityMix : Module {
	enum ParamIds {
		GAIN_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		IN1_INPUT,
		IN2_INPUT,
		IN3_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		MIX_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	UnityMix() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(GAIN_PARAM, 0.f, 1.f, 0.f, "");
	}

	void process(const ProcessArgs& args) override {
	}
};


struct UnityMixWidget : ModuleWidget {
	UnityMixWidget(UnityMix* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/UnityMix.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		// Input Jacks
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.124, 18.511)), module, UnityMix::IN1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.124, 35.37)), module, UnityMix::IN2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.124, 52.23)), module, UnityMix::IN3_INPUT));

		// Gain Knob
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.124, 95.73)), module, UnityMix::GAIN_PARAM));

		// Output Jack
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.124, 119.415)), module, UnityMix::MIX_OUTPUT));
	}
};


Model* modelUnityMix = createModel<UnityMix, UnityMixWidget>("UnityMix");