#include "index_generated.h"
#include "shell-face-4.h"

using namespace js;

auto ShellFace4::create(js::any indices, js::Float32Array data, js::Int16Array normals, js::number id, TileData mesh, DataSizes sizes, js::number faceId) {
    {
            this->setAllVectors(indices, data);
            const js::any isConvex = this->getIsConvex();
            if (isConvex) {
                        {
                                        this->processConvexFace4(mesh, sizes, normals, faceId);
                                        return;
                        }
            }
            ShellFaceX::create(indices, data, normals, id, mesh, js::undefined, sizes, faceId);
    }
}

auto ShellFace4::setAllVectors(js::any indices, js::Float32Array data) {
    {
            this->setVector(indices, data, this->a, js::number(0));
            this->setVector(indices, data, this->b, js::number(1));
            this->setVector(indices, data, this->c, js::number(2));
            this->setVector(indices, data, this->d, js::number(3));
            this->getCrossVectors();
    }
}

auto ShellFace4::processConvexFace4(TileData mesh, DataSizes sizes, js::Int16Array normals, js::number faceId) {
    {
            this->processIndices(mesh, sizes);
            this->processPoints(mesh, sizes);
            this->processNormal(mesh, sizes, normals);
            this->setFaceId(mesh, sizes, faceId);
            this->updateData(sizes);
    }
}

auto ShellFace4::setFaceId(TileData mesh, DataSizes sizes, js::number faceId) {
    {
            const js::any faceIds = mesh["faceIdBuffer"];
            for (js::any i = sizes["vertices"]; (i < (sizes["vertices"] + js::number(4))); i++) {
                        {
                                        faceIds->i = faceId;
                        }
            }
    }
}

auto ShellFace4::getIsConvex() {
    {
            return (this->h.dot(this->i) > js::number(0));
    }
}

auto ShellFace4::getCrossVectors() {
    {
            this->e.copy(this->b);
            this->f.copy(this->c);
            this->g.copy(this->d);
            this->e.sub(this->a);
            this->f.sub(this->a);
            this->g.sub(this->a);
            this->h.crossVectors(this->e, this->f);
            this->i.crossVectors(this->f, this->g);
    }
}

auto ShellFace4::updateData(DataSizes sizes) {
    {
            sizes["normalsAmount"] += this->totalIncrease;
            sizes["vertices"] += this->vertexIncrease;
            sizes["verticesAmount"] += this->totalIncrease;
    }
}

auto ShellFace4::processPoints(TileData mesh, DataSizes sizes) {
    {
            js::number counter = js::number(0);
            const js::any position = mesh["positionBuffer"];
            const js::any amount = sizes["verticesAmount"];
            for (js::number i = js::number(0); (i < this->vertexIncrease); i++) {
                        {
                                        const js::any vec = this->_vecs[i];
                                        position[(amount + counter++)] = vec["x"];
                                        position[(amount + counter++)] = vec["y"];
                                        position[(amount + counter++)] = vec["z"];
                        }
            }
    }
}

auto ShellFace4::setVector(js::any indices, js::Float32Array data, js::any vector, js::number offset) {
    {
            const js::number index = (indices[offset] * js::number(3));
            const js::any x = data->index;
            const js::any y = data->(index + js::number(1));
            const js::any z = data->(index + js::number(2));
            vector["set"](x, y, z);
    }
}

auto ShellFace4::processNormal(TileData mesh, DataSizes sizes, js::Int16Array normals) {
    {
            const js::any normal = mesh["normalBuffer"];
            const js::any amount = sizes["normalsAmount"];
            for (js::number i = js::number(0); (i < this->totalIncrease); i++) {
                        {
                                        normal[(amount + i)] = normals[i];
                        }
            }
    }
}

auto ShellFace4::processIndices(TileData mesh, DataSizes sizes) {
    {
            const js::any indices = mesh["indexBuffer"];
            for (js::number i = js::number(0); (i < this->indexIncrease); i++) {
                        {
                                        const js::any offset = this->_convexIndices[i];
                                        indices[(sizes["indices"] + i)] = (sizes["vertices"] + offset);
                        }
            }
            sizes["indices"] += this->indexIncrease;
    }
}
