#include "index_generated.h"
#include "vce-lod-constructor.h"

using namespace js;

auto VceLodConstructor::construct(CircleExtrusion circleExtrusion, TileData mesh) {
    {
            this->_currentElement = js::number(0);
            mesh["positionBuffer"] = std::make_shared<Float32Array>(mesh["positionCount"]);
            for (js::number i = js::number(0);
            js::any l = circleExtrusion->axesLength(); (i < l); i++) {
                        {
                                        circleExtrusion->axes(i, VceUtils::temp::axis);
                                        this->constructLod(mesh);
                        }
            }
            return mesh;
    }
}

auto VceLodConstructor::constructCircleExtrusionLod(js::number id, TileData mesh) {
    {
            const js::any axis = VceUtils::temp::axis;
            const js::any type = axis["parts"](id);
            const js::any index = axis["order"](id);
            const js::any lodConstructor = this->getLodConstructor(type);
            lodConstructor(axis, index, mesh);
    }
}

auto VceLodConstructor::newCircleCurveLodPath(Axis axis, js::number index) {
    {
            const js::any curve = axis["circleCurves"](index);
            const js::any count = VceCasterUtils::circleCurve3Divisions(curve);
            VceUtils::circleCurves = VceUtils::newPaths(curve, count);
            return count;
    }
}

auto VceLodConstructor::selectNextWire() {
    {
            this->_currentElement += this->_wireSize;
    }
}

void VceLodConstructor::getAxisPartVertexSize(js::number id, TileBasicData template) {
    {
            const js::any axis = VceUtils::temp::axis;
            const js::any partClass = axis["parts"](id);
            const js::any order = axis["order"](id);
            const js::any templateConstructor = this->getTemplateConstructor(partClass);
            templateConstructor(order, template_);
    }
}

auto VceLodConstructor::getIndices() {
    {
            const js::any i1 = this->_currentElement;
            const js::number i2 = (this->_currentElement + js::number(1));
            const js::number i3 = (this->_currentElement + js::number(2));
            const js::number i4 = (this->_currentElement + js::number(3));
            const js::number i5 = (this->_currentElement + js::number(4));
            const js::number i6 = (this->_currentElement + js::number(5));
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("i1", i1);
                  obj_temp_0.set("i2", i2);
                  obj_temp_0.set("i3", i3);
                  obj_temp_0.set("i4", i4);
                  obj_temp_0.set("i5", i5);
                  obj_temp_0.set("i6", i6);
                  return js::any(obj_temp_0);
                }();
    }
}

auto VceLodConstructor::setAxisTemplate(js::number id, TileBasicData template) {
    {
            VceUtils::temp::circleExtrusion::axes(id, VceUtils::temp::axis);
            const js::any count = VceUtils::temp::axis::partsLength();
            for (js::number id = js::number(0); (id < count); id++) {
                        {
                                        this->getAxisPartVertexSize(id, template_);
                        }
            }
            this->setAxisThickness(template_, id);
    }
}

auto VceLodConstructor::constructLod(TileData mesh) {
    {
            const js::any count = VceUtils::temp::axis::orderLength();
            for (js::number id = js::number(0); (id < count); id++) {
                        {
                                        this->constructCircleExtrusionLod(id, mesh);
                        }
            }
    }
}

auto VceLodConstructor::getLodConstructor(AxisPartClass type) {
    {
            const js::any constructors = []() {
                  js::object obj_temp_1;
                  obj_temp_1.set(js::toString(AxisPartClass::WIRE), this->newWireLod);
                  obj_temp_1.set(js::toString(AxisPartClass::WIRE_SET), this->newWireSetLod);
                  obj_temp_1.set(js::toString(AxisPartClass::CIRCLE_CURVE), this->newCircleCurveLod);
                  return js::any(obj_temp_1);
                }();
            return constructors[type];
    }
}

auto VceLodConstructor::newTemplate() {
    {
            const js::any circularExtrusion = VceUtils::temp::circleExtrusion;
            const js::any template_ = this->newTemplateData();
            const js::any count = circularExtrusion->axesLength();
            for (js::number id = js::number(0); (id < count); id++) {
                        {
                                        this->setAxisTemplate(id, template_);
                        }
            }
            return template_;
    }
}

auto VceLodConstructor::setAxisThickness(TileBasicData template, js::number id) {
    {
            const js::any l1 = template_["lodThickness"];
            const js::any l2 = VceUtils::temp::circleExtrusion::radius(id);
            template_["lodThickness"] = js::Math::max(l1, l2);
    }
}

auto VceLodConstructor::newTemplateData() {
    {
            return []() {
                  js::object obj_temp_2;
                  obj_temp_2.set("objectClass", ObjectClass::LINE);
                  obj_temp_2.set("lod", CurrentLod::WIRES);
                  obj_temp_2.set("lodThickness", js::number(0));
                  obj_temp_2.set("positionCount", js::number(0));
                  return js::any(obj_temp_2);
                }();
    }
}

auto VceLodConstructor::getTemplateConstructor(AxisPartClass type) {
    {
            const js::any constructors = []() {
                  js::object obj_temp_3;
                  obj_temp_3.set(js::toString(AxisPartClass::WIRE), this->newWireTemplate);
                  obj_temp_3.set(js::toString(AxisPartClass::WIRE_SET), this->newWireSetTemplate);
                  obj_temp_3.set(js::toString(AxisPartClass::CIRCLE_CURVE), this->newCircleCurveTemplate);
                  return js::any(obj_temp_3);
                }();
            return constructors[type];
    }
}

auto VceLodConstructor::newWire(DataBuffer points, js::any first, js::any last) {
    {
            const js::any x1 = (js::null ? js::null : js::null);
            const js::any y1 = (js::null ? js::null : js::null);
            const js::any z1 = (js::null ? js::null : js::null);
            const js::any x2 = (js::null ? js::null : js::null);
            const js::any y2 = (js::null ? js::null : js::null);
            const js::any z2 = (js::null ? js::null : js::null);
            auto _temp2010 = this->getIndices();
            const auto i1 = _temp2010["i1"];
            const auto i2 = _temp2010["i2"];
            const auto i3 = _temp2010["i3"];
            const auto i4 = _temp2010["i4"];
            const auto i5 = _temp2010["i5"];
            const auto i6 = _temp2010["i6"];
            points[i1] = x1;
            points[i2] = y1;
            points[i3] = z1;
            points[i4] = x2;
            points[i5] = y2;
            points[i6] = z2;
            this->selectNextWire();
    }
}
