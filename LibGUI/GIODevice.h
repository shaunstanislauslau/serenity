#pragma once

#include <LibGUI/GObject.h>
#include <AK/ByteBuffer.h>

class GIODevice : public GObject {
public:
    enum OpenMode {
        NotOpen      = 0,
        ReadOnly     = 1,
        WriteOnly    = 2,
        ReadWrite    = 3,
        Append       = 4,
        Truncate     = 8,
        MustBeNew    = 16,
    };

    virtual ~GIODevice() override;

    int fd() const { return m_fd; }
    unsigned mode() const { return m_mode; }
    bool eof() const { return m_eof; }

    int error() const { return m_error; }
    const char* error_string() const;

    bool has_error() const { return m_error != 0; }

    ByteBuffer read(int max_size);
    ByteBuffer read_line(int max_size);

    virtual bool open(GIODevice::OpenMode) = 0;
    virtual bool close() = 0;

    virtual const char* class_name() const override { return "GIODevice"; }

protected:
    explicit GIODevice(GObject* parent = nullptr);

    void set_fd(int fd) { m_fd = fd; }
    void set_mode(OpenMode mode) { m_mode = mode; }
    void set_error(int error) { m_error = error; }
    void set_eof(bool eof) { m_eof = eof; }

private:
    bool populate_read_buffer();

    int m_fd { -1 };
    int m_error { 0 };
    bool m_eof { false };
    OpenMode m_mode { NotOpen };
    Vector<byte> m_buffered_data;
};
