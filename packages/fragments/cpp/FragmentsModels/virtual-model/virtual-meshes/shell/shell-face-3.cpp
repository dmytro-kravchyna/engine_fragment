#include "index_generated.h"
#include "shell-face-3.h"

using namespace js;

auto ShellFace3::create(js::any indices, js::Float32Array data, js::Int16Array normals, TileData mesh, DataSizes sizes, js::number faceId) {
    {
            this->setFaceIds(sizes, mesh, faceId);
            this->setIndices(mesh, sizes);
            this->setPoints(indices, mesh, sizes, data);
            this->setNormals(mesh, sizes, normals);
            this->updateData(sizes);
    }
}

auto ShellFace3::setFaceIds(DataSizes sizes, TileData mesh, js::number faceId) {
    {
            const js::any amount = sizes["verticesAmount"];
            const js::number firstFace = (amount / js::number(3));
            const js::number lastFace = (firstFace + js::number(3));
            for (js::any i = firstFace; (i < lastFace); i++) {
                        {
                                        mesh["faceIdBuffer"][i] = faceId;
                        }
            }
    }
}

auto ShellFace3::setNormals(TileData mesh, DataSizes sizes, js::Int16Array normals) {
    {
            const js::any normal = mesh["normalBuffer"];
            for (js::number i = js::number(0); (i < this->totalIncrease); i++) {
                        {
                                        normal[(sizes["normalsAmount"] + i)] = normals[i];
                        }
            }
    }
}

auto ShellFace3::setPoints(js::any indices, TileData mesh, DataSizes sizes, js::Float32Array data) {
    {
            js::number counter = js::number(0);
            const js::any points = mesh["positionBuffer"];
            for (js::number i = js::number(0); (i < this->vertexIncrease); i++) {
                        {
                                        const js::number index = (indices[i] * this->vertexIncrease);
                                        for (js::number j = js::number(0); (j < this->vertexIncrease); j++) {
                                                            {
                                                                                    points[(sizes["verticesAmount"] + counter)] = data->(index + j);
                                                                                    counter++;
                                                            }
                                        }
                        }
            }
    }
}

auto ShellFace3::setIndices(TileData mesh, DataSizes sizes) {
    {
            const js::any index = mesh["indexBuffer"];
            for (js::number i = js::number(0); (i < this->vertexIncrease); i++) {
                        {
                                        index[(sizes["indices"] + i)] = (sizes["vertices"] + i);
                        }
            }
            sizes["indices"] += this->vertexIncrease;
    }
}

auto ShellFace3::updateData(DataSizes sizes) {
    {
            sizes["normalsAmount"] += ShellFace3::totalIncrease;
            sizes["vertices"] += ShellFace3::vertexIncrease;
            sizes["verticesAmount"] += ShellFace3::totalIncrease;
    }
}
