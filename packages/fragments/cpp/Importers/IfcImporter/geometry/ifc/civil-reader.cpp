#include "index_generated.h"
#include "civil-reader.h"

using namespace js;

auto CivilReader::read(js::any webIfc) {
    {
            try {
                        const js::any alignments = webIfc->GetAllAlignments(js::number(0));
                        js::array<AlignmentData> allAlignments = js::array<js::any>{};
                        for (const auto& alignment : alignments) {
                                        {
                                                            const AlignmentData currentAlignment = []() {
                                                                  js::object obj_temp_0;
                                                                  obj_temp_0.set("absolute", js::array<js::any>{});
                                                                  obj_temp_0.set("horizontal", js::array<js::any>{});
                                                                  obj_temp_0.set("vertical", js::array<js::any>{});
                                                                  return js::any(obj_temp_0);
                                                                }();
                                                            allAlignments.push(currentAlignment);
                                                            js::number pointsCounter = js::number(0);
                                                            for (js::number i = js::number(0); (i < alignment["horizontal"].length()); i++) {
                                                                                    {
                                                                                                                const js::any points3d = alignment["curve3D"][js::number(0)].points;
                                                                                                                const js::any curveHorizontal = alignment["horizontal"][i];
                                                                                                                js::array<js::number> result3d = js::array<js::any>{};
                                                                                                                js::array<js::number> resultHorizontal = js::array<js::any>{};
                                                                                                                const js::any type = this->getCurveType(curveHorizontal->data->js::number(1));
                                                                                                                js::array<js::array<js::number>> points3DReversed = js::array<js::any>{};
                                                                                                                js::array<js::array<js::number>> pointsHorizontalReversed = js::array<js::any>{};
                                                                                                                for (const auto& point : curveHorizontal->points) {
                                                                                                                                                {
                                                                                                                                                                                    auto _temp6382 = points3d[pointsCounter++];
                                                                                                                                                                                    const auto x = _temp6382["x"];
                                                                                                                                                                                    const auto y = _temp6382["y"];
                                                                                                                                                                                    const auto z = _temp6382["z"];
                                                                                                                                                                                    points3DReversed.push(js::array<js::any>{x, y, z});
                                                                                                                                                                                    pointsHorizontalReversed.push(js::array<js::any>{point["x"], point["y"]});
                                                                                                                                                }
                                                                                                                }
                                                                                                                points3DReversed->reverse();
                                                                                                                pointsHorizontalReversed->reverse();
                                                                                                                for (const auto& js::undefined : points3DReversed) {
                                                                                                                                                {
                                                                                                                                                                                    result3d.push(x, y, z);
                                                                                                                                                }
                                                                                                                }
                                                                                                                for (const auto& js::undefined : pointsHorizontalReversed) {
                                                                                                                                                {
                                                                                                                                                                                    resultHorizontal.push(x, js::number(0), -y);
                                                                                                                                                }
                                                                                                                }
                                                                                                                const std::shared_ptr<Float32Array> buffer3d = std::make_shared<Float32Array>(result3d);
                                                                                                                const std::shared_ptr<Float32Array> bufferHorizontal = std::make_shared<Float32Array>(resultHorizontal);
                                                                                                                currentAlignment->absolute.push([]() {
                                                                                                                      js::object obj_temp_1;
                                                                                                                      obj_temp_1.set("points", buffer3d);
                                                                                                                      obj_temp_1.set("type", type);
                                                                                                                      return js::any(obj_temp_1);
                                                                                                                    }());
                                                                                                                currentAlignment->horizontal.push([]() {
                                                                                                                      js::object obj_temp_2;
                                                                                                                      obj_temp_2.set("points", bufferHorizontal);
                                                                                                                      obj_temp_2.set("type", type);
                                                                                                                      return js::any(obj_temp_2);
                                                                                                                    }());
                                                                                    }
                                                            }
                                                            for (js::number i = js::number(0); (i < alignment["vertical"].length()); i++) {
                                                                                    {
                                                                                                                const js::any curveVertical = alignment["vertical"][i];
                                                                                                                js::array<js::number> resultVertical = js::array<js::any>{};
                                                                                                                const js::any type = this->getCurveType(curveVertical->data->js::number(1));
                                                                                                                js::array<js::array<js::number>> pointsVerticalReversed = js::array<js::any>{};
                                                                                                                for (const auto& point : curveVertical->points) {
                                                                                                                                                {
                                                                                                                                                                                    pointsVerticalReversed.push(js::array<js::any>{point["x"], point["y"]});
                                                                                                                                                }
                                                                                                                }
                                                                                                                pointsVerticalReversed->reverse();
                                                                                                                for (const auto& js::undefined : pointsVerticalReversed) {
                                                                                                                                                {
                                                                                                                                                                                    resultVertical.push(x, y, js::number(0));
                                                                                                                                                }
                                                                                                                }
                                                                                                                const std::shared_ptr<Float32Array> bufferVertical = std::make_shared<Float32Array>(resultVertical);
                                                                                                                currentAlignment->vertical.push([]() {
                                                                                                                      js::object obj_temp_3;
                                                                                                                      obj_temp_3.set("points", bufferVertical);
                                                                                                                      obj_temp_3.set("type", type);
                                                                                                                      return js::any(obj_temp_3);
                                                                                                                    }());
                                                                                    }
                                                            }
                                        }
                        }
                        return allAlignments;
            } catch (const js::any& error) {
                        js::console.error(error);
                        return js::array<js::any>{};
            }
    }
}

auto CivilReader::getCurveType(js::string data) {
    {
            if (data.includes("CIRCULARARC"_S)) {
                        {
                                        return GeometryClass::ELLIPSE_ARC;
                        }
            }
            if ((data.includes("LINE"_S) || data.includes("GRADIENT"_S))) {
                        {
                                        return GeometryClass::LINES;
                        }
            }
            if (data.includes("CLOTHOID"_S)) {
                        {
                                        return GeometryClass::CLOTHOID;
                        }
            }
            if (data.includes("PARABOLICARC"_S)) {
                        {
                                        return GeometryClass::PARABOLA;
                        }
            }
            throw js::any(js::Error(("Fragments: Unknown curve type: "_S + js::toString(data))));
    }
}
