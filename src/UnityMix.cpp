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
		configParam(GAIN_PARAM, 0.f, 2.f, 1.f, "Output gain");
	}

	void process(const ProcessArgs& args) override {
		// read all of the inputs and keep track
		// of how many inputs there are
		float in1=0.f, in2=0.f, in3=0.f;
		int num_inputs = 0;
		if(inputs[IN1_INPUT].isConnected()) {
			in1 = inputs[IN1_INPUT].getVoltage();
			num_inputs++;
		}

		if(inputs[IN2_INPUT].isConnected()) {
			in2 = inputs[IN2_INPUT].getVoltage();
			num_inputs++;
		}

		if(inputs[IN3_INPUT].isConnected()) {
			in3 = inputs[IN3_INPUT].getVoltage();
			num_inputs++;
		}

		// if no inputs, write out a 0 and return
		if(num_inputs == 0) {
			outputs[MIX_OUTPUT].setVoltage(0.f);
			return;
		}
		
		// calculate the input gain
		float input_gain = 1.f/num_inputs;

		// calculate the raw output sample
		float output = (in1 + in2 + in3) * input_gain;

		// read value of output gain knob
		float output_gain = params[GAIN_PARAM].getValue();

		// calculate and write out the output
		outputs[MIX_OUTPUT].setVoltage(output * output_gain);
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