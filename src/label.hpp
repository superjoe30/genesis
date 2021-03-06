#ifndef LABEL_HPP
#define LABEL_HPP

#include "freetype.hpp"
#include "string.hpp"
#include "glm.hpp"
#include "font_size.hpp"
#include "glfw.hpp"

class Gui;
class GuiWindow;

class Label {
public:
    Label(Gui *gui);
    ~Label();

    // need to call update() to make it take effect
    void set_text(const String &text) {
        _text = text;
    }
    const String &text() const {
        return _text;
    }
    String &text() {
        return _text;
    }
    // need to call update() to make it take effect
    void set_font_size(int size);

    void update();

    int width() const {
        return _width;
    }

    int height() const {
        return _height;
    }

    void draw(const glm::mat4 &mvp, const glm::vec4 &color);

    int cursor_at_pos(int x, int y) const;
    void pos_at_cursor(int index, int &x, int &y) const;
    void get_slice_dimensions(int start, int end, int &start_x, int &end_x) const;

    int above_size() const {
        return _font_size->_max_above_size;
    }

    int below_size() const {
        return _font_size->_max_below_size;
    }

    void replace_text(int start, int end, String text);

private:
    struct Letter {
        uint32_t codepoint;

        int left; // half-way between prev letter and this one. 0 for first letter
        int bitmap_left; // left + bitmap_left is the first pixel of the letter
        int bitmap_width; // left + bitmap_left + bitmap_width is the last pixel of the letter
        int full_width; // left + full_width is half-way between this letter and next

        int above_size;
        int below_size;
        int bitmap_top;
    };

    Gui *_gui;
    int _width;
    int _height;
    GLuint _texture_id;
    GLuint _vertex_buffer;

    String _text;
    FontSize *_font_size;

    ByteBuffer _img_buffer;

    // cached from _text on update()
    List<Letter> _letters;
};

#endif
