#include "index_generated.h"
#include "shell-face-x.h"

using namespace js;

auto ShellFaceX::create(js::any indices, js::Float32Array data, js::Int16Array normals, js::number current, TileData mesh, Map holes, DataSizes sizes, js::number faceId) {
    {
            const js::any size = indices.length();
            const js::any amount = sizes["verticesAmount"];
            ShellFaceX::processBuffers(size, indices, mesh, sizes, data, normals);
            const js::any position = mesh["positionBuffer"];
            const js::number pointsDiff = (sizes["verticesAmount"] - amount);
            const js::number normalDims = (pointsDiff / js::number(3));
            this->processNormals(position, this->_tempVec, normalDims, amount);
            this->triangulate(holes, current, size, mesh, sizes, amount);
            this->setFaceId(amount, sizes, mesh, faceId);
    }
}

auto ShellFaceX::setFaceId(js::number amount, DataSizes sizes, TileData mesh, js::number faceId) {
    {
            const js::number firstFace = (amount / js::number(3));
            const js::number lastFace = (sizes["verticesAmount"] / js::number(3));
            for (js::any i = firstFace; (i < lastFace); i++) {
                        {
                                        mesh["faceIdBuffer"][i] = faceId;
                        }
            }
    }
}

auto ShellFaceX::getVertices(TileData mesh, js::number amount, DataSizes sizes) {
    {
            const js::any points = mesh["positionBuffer"];
            const js::any buffer = points["buffer"];
            const js::number position = (amount * js::number(4));
            const js::number size = (sizes["verticesAmount"] - amount);
            return std::make_shared<Float32Array>(buffer, position, size);
    }
}

auto ShellFaceX::getEvent(TileData mesh, DataSizes sizes, js::number amount) {
    {
            return [&](js::number first, js::number second, js::number third) -> auto {
            const js::any position = mesh["indexBuffer"];
            position[sizes["indices"]++] = (first + (amount / js::number(3)));
            position[sizes["indices"]++] = (second + (amount / js::number(3)));
            position[sizes["indices"]++] = (third + (amount / js::number(3)));
            };
    }
}

auto ShellFaceX::processBuffers(js::number size, js::any indices, TileData mesh, DataSizes sizes, js::Float32Array data, js::Int16Array normals) {
    {
            for (js::number id = js::number(0); (id < size); id++) {
                        {
                                        this->processPositionBuffer(mesh, indices, id, sizes, data);
                                        this->processNormalbuffer(mesh, normals, id, sizes);
                                        this->updateBufferData(sizes);
                        }
            }
    }
}

auto ShellFaceX::getHoles(Map shellHoles, js::number index, js::number size, TileData mesh, DataSizes sizes) {
    {
            if (!shellHoles) {
                        {
                                        return js::undefined;
                        }
            }
            const js::any isHole = shellHoles->has(index);
            if (isHole) {
                        {
                                        const js::any currentHole = shellHoles->get(index);
                                        js::array<js::number> holesData = js::array<js::any>{};
                                        for (const auto& index : currentHole->indices) {
                                                            {
                                                                                    holesData.push((index + size));
                                                            }
                                        }
                                        this->setHolesBuffers(mesh, currentHole, sizes);
                                        return holesData;
                        }
            }
            return js::undefined;
    }
}

auto ShellFaceX::setHolesBuffers(TileData mesh, ShellHoleData shellHole, DataSizes sizes) {
    {
            const js::any position = mesh["positionBuffer"];
            const js::any normal = mesh["normalBuffer"];
            position["set"](shellHole->points, sizes["verticesAmount"]);
            const js::any holePoints = shellHole->points.length();
            sizes["verticesAmount"] += holePoints;
            sizes["vertices"] += (holePoints / js::number(3));
            normal["set"](shellHole->normals, sizes["normalsAmount"]);
            sizes["normalsAmount"] += holePoints;
    }
}

auto ShellFaceX::updateBufferData(DataSizes sizes) {
    {
            sizes["vertices"] += js::number(1);
            sizes["verticesAmount"] += js::number(3);
            sizes["normalsAmount"] += js::number(3);
    }
}

auto ShellFaceX::processPositionBuffer(TileData mesh, js::any indices, js::number id, DataSizes sizes, js::Float32Array data) {
    {
            const js::any position = mesh["positionBuffer"];
            for (js::number j = js::number(0); (j < js::number(3)); j++) {
                        {
                                        const js::number current = (indices[id] * js::number(3));
                                        position[(sizes["verticesAmount"] + j)] = data->(current + j);
                        }
            }
    }
}

auto ShellFaceX::triangulate(Map holes, js::number current, js::number size, TileData mesh, DataSizes sizes, js::number amount) {
    {
            const js::number tri = js::number(3);
            const js::any holesData = this->getHoles(holes, current, size, mesh, sizes);
            const js::any vertices = ShellFaceX::getVertices(mesh, amount, sizes);
            const js::any dims = FaceUtils::getEarcutDimensions(this->_tempVec);
            const js::any onCreateGeometry = this->getEvent(mesh, sizes, amount);
            const js::any firstDim = dims[js::number(0)];
            const js::any secondDim = dims[js::number(1)];
            earcut(vertices, holesData, tri, firstDim, secondDim, onCreateGeometry);
    }
}

auto ShellFaceX::processNormals(DataBuffer input, js::any result, js::number size, auto position) {
    {
            result->set(js::number(0), js::number(0), js::number(0));
            for (js::number i = js::number(0); (i < size); i++) {
                        {
                                        const js::number counter = ((i + js::number(1)) % size);
                                        const js::number i1 = (position + (i * js::number(3)));
                                        const js::number i2 = (position + (counter * js::number(3)));
                                        const js::any x1 = input[(i1 + js::number(0))];
                                        const js::any x2 = input[(i2 + js::number(0))];
                                        const js::any y1 = input[(i1 + js::number(1))];
                                        const js::any y2 = input[(i2 + js::number(1))];
                                        const js::any z1 = input[(i1 + js::number(2))];
                                        const js::any z2 = input[(i2 + js::number(2))];
                                        result->x += ((y1 - y2) * (z1 + z2));
                                        result->y += ((z1 - z2) * (x1 + x2));
                                        result->z += ((x1 - x2) * (y1 + y2));
                        }
            }
            result->normalize();
    }
}

auto ShellFaceX::processNormalbuffer(TileData mesh, js::Int16Array normals, js::number id, DataSizes sizes) {
    {
            const js::any normal = mesh["normalBuffer"];
            const js::number current = (id * js::number(3));
            const js::any nx = normals[current];
            const js::any ny = normals[(current + js::number(1))];
            const js::any nz = normals[(current + js::number(2))];
            normal["set"](js::array<js::any>{nx, ny, nz}, sizes["normalsAmount"]);
    }
}
