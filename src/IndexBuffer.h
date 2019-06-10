#pragma once

class IndexBuffer {
private:
    unsigned int m_RendererID; // It's an ID for every type of buffer or object we allocate in OpenGL.
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int *data, unsigned int count); // size usually means #bytes, count means #elements
    ~IndexBuffer();

    void Bind() const;

    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
};