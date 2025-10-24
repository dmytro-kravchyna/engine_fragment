#include "index_generated.h"
#include "item-geometry.h"

using namespace js;

ItemGeometry::ItemGeometry(FragmentsModel model, js::number localId) {
    {
            this->model = model;
            this->localId = localId;
    }
}

auto ItemGeometry::get() {
    {
            auto _temp8320 = co_await this->model.threads.invoke(this->model.modelId, "getItemsGeometry"_S, js::array<js::any>{js::array<js::any>{this->localId}});
            const auto geometries = _temp8320[0];
            for (const auto& geometryData : geometries) {
                        {
                                        geometryData->transform = std::make_shared<three::Matrix4>().fromArray(geometryData->transform->elements);
                                        auto _temp1370 = geometryData;
                                        const auto indices = _temp1370["indices"];
                                        const auto normals = _temp1370["normals"];
                                        const auto positions = _temp1370["positions"];
                                        const auto transform = _temp1370["transform"];
                                        if (!this->_indices) {
                                                            this->_indices = js::array<js::any>{};
                                        }
                                        if (!this->_normals) {
                                                            this->_normals = js::array<js::any>{};
                                        }
                                        if (!this->_positions) {
                                                            this->_positions = js::array<js::any>{};
                                        }
                                        if (!this->_transform) {
                                                            this->_transform = js::array<js::any>{};
                                        }
                                        this->_indices.push(indices);
                                        this->_normals.push(normals);
                                        this->_positions.push(positions);
                                        this->_transform.push(transform);
                        }
            }
            return geometries;
    }
}

auto ItemGeometry::getIndices() {
    {
            if (this->_indices !== js::null) {
                        return this->_indices;
            }
            co_await this->get();
            return this->_indices;
    }
}

auto ItemGeometry::getTransform() {
    {
            if (this->_transform !== js::null) {
                        return this->_transform;
            }
            co_await this->get();
            return this->_transform;
    }
}

auto ItemGeometry::getNormals() {
    {
            if (this->_normals !== js::null) {
                        return this->_normals;
            }
            co_await this->get();
            return this->_normals;
    }
}

auto ItemGeometry::getPositions() {
    {
            if (this->_positions !== js::null) {
                        return this->_positions;
            }
            co_await this->get();
            return this->_positions;
    }
}

auto ItemGeometry::getVertices() {
    {
            if (this->_vertices) {
                        return this->_vertices;
            }
            const js::any allPositions = co_await this->getPositions();
            const js::any allTransforms = co_await this->getTransform();
            if ((!allPositions || !allTransforms)) {
                        return this->_vertices;
            }
            this->_vertices = js::array<js::any>{};
            for (js::number i = js::number(0); (i < allPositions.length()); i++) {
                        {
                                        const js::any positions = allPositions->i;
                                        const js::any transform = allTransforms->i;
                                        if ((!positions || !transform)) {
                                                            continue;
                                        }
                                        js::array<unknown> currentVertices = js::array<js::any>{};
                                        this->_vertices.push(currentVertices);
                                        const js::number numVertices = (js::Object::keys(positions).length / js::number(3));
                                        js::array<js::string> hashes = js::array<js::any>{};
                                        for (js::number i = js::number(0); (i < numVertices); i++) {
                                                            {
                                                                                    const js::any x = positions[(i * js::number(3))];
                                                                                    const js::any y = positions[((i * js::number(3)) + js::number(1))];
                                                                                    const js::any z = positions[((i * js::number(3)) + js::number(2))];
                                                                                    if (((js::typeof_op(x) !== "number"_S || js::typeof_op(y) !== "number"_S) || js::typeof_op(z) !== "number"_S)) {
                                                                                                                {
                                                                                                                                                continue;
                                                                                                                }
                                                                                    }
                                                                                    const js::any hash = (js::toString(x) + ","_S + js::toString(y) + ","_S + js::toString(z));
                                                                                    if (hashes.includes(hash)) {
                                                                                                                continue;
                                                                                    }
                                                                                    hashes.push(hash);
                                                                                    const std::shared_ptr<three::Vector3> vertex = std::make_shared<three::Vector3>(x, y, z);
                                                                                    vertex["applyMatrix4"](transform);
                                                                                    currentVertices.push(vertex);
                                                            }
                                        }
                        }
            }
            return this->_vertices;
    }
}

auto ItemGeometry::getTriangles() {
    {
            if (this->_triangles) {
                        return this->_triangles;
            }
            const js::any allIndices = co_await this->getIndices();
            const js::any allPositions = co_await this->getPositions();
            const js::any allTransforms = co_await this->getTransform();
            if (((!allIndices || !allPositions) || !allTransforms)) {
                        return this->_triangles;
            }
            this->_triangles = js::array<js::any>{};
            for (js::number i = js::number(0); (i < allIndices.length()); i++) {
                        {
                                        const js::any indices = allIndices->i;
                                        const js::any positions = allPositions->i;
                                        const js::any transform = allTransforms->i;
                                        if (((!indices || !positions) || !transform)) {
                                                            continue;
                                        }
                                        js::array<unknown> currentTriangles = js::array<js::any>{};
                                        this->_triangles.push(currentTriangles);
                                        for (js::number i = js::number(0); (i < indices.length()); i += js::number(3)) {
                                                            {
                                                                                    const js::any a = indices[i];
                                                                                    const js::any b = indices[(i + js::number(1))];
                                                                                    const js::any c = indices[(i + js::number(2))];
                                                                                    const std::shared_ptr<three::Vector3> v1 = std::make_shared<three::Vector3>(positions[(a * js::number(3))], positions[((a * js::number(3)) + js::number(1))], positions[((a * js::number(3)) + js::number(2))]);
                                                                                    const std::shared_ptr<three::Vector3> v2 = std::make_shared<three::Vector3>(positions[(b * js::number(3))], positions[((b * js::number(3)) + js::number(1))], positions[((b * js::number(3)) + js::number(2))]);
                                                                                    const std::shared_ptr<three::Vector3> v3 = std::make_shared<three::Vector3>(positions[(c * js::number(3))], positions[((c * js::number(3)) + js::number(1))], positions[((c * js::number(3)) + js::number(2))]);
                                                                                    v1["applyMatrix4"](transform);
                                                                                    v2["applyMatrix4"](transform);
                                                                                    v3["applyMatrix4"](transform);
                                                                                    currentTriangles.push(std::make_shared<three::Triangle>(v1, v2, v3));
                                                            }
                                        }
                        }
            }
            return this->_triangles;
    }
}

auto ItemGeometry::getPosition() {
    {
            if (!this->_position) {
                        {
                                        if (this->localId === js::null) {
                                                            return js::null;
                                        }
                                        this->_position = co_await this->model.getPositions(js::array<js::any>{this->localId});
                        }
            }
            return this->_position;
    }
}

auto ItemGeometry::getBox() {
    {
            if (!this->_box) {
                        {
                                        if (this->localId === js::null) {
                                                            return js::null;
                                        }
                                        this->_box = co_await this->model.getBoxes(js::array<js::any>{this->localId});
                        }
            }
            return this->_box;
    }
}

auto ItemGeometry::setVisibility(bool visible) {
    {
            co_await this->model.setVisible(js::array<js::any>{this->localId}, visible);
    }
}

auto ItemGeometry::getVisibility() {
    {
            auto _temp2726 = co_await this->model.getVisible(js::array<js::any>{this->localId});
            const auto result = _temp2726[0];
            return result;
    }
}
