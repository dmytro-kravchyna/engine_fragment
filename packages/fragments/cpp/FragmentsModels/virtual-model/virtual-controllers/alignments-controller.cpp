#include "index_generated.h"
#include "alignments-controller.h"

using namespace js;

AlignmentsController::AlignmentsController(Model model) {
    {
            this->_model = model;
    }
}

auto AlignmentsController::getAlignments() {
    {
            js::array<AlignmentData> allAlignments = js::array<js::any>{};
            const js::any alignmentsSize = this->_model.alignmentsLength();
            for (js::number i = js::number(0); (i < alignmentsSize); i++) {
                        {
                                        const js::any alignment = this->_model.alignments(i);
                                        const AlignmentData current = []() {
                                              js::object obj_temp_0;
                                              obj_temp_0.set("absolute", js::array<js::any>{});
                                              obj_temp_0.set("horizontal", js::array<js::any>{});
                                              obj_temp_0.set("vertical", js::array<js::any>{});
                                              return js::any(obj_temp_0);
                                            }();
                                        allAlignments.push(current);
                                        this->constructAlignment(alignment, current, "absolute"_S);
                                        this->constructAlignment(alignment, current, "horizontal"_S);
                                        this->constructAlignment(alignment, current, "vertical"_S);
                        }
            }
            return allAlignments;
    }
}

auto AlignmentsController::constructAlignment(Alignment alignment, AlignmentData current, js::any type) {
    {
            const js::any lengthIds = []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("absolute", "absoluteLength"_S);
                  obj_temp_1.set("horizontal", "horizontalLength"_S);
                  obj_temp_1.set("vertical", "verticalLength"_S);
                  return js::any(obj_temp_1);
                }();
            const js::any lengthId = lengthIds->type;
            const js::any curveSize = alignment[lengthId]();
            const js::any geometries = this->_model.geometries();
            for (js::number j = js::number(0); (j < curveSize); j++) {
                        {
                                        const js::any sampleId = alignment[type](j);
                                        const js::any sample = geometries["samples"](sampleId);
                                        const js::any reprIndex = sample["id"]();
                                        const js::any representation = geometries["representations"](reprIndex);
                                        const js::any geomIndex = representation["id"]();
                                        const js::any geometryClass = representation["geometryClass"]();
                                        js::array<js::number> curveBuffer = js::array<js::any>{};
                                        const js::any lines = geometries["lines"](geomIndex);
                                        const js::any coords = lines["pointsArray"]();
                                        for (const auto& coord : coords) {
                                                            {
                                                                                    curveBuffer.push(coord);
                                                            }
                                        }
                                        current[type].push([]() {
                                              js::object obj_temp_2;
                                              obj_temp_2.set("points", std::make_shared<Float32Array>(curveBuffer));
                                              obj_temp_2.set("type", geometryClass);
                                              return js::any(obj_temp_2);
                                            }());
                        }
            }
    }
}
