#pragma once

class VertexBuffer {
private:
    unsigned int m_RendererID; // It's an ID for every type of buffer or object we allocate in OpenGL.
public:
    VertexBuffer(const void *data, unsigned int size);

    ~VertexBuffer();

    void Bind() const;

    void Unbind() const;
};