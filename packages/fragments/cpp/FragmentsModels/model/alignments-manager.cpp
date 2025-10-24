#include "index_generated.h"
#include "alignments-manager.h"

using namespace js;

AlignmentsManager::AlignmentsManager(FragmentsModel model) {
    {
            this->model = model;
    }
}

auto AlignmentsManager::getAlignments() {
    {
            if (!this->_absoluteAlignments.children.length()) {
                        {
                                        co_await this->constructAlignments();
                        }
            }
            return this->_absoluteAlignments;
    }
}

auto AlignmentsManager::getHorizontalAlignments() {
    {
            if (!this->_horizontalAlignments.children.length()) {
                        {
                                        co_await this->constructAlignments();
                        }
            }
            return this->_horizontalAlignments;
    }
}

auto AlignmentsManager::getVerticalAlignments() {
    {
            if (!this->_verticalAlignments.children.length()) {
                        {
                                        co_await this->constructAlignments();
                        }
            }
            return this->_verticalAlignments;
    }
}

auto AlignmentsManager::getAlignmentStyles() {
    {
            return []() {
                  js::object obj_temp_0;
                  return js::any(obj_temp_0);
                }();
    }
}

auto AlignmentsManager::constructAlignments() {
    {
            const js::any result = co_await this->model.threads.invoke(this->model.modelId, "getAlignments"_S);
            for (const auto& alignmentData : result) {
                        {
                                        this->constructLine(alignmentData->absolute, this->_absoluteAlignments);
                                        this->constructLine(alignmentData->horizontal, this->_horizontalAlignments);
                                        this->constructLine(alignmentData->vertical, this->_verticalAlignments);
                        }
            }
    }
}

auto AlignmentsManager::constructLine(js::array<AlignmentCurve> data, js::any parent) {
    {
            if (!data.length()) {
                        {
                                        return;
                        }
            }
            js::array<js::number> iPoints = js::array<js::any>{};
            js::array<js::number> ePoints = js::array<js::any>{};
            const std::shared_ptr<three::Group> alignment = std::make_shared<three::Group>();
            parent["add"](alignment);
            const js::any firstPoints = data->js::number(0).points;
            const js::any lastPoints = data->(data.length() - js::number(1)).points;
            ePoints.push(lastPoints->js::number(0), lastPoints->js::number(1), lastPoints->js::number(2));
            ePoints.push(firstPoints->(firstPoints.length() - js::number(3)), firstPoints->(firstPoints.length() - js::number(2)), firstPoints->(firstPoints.length() - js::number(1)));
            for (const auto& curve : data) {
                        {
                                        const js::any points = curve["points"];
                                        iPoints.push(points[js::number(0)], points[js::number(1)], points[js::number(2)]);
                                        iPoints.push(points[(points.length() - js::number(3))], points[(points.length() - js::number(2))], points[(points.length() - js::number(1))]);
                                        const std::shared_ptr<LineGeometry> geometry = std::make_shared<LineGeometry>();
                                        geometry["setPositions"](points);
                                        const js::any material = this->_alignmentMaterials.get(curve["type"]);
                                        const std::shared_ptr<Line2> line = std::make_shared<Line2>(geometry, material);
                                        alignment["add"](line);
                                        line["renderOrder"] = js::number(1);
                                        line["userData"]["points"] = points;
                        }
            }
            auto _temp3129 = this->_endpointsMaterials;
            const auto interior = _temp3129["interior"];
            const auto exterior = _temp3129["exterior"];
            this->constructPoints(iPoints, interior, alignment);
            this->constructPoints(ePoints, exterior, alignment);
    }
}

auto AlignmentsManager::constructPoints(js::array<js::number> pointsArray, js::any material, js::any alignment) {
    {
            const std::shared_ptr<three::Points> points = std::make_shared<three::Points>();
            const std::shared_ptr<three::BufferGeometry> pointsGeom = std::make_shared<three::BufferGeometry>();
            const std::shared_ptr<Float32Array> pointsBuffer = std::make_shared<Float32Array>(pointsArray);
            const std::shared_ptr<three::BufferAttribute> pointsAttr = std::make_shared<three::BufferAttribute>(pointsBuffer, js::number(3));
            pointsGeom->setAttribute("position"_S, pointsAttr);
            points["geometry"] = pointsGeom;
            points["material"] = material;
            alignment["add"](points);
            points["renderOrder"] = js::number(2);
    }
}

auto AlignmentsManager::dispose() {
    {
            this->_absoluteAlignments.removeFromParent();
            for (const auto& alignment : this->_absoluteAlignments.children) {
                        {
                                        const js::any line = alignment;
                                        line["geometry"]["dispose"]();
                                        line["geometry"] = js::undefined;
                                        line["material"] = js::undefined;
                        }
            }
            for (const auto& material : js::Object::values(this->_alignmentMaterials)) {
                        {
                                        material["dispose"]();
                        }
            }
            this->_alignmentMaterials = []() {
                  js::object obj_temp_1;
                  return js::any(obj_temp_1);
                }();
    }
}
